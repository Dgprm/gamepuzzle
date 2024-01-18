#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

const int size = 3;
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

void startGame(int puzzle[size][size]) {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(puzzle[i][j] == 0) {
                cout << "  ";
            } else {
                // Màu xanh lá cho số từ 1 đến 9
                if (puzzle[i][j] >= 1 && puzzle[i][j] <= 9) {
                    cout << GREEN << puzzle[i][j] << " " << RESET;
                } else {
                    cout << puzzle[i][j] << " ";
                }
            }
        }
        cout << endl;
    }
}

void shuffleBoard(int puzzle[size][size]) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int randomI = rand() % 3;
            int randomJ = rand() % 3;
            swap(puzzle[i][j], puzzle[randomI][randomJ]);
        }
    }
}

bool isValidMove(int i, int j) {
    return (i >= 0 && i < size && j >= 0 && j < size);
}

bool checkWin(int puzzle[size][size]) {
    int counter = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (puzzle[i][j] != counter % (size * size)) {
                return false;
            }
            counter++;
        }
    }
    return true;
}

void movePuzzle(int puzzle[size][size], int &emptyRow, int &emptyCol, char choice) {
    int newRow = emptyRow;
    int newCol = emptyCol;
    switch(choice) {
        case 'W':
            newRow++;
            break;
        case 'S':
            newRow--;
            break;
        case 'A':
            newCol++;
            break;
        case 'D':
            newCol--;
            break;
        default:
            return;
    }
    if (isValidMove(newRow, newCol)) {
        swap(puzzle[emptyRow][emptyCol], puzzle[newRow][newCol]);
        emptyRow = newRow;
        emptyCol = newCol;
    }
}

void checkEmpty(int puzzle[size][size], int &emptyRow, int &emptyCol) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (puzzle[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
            }
        }
    }
}

void findSolution(int puzzle[size][size], int &emptyRow, int &emptyCol) {
    int destination[size][size];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            destination[i][j] = i * size + j + 1;
        }
    }
    destination[size - 1][size - 1] = 0;

    cout << "Trang thai dich:" << endl;
    startGame(destination);
    cout << "Dang tim kiem duong di..." << endl;
    while (!checkWin(puzzle)) {
        char moveOptions[] = {'W', 'S', 'A', 'D'};
        char randomMove = moveOptions[rand() % 4];

        movePuzzle(puzzle, emptyRow, emptyCol, randomMove);
        system("cls");
        startGame(puzzle);
    }

    cout << "Xin chuc mung ban da chien thang" << endl;
}

void thucongGame() {
    int puzzle[size][size] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    int emptyRow, emptyCol;
    char choice;
    shuffleBoard(puzzle);
    checkEmpty(puzzle, emptyRow, emptyCol);

    do {
        system("cls");
        startGame(puzzle);
        cout << RED << "Nhap W: di chuyen len, S: di chuyen xuong, A: di chuyen sang trai, D: di chuyen sang phai, Q de thoat game: ";
        cin >> choice;
        if (islower(choice)) {
            choice = toupper(choice);
        }
        if (choice == 'Q') {
            break;
        }
        movePuzzle(puzzle, emptyRow, emptyCol, choice);
        if (checkWin(puzzle)) {
            cout << "Xin chuc mung ban da chien thang";
            break;
        }
    } while (true);
}
void autorunGame() {
    int puzzle[size][size] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    int emptyRow, emptyCol;
    char choice;

    findSolution(puzzle, emptyRow, emptyCol);
}

int main() {
    string input;
    cout<<"######################### GAME PUZZLE ####################"<<endl;
    cout << "1. Nhap 'autorun' de tu dong chay  "<<endl<<"2. Nhap phim bat ky de choi thu cong"<< endl;
    cout << "Chon chuc nang:";
    cin >> input;
    
    if (input == "autorun") {
        autorunGame();
    } else {
        thucongGame();
    }

    return 0;
}
