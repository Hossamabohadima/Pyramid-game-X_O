#include "BoardGame_Classes.hpp"
#include <iostream>

X_O_Board::X_O_Board()
{
    n_moves = 0;
    n_cols = 5;
    n_rows = 3;
    board = new char *[n_rows];
    for (size_t i = 0; i < n_rows; i++)
    {
        board[i] = new char[i * 2 + 1];
        for (size_t j = 0; j < i * 2 + 1; j++)
        {
            board[i][j] = ' ';
        }
    }
}
bool X_O_Board::update_board(int x, int y, char mark)
{
    if (n_moves == 9)
    {
        return false;
    }
    if (x < n_rows && x > -1 && y < n_cols && y > -1)
    {
        if (board[x][y] != ' ')
        {

            return false;
        }
        board[x][y] = mark;
        n_moves++;
        return true;
    }
    else
        return false;
}

void X_O_Board::display_board()
{
    cout << "======================\n";
    for (size_t i = 0; i < n_rows; i++)
    {
        if (i == 0)
        {
            cout << "   |";
        }
        if (i == 1)
        {
            cout << " |";
        }
        for (size_t j = 0; j < i * 2 + 1; j++)
        {
            cout << board[i][j] << "|";
        }
        cout << "\n"
             << "----------\n";
    }
    cout << "======================\n";
}

bool X_O_Board::is_winner()
{

    if (board[2][2] == board[1][1] && board[0][0] == board[2][2] && board[2][2] != ' ')
    {
        return true;
    }
    else if (board[1][2] == board[1][0] && board[1][1] == board[1][0] && board[1][1] != ' ')
    {
        return true;
    }
    else if (board[0][0] == board[1][2] && board[1][2] == board[2][4] && board[0][0] != ' ')
    {
        return true;
    }
    else if (board[0][0] == board[2][0] && board[1][0] == board[0][0] && board[0][0] != ' ')
    {
        return true;
    }
    else
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (board[2][0 + i] == board[2][1 + i] && board[2][2 + i] == board[2][1 + i] && board[2][0 + i] != ' ')
            {
                return true;
            }
        }
    }

    return false;
}
bool X_O_Board::is_draw()
{
    if (n_moves == 9)
    {
        return true;
    }
    else
        return false;
}

X_O_Board::~X_O_Board()
{
    delete[] board;
}
Player::Player(char symbol) : symbol(symbol)
{
    name = "computer";
}
Player::Player(int order, char symbol) : symbol(symbol)
{
    name = "player " + to_string(order);
}
void Player::get_move(int &x, int &y)
{
    cout << name << " "
         << "Enter your move (x y): ";
    cin >> x >> y;
}
string Player::To_string()
{
    return (name + " symbol is " + symbol);
}
char Player::get_symbol()
{
    return symbol;
}
RandomPlayer::RandomPlayer(char symbol) : Player(symbol)
{
    dimension = 3;
}

void RandomPlayer::get_move(int &x, int &y)
{
    x = rand() % dimension;
    y = rand() % (2 * x + 1);
}

GameManager::GameManager(Board *board, Player *playerPtr[2])
{
    boardPtr = board;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::run()
{
    int x, y;
    boardPtr->display_board();
    while (true)
    {

        for (size_t i = 0; i < 2; i++)
        {
            x = 5;
            y = 5;
            while (!boardPtr->update_board(x, y, players[i]->get_symbol()))
            {
                players[i]->get_move(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_winner())
            {
                cout << "the winner is " << players[i]->To_string() << "\n";
                cout << "Good luck " << players[i + 1 % 2]->To_string();
                return;
            }
            else if (boardPtr->is_draw())
            {
                cout << "good game " << players[i]->To_string() << "\n";
                cout << "Good game " << players[i + 1 % 2]->To_string();
                return;
            }
        }
    }
}
GameManager::~GameManager()
{
    delete boardPtr;
}