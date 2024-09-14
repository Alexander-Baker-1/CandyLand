#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include "Player.h"
#include "Board.h"
#include "CandyStore.h"

using namespace std;

int main()
{
    srand(time(0));
    vector<Player> players;
    vector<Character> characters;
    vector<Candy> candies;
    CandyStore stores[4];
    Treasure treasures[3];
    SpecialTile special_tiles[4];
    vector<Riddle> riddles;
    vector<Candy> candies_on_board;
    vector<ScrambledWord> scrambled_words;
    Board board;
    string character_file = "characters.txt", candy_file = "candies.txt", riddle_file = "riddles.txt", scrambled_words_file = "scrambled_words.txt";
    
    // sets up game
    candies = readCandy(candy_file, candies);
    characters = readCharacters(character_file, characters, candies);
    Calamity calamities[4] = {{"Candy Bandits!", "Oh no! Candy Bandits have swiped your gold coins!"}, {"Lost in a Lollipop Labyrinth", "Oh dear! You got lost in the lollipop labyrinth!"}, {"Candy Avalanche!", "Watch out! A candy avalanche has struck!"}, {"Sticky Taffy Trap", "Oops! You are stuck in a sticky taffy trap!"}};
    int num_players = 0, choice1, position;
    string name, character_name = "", candy_name, num_players_string;
    char choice;   
    bool valid = false, valid1 = false, valid2 = false, playing = true, turn = true;
    Candy candy2;

    board.placeStores(stores);
    board.placeSpecialTiles(special_tiles);
    board.placeTreasures(treasures);
    riddles = board.loadRiddles(riddles, riddle_file);
    scrambled_words = board.loadScrambledWords(scrambled_words, scrambled_words_file);
    stores[0].setPosition(-2);
    for (int i = 0; i < 4; i++)
    {
        stores[i].stockStore(candies);
    }

    // sets up players
    cout << "Welcome to the game of candyland. Please enter the number of participants:" << endl;
    while (!valid2)
    {
        getline(cin, num_players_string);
        if ((!isdigit(num_players_string[0])) || (num_players_string.length() > 1))
        {
            cout << "Invalid input." << endl;
            cin.clear();
            continue;
        }
        num_players = stoi(num_players_string);
        if ((num_players < 2) || (num_players > 8))
        {
            cout << "A minimum of two players and a maximum of 8 players is required." << endl;
        }
        else
        {
            valid2 = true;
        }
    }
    
    for (int i = 0; i < num_players; i++)
    {
        cout << "Enter player name:" << endl;
        getline(cin, name);
        Player player;
        Character character;
        Candy candy, candy1, candy2;
        player.setName(name);
        cout << "Awesome! Here is a list of characters a player can select from:" << endl;
        displayCharacters(characters);
        cout << "The selected character is" << endl;
        while (character.name == "")
        {
            cin >> character_name;
            character = findCharacter(character_name, characters);
        }
        player.setCharacter(character);
        player.setStamina(character.stamina);
        player.setGold(character.gold);
        
        for (int j = 0; j < 9; j++)
        {
            candy = character.candies[j];
            player.addCandy(candy);
        }

        characters = removeCharacter(character_name, characters);
        cout << "Do you want to visit the candy store?(y/n)" << endl;
        cin >> choice;
        while ((cin.fail()) || ((tolower(choice) != 'y') && (tolower(choice) != 'n')))
        {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore();
            cin >> choice;
        }
        if (choice == 'y')
        {
            double percent = 1.00;
            cout << "Do you want to solve a puzzle to get a 10 percent discount?(y/n)" << endl;
            char choice1;
            cin >> choice1;
            while ((cin.fail()) || ((tolower(choice1) != 'y') && (tolower(choice1) != 'n')))
            {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore();
                cin >> choice1;
            }
            if (choice1 == 'y')
            {
                bool correct = board.giveScrambledWord(scrambled_words);
                if (correct == true)
                {
                    cout << "Congratulations! You get 10 percent off!" << endl;
                    percent = 0.9;
                }
                else
                {
                    cout << "Sorry that is not the correct answer! You have to pay 10 percent more!" << endl;
                    percent = 1.1;
                }
            }
            cout << "Here is a list of candies in the candy store:" << endl;
            stores[0].displayStock();
            cout << "Which candy would you like to buy?" << endl;
            getline(cin, candy_name);
            valid = stores[0].buyCandy(candy_name, player, player.getCandyAmount(), percent);
            while (!valid)
            {
                cout << "Candy not found." << endl;
                getline(cin, candy_name);
                valid = stores[0].buyCandy(candy_name, player, player.getCandyAmount(), percent);
            }
        }
        else
        {
            cin.ignore();
        }
        players.push_back(player);
    }

    // gameplay
    cout << "Let's begin the game. Here is the board:" << endl;
    board.displayBoard(players);
    while (playing)
    {
        for (int i = 0; i < num_players; i++)
        {
            turn = true;
            while (turn)
            {
                if (players.at(i).getSkippedFor() >= 0)
                {
                    cout << players.at(i).getName() << "'s turn was skipped." << endl;
                    players.at(i).setSkippedFor(players.at(i).getSkippedFor() - 1);
                    if (i == num_players - 1)
                    {
                        i = 0;
                    }
                    else
                    {
                        i++;
                    }
                }
                bool done = false;
                while (!done) {
                    if (players.at(i).getSkipped() == true)
                    {
                        cout << players.at(i).getName() << "'s turn was skipped." << endl;
                        if (players.at(i).getStamina() == 0)
                        {
                            players.at(i).setStamina(20);
                            turn = false;
                            done = true;
                            break;
                        }
                        else
                        {
                            players.at(i).setSkipped(false);
                            if (i == num_players - 1)
                            {
                                i = 0;
                            }
                            else
                            {
                                i++;
                            }
                        }
                    }
                    else
                    {
                        done = true;
                    }
                }
                // main menu
                valid1 = false;
                cout << "It's " << players.at(i).getName() << "'s turn" << endl;
                cout << "Please select a menu option:" << endl;
                cout << "1. Draw a card" << endl;
                cout << "2. Use candy" << endl;
                cout << "3. Show player stats" << endl;
                while (!valid1)
                {
                    cin >> choice1;
                    if (cin.fail())
                    {
                        cout << "Invalid input" << endl;
                        cin.clear();
                        cin.ignore();
                        continue;
                    }
                    switch (choice1)
                    {
                        // draw a card
                        case 1:
                        {
                            valid1 = true;
                            int old_position = players.at(i).getPosition();
                            position = board.drawCard(players.at(i));
                            players.at(i).setPosition(position);
                            players.at(i).setStamina(players.at(i).getStamina()-1);
                            board.displayBoard(players);

                            // checks if player lands on gummy candy
                            if (candies_on_board.size() != 0)
                            {
                                string number;
                                for (int j = 0; j < (int)candies_on_board.size(); j++)
                                {
                                    if (players.at(i).getPosition() == candies_on_board.at(j).position)
                                    {
                                        if (candies_on_board.at(j).effect_value == -1)
                                        {
                                            number = "one turn.";
                                        }
                                        else if (candies_on_board.at(j).effect_value == -2)
                                        {
                                            number = "two turns.";
                                        }
                                        cout << "You have landed on a gummy candy. You lose " << number << endl;
                                        players.at(i).setSkippedFor(abs(players.at(i).getSkippedFor() + 1 + candies_on_board.at(j).effect_value));
                                        candies_on_board.erase(candies_on_board.begin() + j);
                                    }
                                }
                            }

                            // checks if player lands on an occupied tile
                            bool done = false, done1 = false;
                            int random = 0;
                            while (!done1)
                            {
                                for (int j = 0; j < num_players; j++)
                                {
                                    if ((players.at(i).getPosition() == players.at(j).getPosition()) && (players.at(i).getCharacter().name != players.at(j).getCharacter().name))
                                    {
                                        if ((players.at(i).getGold() > 5) && (players.at(i).getRepel() == false))
                                        {
                                            while(!done)
                                            {
                                                random = rand() % (30 - 5 + 1) + 5;
                                                if (random <= players.at(i).getGold())
                                                {
                                                    players.at(j).setGold(players.at(j).getGold() + random);
                                                    if (players.at(j).getGold() > 100)
                                                    {
                                                        players.at(j).setGold(players.at(j).getGold() - (int(players.at(j).getGold()) % 100));
                                                    }
                                                    players.at(i).setGold(players.at(i).getGold() - random);
                                                    cout << players.at(j).getName() << " stole " << random << " gold from " << players.at(i).getName() << "! Here's the updated trail:" << endl;
                                                    board.displayBoard(players);
                                                    done = true;
                                                }
                                            }
                                        }
                                        else if (players.at(i).getGold() < 5) 
                                        {
                                            cout << players.at(i).getName() << " does not have enough gold to steal from. Here's the updated trail:" << endl;
                                            board.displayBoard(players);
                                            turn = false;
                                            done1 = true;
                                            break;
                                        }
                                        else if (players.at(i).getRepel() == true)
                                        {
                                            cout << players.at(i).getName() << " used Robber's repel to prevent their gold from being stolen!" << endl;
                                            players.at(i).removeCandy("Robber's repel");
                                            players.at(i).setRepel(false);
                                            players.at(j).setPosition(players.at(j).getPosition()-1);
                                            board.displayBoard(players);
                                            turn = false;
                                            done1 = true;
                                            break;
                                        }
                                    }
                                    done1 = true;
                                    turn = false;
                                    if (done == true)
                                    {
                                        break;
                                    }
                                }
                            }

                            // checks if player lands on tile with candystore
                            if (board.isPositionCandyStore(players.at(i).getPosition()) == true)
                            {
                                cout << "You landed on a tile which has a candy store." << endl;
                                cout << endl;
                                cout << "Do you want to visit the candy store?(y/n)" << endl;
                                cin >> choice;
                                while ((cin.fail()) || ((tolower(choice) != 'y') && (tolower(choice) != 'n')))
                                {
                                    cout << "Invalid input." << endl;
                                    cin.clear();
                                    cin.ignore();
                                    cin >> choice;
                                }
                                if (choice == 'y')
                                {
                                    double percent = 1.00;
                                    cout << "Do you want to solve a puzzle to get a 10 percent discount?(y/n)" << endl;
                                    char choice1;
                                    cin >> choice1;
                                    while ((cin.fail()) || ((tolower(choice1) != 'y') && (tolower(choice1) != 'n')))
                                    {
                                        cout << "Invalid input." << endl;
                                        cin.clear();
                                        cin.ignore();
                                        cin >> choice1;
                                    }
                                    if (choice1 == 'y')
                                    {
                                        bool correct = board.giveScrambledWord(scrambled_words);
                                        if (correct == true)
                                        {
                                            cout << "Congratulations! You get 10 percent off!" << endl;
                                            percent = 0.9;
                                        }
                                        else
                                        {
                                            cout << "Sorry that is not the correct answer! You have to pay 10 percent more!" << endl;
                                            percent = 1.1;
                                        }
                                    }
                                    for (int j = 1; j < 4; j++)
                                    {
                                        if (players.at(i).getPosition() == stores[j].getPosition())
                                        {
                                            cout << "Here is a list of candies in the candy store:" << endl;
                                            stores[j].displayStock();
                                            cout << "Which candy would you like to buy?" << endl;
                                            getline(cin, candy_name);
                                            valid = stores[j].buyCandy(candy_name, players.at(i), players.at(i).getCandyAmount(), percent);
                                            while (!valid)
                                            {
                                                cout << "Candy not found." << endl;
                                                getline(cin, candy_name);
                                                valid = stores[j].buyCandy(candy_name, players.at(i), players.at(i).getCandyAmount(), percent);
                                            }
                                        }
                                    }
                                }
                                turn = false; 
                            }

                            // checks if player lands on special tile
                            else if (board.isPositionSpecialTile(players.at(i).getPosition()) == true)
                            {
                                for (int j = 0; j < 4; j++)
                                {
                                    string old_description = special_tiles[j].description;
                                    if (players.at(i).getPosition() == special_tiles[j].position)
                                    {
                                        if (special_tiles[j].name == "Shortcut Tile")
                                        {
                                            if (players.at(i).getPosition() + 4 >= 81)
                                            {
                                                players.at(i).setPosition(-1);
                                            }
                                            else
                                            {
                                                players.at(i).setPosition(players.at(i).getPosition() + 4);
                                            }
                                            turn = false;
                                        }
                                        else if (special_tiles[j].name == "Ice Cream Stop Tile")
                                        {
                                            turn = true;
                                            cout << players.at(i).getName() << " has landed on a " << special_tiles[j].name << ". " << special_tiles[j].description << endl;
                                            special_tiles[j].description =  old_description;
                                            if (i == 0)
                                            {
                                                i = num_players-1;
                                            }
                                            else
                                            {
                                                i--;
                                            }
                                            break;
                                        }
                                        else if (special_tiles[j].name == "Gumdrop Forest Tile")
                                        {
                                            int random1 = 0;
                                            if (players.at(i).getPosition() - 4 < 0)
                                            {
                                                players.at(i).setPosition(0);
                                            }
                                            else
                                            {
                                                players.at(i).setPosition(players.at(i).getPosition() - 4);
                                            }

                                            if (players.at(i).getGold() < 5)
                                            {
                                                random1 = 0;
                                            }
                                            else
                                            {
                                                random1 = (rand() % 6) + 5;
                                                while (players.at(i).getGold() - random1 < 0)
                                                {
                                                    random1 = (rand() % 6) + 5;
                                                }
                                                players.at(i).setGold(players.at(i).getGold() - random1);
                                            }
                                            special_tiles[j].description += (to_string(random1) + " gold.");
                                            turn = false;
                                        }
                                        else if (special_tiles[j].name == "Gingerbread House Tile")
                                        {
                                            players.at(i).setPosition(old_position);
                                            for (int j = 0; j < players.at(i).getCandyAmount(); j++)
                                            {
                                                string immunity = players.at(i).findCandyType("immunity", 0);
                                                if (immunity != "")
                                                {
                                                    players.at(i).removeCandy(immunity);
                                                    turn = false;
                                                    break;
                                                }
                                                turn = false;
                                            }
                                        }
                                        cout << players.at(i).getName() << " has landed on a " << special_tiles[j].name << ". " << special_tiles[j].description << endl;
                                        special_tiles[j].description =  old_description;
                                        if (special_tiles[j].name == "Gingerbread House Tile")
                                        {
                                            cout << "Here is your updated candy inventory:" << endl;
                                            players.at(i).printInventory(); 
                                            turn = false;
                                        }
                                        board.displayBoard(players);
                                    }
                                }
                                turn = false;
                            }

                            // checks if player lands on tile with treasure
                            else if (board.isPositionTreasure(players.at(i).getPosition()) == true)
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    if (players.at(i).getPosition() == treasures[j].position)
                                    {
                                        cout << players.at(i).getName() << " has landed on a hidden treasure! Solve this riddle to claim your treasure: " << endl;
                                        cin.ignore();
                                        bool solved = board.giveRiddle(riddles);

                                        if (solved == true)
                                        {
                                            cout << players.at(i).getName() << " has recieved " << treasures[j].name << "!" << endl;
                                            if (treasures[j].name == "Treasure Hunter's Truffle")
                                            {

                                                Candy Treasure = {"Treasure Hunter's Truffle", "Allows the player to unlock a hidden treasure.", "gold", 0, "special", 0};
                                                if (players.at(i).getCandyAmount() == 9)
                                                {
                                                    string candy_sub = "";
                                                    char choice2;
                                                    cout << "You do not have sufficient space in the candy inventory. Would you like to substitute your candy with any existing candy?(y/n)" << endl;
                                                    cin >> choice2;
                                                    while ((cin.fail()) || ((tolower(choice2) != 'y') && (tolower(choice2) != 'n')))
                                                    {
                                                        cout << "Invalid input." << endl;
                                                        cin.clear();
                                                        cin.ignore();
                                                        cin >> choice2;
                                                    }
                                                    if (choice2 == 'y')
                                                    {
                                                        cout << "Which candy would you like to substitute?" << endl;
                                                        cin.ignore();
                                                        getline(cin, candy_sub);
                                                        Candy candy3 = players.at(i).findCandy(candy_sub), candy4;
                                                        while (candy3.name == "")
                                                        {
                                                            cout << "Candy not found." << endl;
                                                            getline(cin, candy_sub);
                                                            candy4 = players.at(i).findCandy(candy_sub);
                                                        }
                                                        players.at(i).removeCandy(candy_sub);
                                                        players.at(i).addCandy(Treasure);

                                                        cout << "Here is your updated candy inventory:" << endl;
                                                        players.at(i).printInventory();
                                                    }
                                                }
                                                else
                                                {
                                                    players.at(i).addCandy(Treasure);
                                                }
                                                turn = false; 
                                            }
                                            if (treasures[j].name == "Stamina Refill")
                                            {
                                                if (players.at(i).getStamina() <= 90)
                                                {
                                                    int stamina = 0;
                                                    while ((stamina + players.at(i).getStamina() > 100) || (stamina == 0))
                                                    {
                                                        stamina = rand() % (30 - 10 + 1) + 10;
                                                    }
                                                    players.at(i).setStamina(players.at(i).getStamina() + stamina);
                                                    cout << players.at(i).getName() << " has recieved " << stamina << " stamina!" << endl;
                                                    turn = false;
                                                }
                                                else
                                                {
                                                    cout << players.at(i).getName() << " already has " << players.at(i).getStamina() << " stamina." << endl;
                                                    turn = false;
                                                }
                                            }
                                            else if (treasures[j].name == "Gold Windfall")
                                            {
                                                if (players.at(i).getGold() <= 80)
                                                {
                                                    int gold = 0;
                                                    while ((gold + players.at(i).getGold() > 100) || (gold == 0))
                                                    {
                                                        gold = rand() % (40 - 20 + 1) + 20;
                                                    }
                                                    players.at(i).setGold(players.at(i).getGold() + gold);
                                                    cout << players.at(i).getName() << " has recieved " << gold << " gold!" << endl;
                                                    turn = false;
                                                }
                                                else
                                                {
                                                    cout << players.at(i).getName() << " already has " << players.at(i).getGold() << " gold." << endl;
                                                    turn = false;
                                                }
                                            }
                                            else if (treasures[j].name == "Robber's repel")
                                            {
                                                Candy Repel = {"Robber's repel", "Acts as an anti-robbery shield.", "immunity", 0, "special", 0};
                                                if (players.at(i).getCandyAmount() == 9)
                                                {
                                                    string candy_sub = "";
                                                    char choice2;
                                                    cout << "You do not have sufficient space in the candy inventory. Would you like to substitute your candy with any existing candy?(y/n)" << endl;
                                                    cin >> choice2;
                                                    while ((cin.fail()) || ((tolower(choice2) != 'y') && (tolower(choice2) != 'n')))
                                                    {
                                                        cout << "Invalid input." << endl;
                                                        cin.clear();
                                                        cin.ignore();
                                                        cin >> choice2;
                                                    }
                                                    if (choice2 == 'y')
                                                    {
                                                        cout << "Which candy would you like to substitute?" << endl;
                                                        cin.ignore();
                                                        getline(cin, candy_sub);
                                                        Candy candy3 = players.at(i).findCandy(candy_sub), candy4;
                                                        while (candy3.name == "")
                                                        {
                                                            cout << "Candy not found." << endl;
                                                            getline(cin, candy_sub);
                                                            candy4 = players.at(i).findCandy(candy_sub);
                                                        }
                                                        players.at(i).removeCandy(candy_sub);
                                                        players.at(i).addCandy(Repel);
                                                        players.at(i).setRepel(true);

                                                        cout << "Here is your updated candy inventory:" << endl;
                                                        players.at(i).printInventory();
                                                        turn = false;
                                                    }
                                                }
                                                else
                                                {
                                                    players.at(i).addCandy(Repel);
                                                    players.at(i).setRepel(true);
                                                    turn = false;
                                                }
                                            }
                                            else if (treasures[j].name == "Jellybean of Vigor")
                                            {
                                                Candy Jelly = {"Jellybean of Vigor", "Restores 50 units of stamina.", "stamina", 50, "special", 0};
                                                if (players.at(i).getCandyAmount() == 9)
                                                {
                                                    string candy_sub = "";
                                                    char choice2;
                                                    cout << "You do not have sufficient space in the candy inventory. Would you like to substitute your candy with any existing candy?(y/n)" << endl;
                                                    cin >> choice2;
                                                    while ((cin.fail()) || ((tolower(choice2) != 'y') && (tolower(choice2) != 'n')))
                                                    {
                                                        cout << "Invalid input." << endl;
                                                        cin.clear();
                                                        cin.ignore();
                                                        cin >> choice2;
                                                    }
                                                    if (choice2 == 'y')
                                                    {
                                                        cout << "Which candy would you like to substitute?" << endl;
                                                        cin.ignore();
                                                        getline(cin, candy_sub);
                                                        Candy candy3 = players.at(i).findCandy(candy_sub), candy4;
                                                        while (candy3.name == "")
                                                        {
                                                            cout << "Candy not found." << endl;
                                                            getline(cin, candy_sub);
                                                            candy4 = players.at(i).findCandy(candy_sub);
                                                        }
                                                        players.at(i).removeCandy(candy_sub);
                                                        players.at(i).addCandy(Jelly);

                                                        cout << "Here is your updated candy inventory:" << endl;
                                                        players.at(i).printInventory();
                                                    }
                                                }
                                                else
                                                {
                                                    players.at(i).addCandy(Jelly);
                                                }
                                                turn = false; 
                                            }                                         
                                        }
                                        else
                                        {
                                            cout << "Sorry that is not the correct answer!" << endl;
                                            turn = false;
                                        }
                                    }
                                }
                            }

                            // checks if player gets a calamity
                            else
                            {
                                int random = 0, random1 = 0, random2 = 0;
                                random = rand() % 101;
                                if ((random >= 0) && (random < 40))
                                {
                                    random1 = rand() % 101;
                                    if ((random1 >= 0) && (random1 <= 30))
                                    {
                                        cout << calamities[0].description << endl;
                                        if (players.at(i).getGold() != 0)
                                        {
                                            random2 = (rand() % 10) + 1;
                                            cout << players.at(i).getName() << " has lost " << random2 << " gold." << endl;
                                            players.at(i).setGold(players.at(i).getGold() - random2);
                                        }
                                    }
                                    else if ((random1 > 30) && (random1 <= 65))
                                    {
                                        cout << calamities[1].description << endl;
                                        cout << "You can recover the damage by playing Rock, Paper, Scissors. If you win, you get your lost turn back." << endl;
                                        bool won = playRockPaperScissors(players.at(i));
                                        if (won == false)
                                        {
                                            cout << players.at(i).getName() << " has lost a turn." << endl;
                                            players.at(i).setSkipped(true);
                                        }
                                        else
                                        {
                                            cout << players.at(i).getName() << " has won their turn back!" << endl;
                                        }
                                    }
                                    else if ((random1 > 65) && (random1 <= 80))
                                    {
                                        if (players.at(i).getStamina() == 0)
                                        {
                                            random2 = 0;
                                        }
                                        else
                                        {
                                            random2 = (rand() % 10) + 1;
                                            while (players.at(i).getStamina() - random2 < 0)
                                            {
                                                random2 = (rand() % 10) + 1;
                                            }
                                        }
                                        
                                        cout << calamities[2].description << endl;
                                        cout << "You can recover the damage by playing Rock, Paper, Scissors. If you win, you get your lost turn and stamina back." << endl;
                                        bool won = playRockPaperScissors(players.at(i));
                                        if (won == false)
                                        {
                                            cout << players.at(i).getName() << " has lost a turn and " << random2 << " stamina." << endl;
                                            players.at(i).setStamina(players.at(i).getStamina() - random2);
                                            players.at(i).setSkipped(true);
                                        }
                                        else
                                        {
                                            cout << players.at(i).getName() << " has won their turn and " << random2 << " stamina back!" << endl;
                                        }
                                    }
                                    else if ((random1 > 80) || (random1 <= 100))
                                    {
                                        cout << calamities[3].description << endl;
                                        for (int j = 0; j < players.at(i).getCandyAmount(); j++)
                                        {
                                            string magical = players.at(i).findCandyType("magical", 0);
                                            if (magical != "")
                                            {
                                                cout << "Would you like to use a Magical Candy in your inventory to regain your lost turn?(y/n)" << endl;
                                                char choice1;
                                                cin >> choice1;
                                                while ((cin.fail()) || ((tolower(choice) != 'y') && (tolower(choice) != 'n')))
                                                {
                                                    cout << "Invalid input." << endl;
                                                    cin.clear();
                                                    cin.ignore();
                                                    cin >> choice1;
                                                }
                                                if (choice1 == 'y')
                                                {
                                                    cout << "Which candy would you like to use?" << endl;
                                                    cin.ignore();
                                                    string candy_sub;
                                                    Candy candy3;
                                                    getline(cin, candy_sub);
                                                    candy3 = players.at(i).findCandy(candy_sub);
                                                    while (candy3.name == "" || candy3.candy_type != "magical")
                                                    {
                                                        cout << "Candy not found or candy is not a Magical Candy." << endl;
                                                        getline(cin, candy_sub);
                                                        candy3 = players.at(i).findCandy(candy_sub);
                                                    }
                                                    players.at(i).removeCandy(candy_sub);
                                                    cout << "Here is your updated candy inventory:" << endl;
                                                    players.at(i).printInventory();
                                                    break;
                                                }
                                                else if (choice1 == 'n')
                                                {
                                                    cout << players.at(i).getName() << " has lost a turn." << endl;
                                                    players.at(i).setSkipped(true);
                                                    cin.ignore();
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                cout << players.at(i).getName() << " has lost a turn." << endl;
                                                players.at(i).setSkipped(true);
                                                turn = false;
                                                break;
                                            }
                                            turn = false;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Error" << endl;
                                    }
                                }
                            }

                            // checks if there is a marshmallow hailstorm
                            int storm = rand() % 101;
                            if ((storm >= 0) && (storm <= 5))
                            {
                                int places = (rand() % 6) + 5;
                                for (int j = 0; j < num_players; j++)
                                {
                                    if (players.at(j).getPosition() - places < 0)
                                    {
                                        players.at(j).setPosition(0);
                                    }
                                    else
                                    {
                                        players.at(j).setPosition(players.at(j).getPosition() - places);
                                    }
                                }
                                cout << "Oh no! There has been a Marshmallow Hailstorm! Each player gets pushed back by " << places << " tiles!" << endl;
                                board.displayBoard(players);
                            }


                            // winning condition
                            if (position == -1)
                            {
                                // prints out end of game statistics to terminal
                                cout << players.at(i).getName() << " has won!" << endl;
                                cout << "End of Game Statistics:" << endl;
                                for (int j = 0; j < num_players; j++)
                                {
                                    cout << "Player name: " << players.at(j).getName() << endl;
                                    cout << "Character: " << players.at(j).getCharacter().name << endl;
                                    cout << "Stamina: " << players.at(j).getStamina() << endl;
                                    
                                    cout << "Gold: " << players.at(j).getGold() << endl;
                                    cout << "Candies:" << endl;
                                    players.at(j).printInventory();
                                }
                                // saves results to file
                                ofstream file;
                                file.open("results.txt");
                                if (file.fail())
                                {
                                    cout << "Failed to open file" << endl;
                                    return 0;
                                }
                                file << players.at(i).getName() << " has won!" << endl;
                                file << "End of Game Statistics:" << endl;
                                for (int k = 0; k < num_players; k++)
                                {
                                    file << "Player name: " << players.at(k).getName() << endl;
                                    file << "Character: " << players.at(k).getCharacter().name << endl;
                                    file << "Stamina: " << players.at(k).getStamina() << endl;
                                    file << "Gold: " << players.at(k).getGold() << endl;
                                    file << "Candies:" << endl;
                                    int count = 0;
                                    for (int j = 0; j < 9; j++)
                                    {
                                        candy2 = players.at(k).getCandy(j);
                                        if (candy2.name == "")
                                        {
                                            file << "[Empty]";
                                        }
                                        else
                                        {
                                            file << "[" << candy2.name << "]   ";
                                        }
                                        
                                        count++;

                                        if (count == 3)
                                        {
                                            file << endl;
                                            count = 0;
                                        }
                                    }
                                }
                                return 0;
                            }

                            break;
                        }
                        // use a candy
                        case 2:
                        {
                            valid1 = true;
                            bool valid2 = false;
                            // checks if player has candies to use
                            for (int j = 0; j < players.at(i).getCandyAmount(); j++)
                            {
                                if ((players.at(i).findCandyType("magic", 0) != "") || (players.at(i).findCandyType("poison", 0) != "") || (players.at(i).findCandyType("gummy", 0) != "") || (players.at(i).findCandy("Treasure Hunter's Truffle").name != "Treasure Hunter's Truffle"))
                                {
                                    valid2 = true;
                                }
                            }

                            if ((players.at(i).getCandyAmount() == 0) || (valid2 == false))
                            {
                                cout << "You do not have any candies to use." << endl;
                                break;
                            }
                            else
                            {
                                // allows used to pick candy to use
                                cout << "Here is a list of your candies." << endl;
                                players.at(i).printInventory();      
                                cout << "Enter a candy you wish to use:" << endl; 
                                cin.ignore();
                                string candy_name = "";
                                Candy candy_use;
                                getline(cin, candy_name);
                                candy_use = players.at(i).findCandy(candy_name);
                                while ((candy_use.name == "") || (candy_use.candy_type == "immunity") || (candy_use.name == "Robber's repel"))
                                {
                                    cout << "Candy not found or candy cannot be used." << endl;
                                    getline(cin, candy_name);
                                    candy_use = players.at(i).findCandy(candy_name);
                                }

                                // magical candy
                                if (candy_use.candy_type == "magical")
                                {
                                    if (players.at(i).getStamina() + candy_use.effect_value > 100)
                                    {
                                        players.at(i).setStamina(100);
                                    }
                                    else
                                    {
                                        players.at(i).setStamina(players.at(i).getStamina() + candy_use.effect_value);
                                    }
                                    cout << "You have used " << candy_use.name << " candy. This has increased your stamina by " << candy_use.effect_value << " points." << endl;
                                }

                                // poison candy
                                else if (candy_use.candy_type == "poison")
                                {
                                    cout << "Which player would you like to use " << candy_use.name << " on?" << endl; int tile = 0;
                                    int player = -1;
                                    cin >> player;
                                    player--;
                                    while ((cin.fail() || (player < 0) || (player > num_players - 1)))
                                    {
                                        cout << "Invalid input." << endl;
                                        cin.clear();
                                        cin.ignore();
                                        cin >> tile;
                                    }
                                    string candy_name = "";
                                    Candy candy;
                                    for (int i = 0; i < players.at(player).getCandyAmount(); i++)
                                    {
                                        int n = i;
                                        candy_name = players.at(player).findCandyType("immunity", n);
                                        if (candy_name != "")
                                        {
                                            candy = players.at(player).findCandy(candy_name);
                                            if (candy.effect_value == 3)
                                            {
                                                break;
                                            }
                                            else if (candy.effect_value == 2)
                                            {
                                                if ((candy_use.effect_value == -15) || (candy_use.effect_value == -10))
                                                {
                                                    break;
                                                }
                                            }
                                            else if (candy.effect_value == 1)
                                            {
                                               if (candy_use.effect_value == 10)
                                                {
                                                    break;
                                                } 
                                            }
                                        }
                                    }
                                    if (candy_name != "")
                                    {
                                        cout << "You have used " << candy_use.name << " candy but your opponent has " << candy_name << " candy to protect against your poison candy." << endl;
                                        
                                        players.at(player).removeCandy(candy_name);
                                        players.at(i).removeCandy(candy_use.name);
                                        turn = false;
                                    }
                                    else
                                    {
                                        if (players.at(player).getStamina() - abs(candy_use.effect_value) < 0)
                                        {
                                            players.at(player).setStamina(0);
                                        }
                                        else
                                        {
                                            players.at(player).setStamina(players.at(player).getStamina() - abs(candy_use.effect_value));
                                        }
                                        players.at(i).removeCandy(candy_use.name);
                                        cout << "You have successfully used poison candy on " << players.at(player).getName() << ". They lose " << abs(candy_use.effect_value) << " stamina." << endl;
                                    }
                                }

                                // gummy candy
                                else if (candy_use.candy_type == "gummy")
                                {
                                    cout << "On which tile do you want to place your " << candy_use.name << " - gummy candy?" << endl;
                                    int tile = -2;
                                    cin >> tile;
                                    tile--;
                                    while ((cin.fail() || (tile < 0) || (tile > 82)))
                                    {
                                        cout << "Invalid input." << endl;
                                        cin.clear();
                                        cin.ignore();
                                        cin >> tile;
                                    }
                                    
                                    candy_use.position = tile;
                                    candies_on_board.push_back(candy_use);

                                    string number;
                                    if (candy_use.effect_value == -1)
                                    {
                                        number = "one move.";
                                    }
                                    else if (candy_use.effect_value == -2)
                                    {
                                        number = "two moves.";
                                    }
                                    cout << "You have successfully placed gummy candy on tile " << tile + 1 << ". Any player that lands on the gummy tile will be obstructed from advancing past the tile for " << number << endl;
                                }

                                if (candy_use.name == "Treasure Hunter's Truffle")
                                {
                                    string treasure_name = "";
                                    string treasures_available[4] = {"Stamina Refill", "Gold Windfall", "Robber's repel", "Jellybean of Vigor"};
                                    cout << "Solve this riddle to claim your treasure: " << endl;
                                    bool solved = board.giveRiddle(riddles);

                                    if (solved == true)
                                    {
                                        int random = rand() % 101;
                                        if ((random >= 0) && (random <= 30))
                                        {
                                            random = 0;
                                        }
                                        else if ((random > 30) && (random <= 40))
                                        {
                                            random = 1;
                                        }
                                        else if ((random > 40) && (random <= 70))
                                        {
                                            random = 2;
                                        }
                                        else if ((random > 70) && (random <= 100))
                                        { 
                                            random = 3;
                                        }
                                        treasure_name = treasures_available[random];
                                        cout << players.at(i).getName() << " has recieved " << treasure_name << "!" << endl;
                                    }
                                    else
                                    {
                                        cout << "Sorry that is not the correct answer!" << endl;
                                        turn = false;
                                    }

                                    if (treasure_name == "Stamina Refill")
                                    {
                                        if (players.at(i).getStamina() <= 90)
                                        {
                                            int stamina = 0;
                                            while ((stamina + players.at(i).getStamina() > 100) || (stamina == 0))
                                            {
                                                stamina = rand() % (30 - 10 + 1) + 10;
                                            }
                                            players.at(i).setStamina(players.at(i).getStamina() + stamina);
                                            cout << players.at(i).getName() << " has recieved " << stamina << " stamina!" << endl;
                                            
                                            players.at(i).removeCandy("Treasure Hunter's Truffle");
                                            cout << "Here is your updated candy inventory:" << endl;
                                            players.at(i).printInventory();
                                            turn = false; 
                                        }
                                        else
                                        {
                                            cout << players.at(i).getName() << " already has " << players.at(i).getStamina() << " stamina." << endl;
                                            players.at(i).removeCandy("Treasure Hunter's Truffle");
                                            cout << "Here is your updated candy inventory:" << endl;
                                            players.at(i).printInventory();
                                            turn = false;
                                        }
                                    }
                                    else if (treasure_name == "Gold Windfall")
                                    {
                                        if (players.at(i).getGold() <= 80)
                                        {
                                            int gold = 0;
                                            while ((gold + players.at(i).getGold() > 100) || (gold == 0))
                                            {
                                                gold = rand() % (40 - 20 + 1) + 20;
                                            }
                                            players.at(i).setGold(players.at(i).getGold() + gold);
                                            cout << players.at(i).getName() << " has recieved " << gold << " gold!" << endl;
                                            
                                            players.at(i).removeCandy("Treasure Hunter's Truffle");
                                            cout << "Here is your updated candy inventory:" << endl;
                                            players.at(i).printInventory();
                                            turn = false; 
                                        }
                                        else
                                        {
                                            cout << players.at(i).getName() << " already has " << players.at(i).getGold() << " gold." << endl;
                                            players.at(i).removeCandy("Treasure Hunter's Truffle");
                                            cout << "Here is your updated candy inventory:" << endl;
                                            players.at(i).printInventory();
                                            turn = false;
                                        }
                                    }
                                    else if (treasure_name == "Robber's repel")
                                    {
                                        Candy Repel = {"Robber's repel", "Acts as an anti-robbery shield.", "immunity", 0, "special", 0};
                                        players.at(i).removeCandy("Treasure Hunter's Truffle");
                                        players.at(i).addCandy(Repel);
                                        players.at(i).setRepel(true);

                                        cout << "Here is your updated candy inventory:" << endl;
                                        players.at(i).printInventory();
                                        turn = false;
                                    }
                                    else if (treasure_name == "Jellybean of Vigor")
                                    {
                                        Candy Jelly = {"Jellybean of Vigor", "Restores 50 units of stamina.", "stamina", 50, "special", 0};
                                        players.at(i).removeCandy("Treasure Hunter's Truffle");
                                        players.at(i).addCandy(Jelly);

                                        cout << "Here is your updated candy inventory:" << endl;
                                        players.at(i).printInventory();
                                        turn = false;
                                    }                                         

                                }
                            }
                            turn = false;
                            break;
                        }
                        // display stats
                        case 3:
                        {
                            valid1 = true;
                            cout << "Here are your stats:" << endl;
                            cout << "Player name: " << players.at(i).getName() << endl;
                            cout << "Character: " << players.at(i).getCharacter().name << endl;
                            cout << "Stamina: " << players.at(i).getStamina() << endl;
                            cout << "Gold: " << players.at(i).getGold() << endl;
                            cout << "Candies:" << endl;
                            players.at(i).printInventory();
                            break;
                        }
                        default:
                        {
                            cout << "Invalid choice" << endl;
                        }
                    }
                }
            }  
        }
    }
    return 0;
}