#ifndef NONCLASSFUNCTIONS_H
#define NONCLASSFUNCTIONS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <cctype>
#include <time.h>
#include <vector>

#define REDb "\x1b[41m"
#define GREENb "\x1b[42m"
#define BLUEb "\x1b[44m"
#define CYANb "\x1b[46m"
#define WHITEb "\x1b[47m"
#define RESET "\x1b[0m"

using namespace std;

// probability
int sixSidedDie();
int fiveSidedDie();
int fourSidedDie();
int threeSidedDie();
int hundredSidedDie();
int dieRollingTwoPlayers(string player1, string player2);

// validators
string swapTypeChoiceVal(string input);
string dropTypeChoiceVal(string input);
string islandCombatChoiceMenuVal(string input);
string epicCombatChoiceMenuVal(string input);
string shopVisitQuestionVal(string input);
string userFirstPlayerChoiceVal(string input);
string userSecondPlayerChoiceVal(string input, string firstPlayerChoice);
string shopOptionChoiceVal(string input);
string menuChoiceVal(string input);
string swapOrDropVal(string input);
string defOrDamBuffVal(string nameD, string nameS, string input);
bool beginOdysseyVal(string& input);

// other
int staminaRefill();
int goldWindfall();
int damageBuff();
int split(string input_string, char separator, string arr[], const int ARR_SIZE);
void shuffle(string board[], string boardTemplate[], bool sisterBoard[]);
string colorize(string input, string temp);

// cout simplifier
void characterChoiceOptions(int playerNum);

#endif