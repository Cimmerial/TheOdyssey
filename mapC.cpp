#include "mapC.h"

// constructor
Map::Map()
{
    playerIcon[0] = "1", playerIcon[1] = "2";
    playerIndex[0] = 0, playerIndex[1] = 0;
    for (int i = 0; i < 34; i++) // add water
    {
        for (int j = 0; j < 2; j++)
        {
            playerBoard[j][i] = "~";
            playerBoardTemplate[j][i] = "~";
        }
    }
    for (int i = 34; i < 44; i++) // add land
    {
        for (int j = 0; j < 2; j++)
        {
            playerBoard[j][i] = "_";
            playerBoardTemplate[j][i] = "_";
        }
    }
    for (int i = 44; i < 59; i++) // add special
    {
        for (int j = 0; j < 2; j++)
        {
            playerBoard[j][i] = "*";
            playerBoardTemplate[j][i] = "*";
        }
    }
    for (int i = 59; i < 60; i++) // add start / end water
    {
        for (int j = 0; j < 2; j++)
        {
            playerBoard[j][i] = "~";
            playerBoardTemplate[j][i] = "~";
        }
    }
    for (int i = 0; i < 60; i++) // sets all player indicies to false
    {
        for (int j = 0; j < 2; j++)
        {
            playerSisterBoard[j][i] = false;
        }
    }
    string dummyArr[60], dummyArrTemplate[60];
    bool sisterDummyArr[60];
    for (int i = 0; i < 60; i++)
    {
        dummyArr[i] = playerBoard[0][i];
        dummyArrTemplate[i] = playerBoardTemplate[0][i];
        sisterDummyArr[i] = playerSisterBoard[0][i];
    }
    shuffle(dummyArr, dummyArrTemplate, sisterDummyArr); // only allows for 1D arrays
    for (int i = 0; i < 60; i++)
    {
        playerBoard[0][i] = dummyArr[i];
        playerBoardTemplate[0][i] = dummyArrTemplate[i];
        playerSisterBoard[0][i] = sisterDummyArr[i];
    }
    for (int i = 0; i < 60; i++)
    {
        dummyArr[i] = playerBoard[1][i];
        dummyArrTemplate[i] = playerBoardTemplate[1][i];
        sisterDummyArr[i] = playerSisterBoard[1][i];
    }
    shuffle(dummyArr, dummyArrTemplate, sisterDummyArr); // only allows for 1D arrays
    for (int i = 0; i < 60; i++)
    {
        playerBoard[1][i] = dummyArr[i];
        playerBoardTemplate[1][i] = dummyArrTemplate[i];
        playerSisterBoard[1][i] = sisterDummyArr[i];
    }
    playerSisterBoard[0][0] = true, playerSisterBoard[1][0] = true; // puts players on starting tiles
    playerBoard[0][59] = "$", playerBoardTemplate[0][59] = "$";     // Ithaca
    playerBoard[0][0] = ".", playerBoardTemplate[0][0] = ".";       // start
    playerBoard[1][59] = "$", playerBoardTemplate[1][59] = "$";     // Ithaca
    playerBoard[1][0] = ".", playerBoardTemplate[1][0] = ".";       // start
}

// map misc
void Map::changePlayerIcon(int playerNum, string icon)
{
    playerIcon[playerNum] = icon[0];
}
int Map::getMapPos(int player)
{
    return playerIndex[player];
}
int Map::getTileType(int player)
{
    if (playerBoardTemplate[player][playerIndex[player]] == "~")
    {
        return 1; // calamity chance check
    }
    else if (playerBoardTemplate[player][playerIndex[player]] == "_")
    {
        return 2; // island encounter
    }
    else if (playerBoardTemplate[player][playerIndex[player]] == "*")
    {
        return 3; // special tile stuff (use setMapPos for knockback of player)
    }
    else if (playerBoardTemplate[player][playerIndex[player]] == ".")
    {
        return 10;
    }
    else
    {
        return 4;
    }
}
int Map::epicCombatMoment()
{
    if (playerIndex[0] == playerIndex[1])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Map::setMapPos(int player, int newIndex, int oldIndex) // theoretically erases + moves visual / recorded ind
{
    playerSisterBoard[player][oldIndex] = false;
    if (newIndex >= 59)
    {
        playerSisterBoard[player][59] = true;
        playerIndex[player] = 59;
    }
    else
    {
        playerSisterBoard[player][newIndex] = true;
        playerIndex[player] = newIndex;
    }
}
int Map::move(int player, int moveAmount, string playerTemp[][60]) // returns moveamount (accounts for islands)
{
    int oldIndex = getMapPos(player);
    for (int i = oldIndex + 1; i < oldIndex + moveAmount; i++)
    {
        if (playerTemp[player][i] == "_")
        {
            setMapPos(player, i, oldIndex);
            return i; // returns new index
        }
    }
    return oldIndex + moveAmount;
}
void Map::printMap()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            if (playerSisterBoard[i][j] == false)
            {
                cout << colorize(playerBoard[i][j], playerBoardTemplate[i][j]);
            }
            else
            {
                cout << colorize(playerIcon[i], playerBoardTemplate[i][j]);
            }
        }
        cout << endl;
    }
}
