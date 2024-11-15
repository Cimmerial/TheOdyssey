#include "helperC.h"

// probability
int sixSidedDie() // make sure srand (time(NULL)); is included
{
    return (rand() % 6 + 1);
}
int fiveSidedDie() // make sure srand (time(NULL)); is included
{
    return (rand() % 5 + 1);
}
int fourSidedDie() // make sure srand (time(NULL)); is included
{
    return (rand() % 4 + 1);
}
int threeSidedDie() // make sure srand (time(NULL)); is included
{
    return (rand() % 3 + 1);
}
int hundredSidedDie()
{
    return (rand() % 100 + 1);
}
int dieRollingTwoPlayers(string player1, string player2)
{
    int firstPlayerRoll = sixSidedDie();
    int secondPlayerRoll = sixSidedDie();
    cout << player1 << " rolled a " << firstPlayerRoll << " and " << player2 << " rolled a " << secondPlayerRoll << "!" << endl;
    while (firstPlayerRoll == secondPlayerRoll)
    {
        cout << "Tie! Roll again!" << endl;
        firstPlayerRoll = sixSidedDie(), secondPlayerRoll = sixSidedDie();
        cout << player1 << " rolled a " << firstPlayerRoll << " and " << player2 << " rolled a " << secondPlayerRoll << "!" << endl;
    }
    if (firstPlayerRoll > secondPlayerRoll)
    {
        cout << player1 << " wins with a " << firstPlayerRoll << "!" << endl;
        return 0;
    }
    else
    {
        cout << player2 << " wins with a " << secondPlayerRoll << "!" << endl;
        return 1;
    }
}

// validators
string swapTypeChoiceVal(string input)
{
    while (input != "1" && input != "2" && input != "Weapon" && input != "Shield" && input != "weapon" && input != "shield")
    {
        cout << "Invalid choice" << endl;
        cout << "Would you like to swap your weapon or shield?" << endl;
        cout << "1: Weapon" << endl;
        cout << "2: Shield" << endl;
        getline(cin, input);
    }
    return input;
}
string dropTypeChoiceVal(string input)
{
    while (input != "1" && input != "2")
    {
        cout << "Invalid choice" << endl;
        cout << "Would you like to drop a piece of equipment or a potion?" << endl;
        cout << "1: Equipment (weapons and shields)" << endl;
        cout << "2: Potions" << endl;
        getline(cin, input);
    }
    return input;
}
string islandCombatChoiceMenuVal(string input)
{
    while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5")
    {
        cout << "Invalid choice" << endl;
        cout << "Make an Action!: (choose a number)" << endl;
        cout << "(1) Attack!" << endl;
        cout << "(2) Use Potion" << endl;
        cout << "(3) Swap Weapon" << endl;
        cout << "(4) Use Ultimate" << endl;
        cout << "(5) Retreat!" << endl;
        getline(cin, input);
    }
    return input;
}
string epicCombatChoiceMenuVal(string input)
{
    while (input != "1" && input != "2" && input != "3" && input != "4")
    {
        cout << "Invalid choice" << endl;
        cout << "Make an Action!: (choose a number)" << endl;
        cout << "(1) Attack!" << endl;
        cout << "(2) Use Potion" << endl;
        cout << "(3) Swap Weapon" << endl;
        cout << "(4) Use Ultimate" << endl;
        getline(cin, input);
    }
    return input;
}
string shopVisitQuestionVal(string input)
{
    while (input != "Y" && input != "N" && input != "y" && input != "n" && input != "1")
    {
        cout << "Invalid choice" << endl;
        cout << "Would you like to visit the shop? (Y/N)" << endl;
        getline(cin, input);
    }
    return input;
}
string userFirstPlayerChoiceVal(string input)
{
    while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5")
    {
        cout << "Invalid choice" << endl;
        cout << "Would the first player please pick their character:" << endl;
        cout << "(1) Odysseus (2) Argos (3) Circe (4) Perseus (5) Heracles" << endl;
        getline(cin, input);
    }
    return input;
}
string userSecondPlayerChoiceVal(string input, string firstPlayerChoice)
{
    while ((input != "1" && input != "2" && input != "3" && input != "4" && input != "5") || input == firstPlayerChoice)
    {
        cout << "Invalid choice" << endl;
        cout << "Would the second player please pick their character:" << endl;
        cout << "(1) Odysseus (2) Argos (3) Circe (4) Perseus (5) Heracles" << endl;
        getline(cin, input);
    }
    return input;
}
string shopOptionChoiceVal(string input)
{
    while (input != "1" && input != "2" && input != "3" && input != "4")
    {
        cout << "Invalid choice" << endl;
        cout << "Welcome to the shop! What would you like to do?" << endl;
        cout << "(1) Buy Equipment" << endl;
        cout << "(2) Buy Potions" << endl;
        cout << "(3) Sell Equipment" << endl;
        cout << "(4) Leave Shop" << endl;
        getline(cin, input);
    }
    return input;
}
string menuChoiceVal(string input)
{
    while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5")
    {
        cout << "Invalid choice" << endl;
        cout << "What would you like to do?" << endl;
        cout << "(1) Move" << endl;
        cout << "(2) Swap/Drop Weapon" << endl;
        cout << "(3) Use Potion" << endl;
        cout << "(4) Print Player Stats" << endl;
        cout << "(5) Quit" << endl;
        getline(cin, input);
    }
    return input;
}
string swapOrDropVal(string input)
{
    while (input != "1" && input != "2")
    {
        cout << "Invalid choice" << endl;
        cout << "Would you like to swap or drop your equipment?" << endl;
        cout << "(1) Swap" << endl;
        cout << "(2) Drop" << endl;
        getline(cin, input);
    }
    return input;
}
string defOrDamBuffVal(string nameD, string nameS, string input)
{
    while (input != "1" && input != "2")
    {
        cout << "Invalid choice" << endl;
        cout << "Add 20 damage to " << nameD << " or 20 defense to " << nameS << "?" << endl;
        cout << "(1) " << nameD << " +20 damage" << endl;
        cout << "(2) " << nameS << " +20 defense" << endl;
        getline(cin, input);
    }
    return input;
}
bool beginOdysseyVal(string &input)
{
    while (input != "y" && input != "Y" && input != "n" && input != "N" && input != "4815162342")
    {
        cout << "It's so simple:" << endl;
        cout << "Begin Odyssey? (Y/N)" << endl;
        getline(cin, input);
    }
    if (input == "4815162342")
    {
        cout << "you are now cheating..." << endl;
        return true;
    }
    return false;
}

// other
int staminaRefill()
{
    return (rand() % 21 + 10);
}
int goldWindfall()
{
    return (rand() % 31 + 20);
}
int damageBuff()
{
    return (rand() % 6 + 5);
}
int split(string input_string, char separator, string arr[], const int ARR_SIZE)
{

    int separatorAmount = 0;
    if (input_string == "")
    {
        arr[0] = input_string;
        return 0;
    }
    for (int i = 0; i < static_cast<int>(input_string.length()); i++)
    {
        if (input_string[i] == separator)
        {
            separatorAmount += 1;
        }
    }
    if (separatorAmount == 0)
    {
        arr[0] = input_string;
        return 1;
    }

    int x = 0;
    for (int i = 0; i < static_cast<int>(input_string.length()); i++)
    {
        if (input_string[i] != separator)
        {
            arr[x] += input_string[i];
        }
        else
        {
            x++;
        }
        if (x >= ARR_SIZE)
        {
            return -1;
        }
    }
    return separatorAmount + 1;
}
void shuffle(string board[], string boardTemplate[], bool sisterBoard[])
{
    string tempy;
    bool tempySister;
    int randomIndex;
    for (int j = 1; j < 59; j++)
    {
        randomIndex = rand() % 60; // Shuffle within the row
        tempy = board[j];
        board[j] = board[randomIndex];
        board[randomIndex] = tempy;
        tempy = boardTemplate[j];
        boardTemplate[j] = boardTemplate[randomIndex];
        boardTemplate[randomIndex] = tempy;
        tempySister = sisterBoard[j];
        sisterBoard[j] = sisterBoard[randomIndex];
        sisterBoard[randomIndex] = tempySister;
    }
}
string colorize(string input, string temp)
{
    if (temp == "~")
    {
        return BLUEb + input + RESET;
    }
    else if (temp == "_")
    {
        return GREENb + input + RESET;
    }
    else if (temp == "$")
    {
        return WHITEb + input + RESET;
    }
    else if (temp == ".")
    {
        return CYANb + input + RESET;
    }
    else // if (input == "*")
    {
        return REDb + input + RESET;
    }
}

// cout simplifier
void characterChoiceOptions(int playerNum)
{
    if (playerNum == 0)
    {
        cout << "Hello! Would the first player please pick their character:" << endl;
        cout << "Which character would you like to choose? Enter a number." << endl;
        cout << "(1) Odysseus (2) Argos (3) Circe (4) Perseus (5) Heracles" << endl;
    }
    else
    {
        cout << "Hello! Would the second player please pick their character:" << endl;
        cout << "Which character would you like to choose? Enter a number." << endl;
        cout << "(1) Odysseus (2) Argos (3) Circe (4) Perseus (5) Heracles" << endl;
    }
}
