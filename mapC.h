#ifndef MAP_H
#define MAP_H

#include "helperC.h"

class Map
{
public:
    int playerIndex[2];
    string playerIcon[2];
    bool playerSisterBoard[2][60];
    string playerBoard[2][60];
    string playerBoardTemplate[2][60];

    Map();
    void changePlayerIcon(int playerNum, string icon);
    int getMapPos(int player);
    int getTileType(int player);
    int epicCombatMoment();
    void setMapPos(int player, int newIndex, int oldIndex);
    int move(int player, int moveAmount, string playerTemp[][60]);
    void printMap();
};

#endif