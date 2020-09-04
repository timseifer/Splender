/*
 * game.h
 * COMP11 Splendor
 */

#ifndef GAME_H
#define GAME_H

#include <string>

#include "player.h"

// #include "splendor.data"
#include <vector>

using namespace std;

class Game {
  public:
    //constructor
    Game(string filename, string play_nobles);

    //main gameplay
    void playGame();
    //setting up data structures
    int nobleloyalty(Player* arg, vector<Card> n);
    int playervcardo(Player* argc, Card type, int tempv);
    bool playervcard(Player argc, Card type, int tempv);
    int getgembank(int index);
    void setgembank(int index, int num);
    int colortonum(string color);
    string indexToColor(int index);
    void gridSetter();
    void addCardm(Card *m, vector<Card> &ctype);
    bool setupGame(string splendor_data);
  private:

    //drawing functions
    void drawBoard();
    void drawNoble(int vpos, int hpos, Card c);
    void drawPlayer(int vpos, int hpos, Player *p);
    void drawDeck(int vpos, int hpos, string type);
    void drawCard(int vpos, int hpos, Card c);
    void drawGem(int vpos, int hpos, string color);
    void clearBoard();

    static const int BOARD_HEIGHT = 41;
    static const int BOARD_WIDTH = 120;
    static const int CARD_WIDTH = 13;
    static const int CARD_HEIGHT = 8;
    static const int CARD_ROWS = 3;
    static const int CARD_COLS = 4;
    static const int NUM_NOBLES = 3;
    static const int GEMS = 6;

    //nobles activated true/false
    bool play_nobles;

    //cards in play
    Card *grid[CARD_ROWS][CARD_COLS];

    //display
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    string board_color[BOARD_HEIGHT][BOARD_WIDTH];
};

#endif
