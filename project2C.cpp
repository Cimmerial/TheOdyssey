#include "gameC.h"

int main() 
{
    srand(time(NULL));

    // instantiating classes
    Game game;
    Map map;
    Entity player[2];

    // initialize variables
    string userPlayerChoice[2];
    int playerTurn = -1;
    int playerOffTurn = -1;
    int moveAmount = -1;
    int playerWhoQuit = -1;
    bool cheatCode = false;

    // load resources
    game.loadEquipment("textFiles/equipment.txt");
    game.loadPotions("textFiles/potions.txt");
    game.loadEntities("textFiles/enemy.txt");
    game.loadPlayers("textFiles/player.txt");
    game.loadRiddles("textFiles/riddles.txt");

    // start / enter cheat code
    cout << "Begin Odyssey? (Y/N)" << endl;
    string begin;
    getline(cin, begin);
    cheatCode = beginOdysseyVal(begin);

    // choose characters
    characterChoiceOptions(0);
    getline(cin, userPlayerChoice[0]);
    userPlayerChoice[0] = userFirstPlayerChoiceVal(userPlayerChoice[0]);
    characterChoiceOptions(1);
    getline(cin, userPlayerChoice[1]);
    userPlayerChoice[1] = userSecondPlayerChoiceVal(userPlayerChoice[1], userPlayerChoice[0]);
    player[0] = game.getPlayer(stoi(userPlayerChoice[0]) - 1);
    player[1] = game.getPlayer(stoi(userPlayerChoice[1]) - 1);
    map.changePlayerIcon(0, player[0].getName()), map.changePlayerIcon(1, player[1].getName());

    // for testing; makes players ~invincible
    if (cheatCode)
    {
        for (int i = 0; i < 2; i++)
        {
            player[i].updateEquipment(game.getEquipmentViaName("Zeus' Bolt"));
            player[i].updateEquipment(game.getEquipmentViaName("Hades' Crown"));
            player[i].changeGold(500);
            player[i].changeMaxHp(500);
            player[i].changeHp(500);
            player[i].updatePotion(game.getPotionViaName("Philter of Wisdom"));
        }
    }
    else // normal gameplay
    {
        // load characters
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < player[i].getPotionCount(); j++)
            {
                player[i].updatePotion(game.getPotionViaName(game.getPlayer(stoi(userPlayerChoice[i]) - 1).getTempGear(0)));
            }
            player[i].updateEquipment(game.getEquipmentViaName(game.getPlayer(stoi(userPlayerChoice[i]) - 1).getTempGear(1)));
        }
    }

    // visit shop
    game.generateShop(player[0]);
    game.generateShop(player[1]);

    // roll for start
    playerTurn = dieRollingTwoPlayers(player[0].getName(), player[1].getName());
    cout << endl;
    cout << player[playerTurn].getName() << " starts!" << endl;

    while (true) // main game loop
    {
        if (playerTurn == 0) // updates playerOffTurn
        {
            playerOffTurn = 1;
        }
        if (playerTurn == 1)
        {
            playerOffTurn = 0;
        }
        if (moveAmount != 9) // only runs once a turn
        {
            player[playerTurn].poisonOrDeseaseTick();
            cout << endl;
            cout << "(P" << playerTurn + 1 << ") ";
            player[playerTurn].entityStatsmenu();
            map.printMap();
        }
        moveAmount = game.playerOptionMenu(player[playerTurn]);
        if (moveAmount == 0) // end game
        {
            playerWhoQuit = playerTurn;
        }
        if (moveAmount >= 1 && moveAmount <= 6) // if "move" is chosen
        {
            map.setMapPos(playerTurn, map.move(playerTurn, moveAmount, map.playerBoardTemplate), map.getMapPos(playerTurn));
            if (map.epicCombatMoment()) // if playerColumn = player2Column
            {
                map.printMap();
                game.combat(player[playerTurn], player[playerOffTurn], 'E', game);
            }
            else // checks if water, special, island
            {
                game.tileAction(map.getTileType(playerTurn), player[playerTurn], player[playerOffTurn], map, game, playerTurn);
            }
        }
        if (moveAmount != 9) // only runs once a turn
        {
            // add stam and skip turn
            if (player[0].getStam() <= 0)
            {
                player[0].changeStam(10);
                player[0].setSkip(true);
            }
            if (player[1].getStam() <= 0)
            {
                player[1].changeStam(10);
                player[1].setSkip(true);
            }

            // transition to next players turn (account for turn skipping)
            if (playerTurn == 0 && !(player[1].getSkip()))
            {
                playerTurn = 1;
            }
            else if (playerTurn == 1 && !(player[0].getSkip()))
            {
                playerTurn = 0;
            }

            // reset turn skip
            player[0].setSkip(false), player[1].setSkip(false);
        }
        // if ( quit == true || HP == 0 || Ithica Reached )
        if (moveAmount == 0 || player[0].getHp() <= 0 || player[1].getHp() <= 0 || map.getMapPos(0) == 59 || map.getMapPos(1) == 59)
        {
            break;
        }
    }

    cout << "GAME OVER" << endl;
    // print player stats
    if (player[0].getHp() <= 0 && player[1].getHp() <= 0)
    {
        map.printMap();
        cout << "Wow! You both lose!" << endl
             << endl;
        cout << "Losing stats of " << player[0].getName() << "!" << endl;
        player[0].entityStatsmenu();
        player[0].getTotals();
        cout << endl;
        cout << "Losing stats of " << player[1].getName() << "!" << endl;
        player[1].entityStatsmenu();
        player[1].getTotals();
    }
    else if (player[0].getHp() <= 0 || playerWhoQuit == 0 || map.getMapPos(1) == 49)
    {
        map.printMap();
        cout << player[1].getName() << " wins!" << endl
             << endl;
        cout << "Winning stats of " << player[1].getName() << "!" << endl;
        player[1].entityStatsmenu();
        player[1].getTotals();
        cout << endl;
        cout << "Losing stats of " << player[0].getName() << "!" << endl;
        player[0].entityStatsmenu();
        player[0].getTotals();
    }
    else // if (player[1].getHp() <= 0 || playerWhoQuit == 1 || map.getMapPos(0) == 49)
    {
        map.printMap();
        cout << player[0].getName() << " wins!" << endl
             << endl;
        cout << "Winning stats of " << player[0].getName() << "!" << endl;
        player[0].entityStatsmenu();
        player[0].getTotals();
        cout << endl;
        cout << "Losing stats of " << player[1].getName() << "!" << endl;
        player[1].entityStatsmenu();
        player[1].getTotals();
    }
    // record player stats in "results.txt"
    ofstream file_out("textFiles/results.txt");
    for (int i = 0; i < 2; i++)
    {
        file_out << player[i].getName() << "  Health remaining: " << player[i].getHp() << "  Stamina remaining: " << player[i].getStam() << endl;
        file_out << "Defense: " << player[i].getDef() << "  Calamity chance: " << player[i].getCalamityChance() << endl;
        file_out << "Total gold earned: " << player[i].getTotalGold() << "  Total damage dealt: " << player[i].getTotalDamage() << "  Number of misses: " << player[i].getMisses() << endl;
        file_out << "Total damage taken: " << player[i].getTotalDamageTaken() << endl
                 << endl;
    }
    return 0;
}