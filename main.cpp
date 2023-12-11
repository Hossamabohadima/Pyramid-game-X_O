#include "BoardGame_Classes.cpp"

int main()
{
    Board *X_o = new X_O_Board;
    Player *players[2];
    players[0] = new Player(1, 'X');
    players[1] = new RandomPlayer('O');
    GameManager v(X_o, players);
    v.run();
    // delete[] players;
    // delete X_o;
}