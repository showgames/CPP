#include <iostream>
#include "game.hpp"
using namespace std;

void
STAGE::init(int height, int width, char* boardData)
{
    boardHeight = height;
    boardWidth  = width;

    board = new OBJECT[height * width];

    for (int i = 0; i < height * width; i++) {
        switch(boardData[i]) {
            case '#': board[i] = WALL;
            break;

            case '.': board[i] = GOAL;
            break;

            case 'o': board[i] = BAGGAGE;
            break;

            case 'p': board[i] = PLAYER;
            break;

            case 'P': board[i] = ON_GOAL_PLAYER;
            break;

            case ' ': board[i] = EMPTY;
            break;

            default: cout << "Initialize error" << endl;
            break;
        }
    }
    setDirection();
    searchPlayer();
}

void
STAGE::draw()
{
    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            switch(board[i * boardWidth + j]) {
                case WALL: cout <<  "#";
                break;

                case GOAL: cout << ".";
                break;

                case BAGGAGE: cout << "o";
                break;

                case ON_GOAL_BAGGAGE: cout << "O";
                break;

                case PLAYER: cout << "p";
                break;

                case ON_GOAL_PLAYER: cout << "P";
                break;

                case EMPTY: cout << " ";
                break;

                default: cout << "Draw error" << endl;
                break;
            }
        }
        cout << endl;
    }
}

void
STAGE::update(int dir)
{
    int tmpNext = (playerY * boardWidth + playerX) + Direction[dir];
    int tmpNext2 = (playerY * boardWidth + playerX) + Direction[dir] * 2;
    int pXY = playerY * boardWidth + playerX;
    int flag = checkMove(tmpNext, tmpNext2);
    if (!flag) {
        cout << "cannot move to this direction..." << endl;
        return;
    }

    if (board[tmpNext] == EMPTY) {
        board[tmpNext] = PLAYER;
        board[pXY] = (board[pXY] == ON_GOAL_PLAYER)? GOAL : EMPTY;
    }
    else if (board[tmpNext] == GOAL) {
        board[tmpNext] = ON_GOAL_PLAYER;
        board[pXY] = (board[pXY] == ON_GOAL_PLAYER)? GOAL : EMPTY;
    }
    else if (board[tmpNext] == BAGGAGE || board[tmpNext] == ON_GOAL_BAGGAGE) {
        if (board[tmpNext2] == GOAL) {
            board[tmpNext2] = ON_GOAL_BAGGAGE;
            board[tmpNext] = (board[tmpNext] == ON_GOAL_BAGGAGE)? ON_GOAL_PLAYER : PLAYER;
            board[pXY] = (board[pXY] == ON_GOAL_PLAYER)? GOAL : EMPTY;
        } else if (board[tmpNext2] == EMPTY){
            board[tmpNext2] = BAGGAGE;
            board[tmpNext] = (board[tmpNext] == ON_GOAL_BAGGAGE)? ON_GOAL_PLAYER : PLAYER;
            board[pXY] = (board[pXY] == ON_GOAL_PLAYER)? GOAL : EMPTY;
        }
    }
    searchPlayer();
}

int
STAGE::checkClear()
{
    for (int i = 0; i < boardHeight * boardWidth; i++) {
        if (board[i] == BAGGAGE) return 0;
    }
    return 1;
}

void
STAGE::searchPlayer()
{
    int i;
    for (i = 0; i < boardHeight*boardWidth; i++) {
        if (board[i] == PLAYER || board[i] == ON_GOAL_PLAYER) break;
    }

    playerX = i % boardWidth;
    playerY = i / boardWidth;
}

int
STAGE::checkMove(int tmpNext, int tmpNext2)
{
    if (board[tmpNext] == WALL) {
        return 0;
    }
    else if (board[tmpNext] == EMPTY || board[tmpNext] == GOAL) {
        return 1;
    }
    else if (board[tmpNext] == BAGGAGE || board[tmpNext] == ON_GOAL_BAGGAGE) {
        if (board[tmpNext2] == EMPTY || board[tmpNext2] == GOAL) return 1;
        else return 0;
    }

    return 0;
}

void
STAGE::setDirection()
{
    Direction[0] = -boardWidth;
    Direction[1] = boardWidth;
    Direction[2] = -1;
    Direction[3] = 1;
}