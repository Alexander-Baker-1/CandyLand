#include "Board.h"

Board::Board()
{
    resetBoard();
}

// resets board
void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 1;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player_position = 0;
}

// displays tile
void Board::displayTile(int position, vector<Player> players)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    for (int i = 0; i < (int)players.size(); i++)
    {
        if (position == players[i].getPosition())
        {
            cout << i+1;
            cout << " " << RESET;
            return;
        }

    }
    cout << " ";
    cout << " " << RESET;
}

// displays board
void Board::displayBoard(vector<Player> players)
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i, players);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i, players);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i, players);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i, players);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i, players);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

// adds candy store to array given the position
bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

// checks if a tile has a candy store on it
bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 1; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

// checks if tile is a special tile
bool Board::isPositionSpecialTile(int board_position)
{
    for (int i = 0; i < 4; i++)
    {
        //_special_tile_position[i];
        if(_special_tile_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

// checks if a tile has a treasure on it
bool Board::isPositionTreasure(int board_position)
{
    for (int i = 0; i < 3; i++)
    {
        if(_treasure_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

// allows player to pick a card
int Board::drawCard(Player player)
{
    Card card;
    int color_rand = rand() % 3+1;
    int type_rand = rand() % 99+1;
    int count = 0;

    switch (color_rand)
    {
        case 1:
        {
            card.color = MAGENTA;
            break;
        }
        case 2:
        {
            card.color = GREEN;
            break;
        }
        case 3:
        {
            card.color =  BLUE;
            break;
        }
        default:
        {
            cout << "Error" << endl;
        }
    }


    if ((type_rand >= 0) && (type_rand <= 70))
    {
        card.card_type = "Single";
    }
    else if ((type_rand > 70) && (type_rand <= 100))
    {
            card.card_type = "Double";
    }
    else
    {
        cout << "Error" << endl;
    }


    if (card.card_type == "Single")
    {
        if (card.color == MAGENTA)
        {
            cout << "You drew a Cotton Candy Magenta card. Your game piece advances to Magenta tile. Here's the updated trail:" << endl;
        }
        else if (card.color == GREEN)
        {
            cout << "You drew a Minty Green card. Your game piece advances to Green tile. Here's the updated trail:" << endl;
        }
        else if (card.color == BLUE)
        {
            cout << "You drew a Bubblegum Blue card. Your game piece advances to Blue tile. Here's the updated trail:" << endl;
        }

        for (int i = player.getPosition()+1; i < _BOARD_SIZE; i++)
        {
            if (_tiles[i].color == card.color)
            {
                return i;
            }
        }
        return -1;
    }

    else if (card.card_type == "Double")
    {
        if (card.color == MAGENTA)
        {
            cout << "You drew a double Cotton Candy Magenta card. Your game piece advances two Magenta tile. Here's the updated trail:" << endl;
        }
        else if (card.color == GREEN)
        {
            cout << "You drew a double Minty Green card. Your game piece advances two Green tile. Here's the updated trail:" << endl;
        }
        else if (card.color == BLUE)
        {
            cout << "You drew a double Bubblegum Blue card. Your game piece advances two Blue tile. Here's the updated trail:" << endl;
        }

        for (int i = player.getPosition()+1; i < _BOARD_SIZE; i++)
        {
            if (_tiles[i].color == card.color)
            {
                count++;
                if (count == 2)
                {
                    count = 0;
                    return i;
                }
            }
        }
        return -1;
    }

    return player.getPosition();
}

// places stores on board
void Board::placeStores(CandyStore stores[])
{
    int position = -1;
    stores[0].setSection(0);
    stores[0].setPosition(-2);
    stores[1].setSection(1);
    position = (rand() % 27) + 1;
    while (position % 3 != 0)
    {
        position = (rand() % 27) + 1;
    }
    stores[1].setPosition(position);
    addCandyStore(stores[1].getPosition());
    stores[2].setSection(2);
    position = -1;
    while (position % 3 != 1)
    {
        position = (rand() % (54 - 28 + 1)) + 28;
    }
    stores[2].setPosition(position);
    addCandyStore(stores[2].getPosition());
    stores[3].setSection(3);
    position = -1;
    while (position % 3 != 2)
    {
        position = (rand() % (81 - 55 + 1 )) + 55;
    }
    stores[3].setPosition(position);
    addCandyStore(stores[3].getPosition());

    for (int i = 1; i < 4; i++)
    {
        _candy_store_position[i] = stores[i].getPosition();
    }
    
    _candy_store_position[0] = -2;
}

// places special tiles on board
void Board::placeSpecialTiles(SpecialTile special_tiles[4])
{
    int random = 0, random1 = 0, random2 = 0;
    bool done = false, flag = false;
    SpecialTile special_tiles_available[4] = {{"Shortcut Tile", "Your spirits soar as you're propelled four tiles ahead, closing in on the Candy Castle."}, {"Ice Cream Stop Tile", "Congrats! You get a chance to draw a card again."}, {"Gumdrop Forest Tile", "Oops, You head back 4 tiles and lose "}, {"Gingerbread House Tile", "It's a bittersweet return to your previous location, accompanied by the forfeiture of one immunity candy."}};
    for (int i = 0; i < 4; i++)
    {
        random = (rand() % 101) + 1;
        if ((random >= 0) && (random <= 25))
        {
            random2 = 0;
        }
        else if ((random > 25) && (random <= 50))
        {
            random2 = 1;
        }
        else if ((random > 50) && (random <= 75))
        {
            random2 = 2;
        }
        else if ((random > 75) && (random <= 100))
        {
            random2 = 3;
        }
        special_tiles[i] = special_tiles_available[random2];
    }

    for (int i = 0; i < 4; i++)
    {
        done = false;
        flag = false;
        while (!done)
        {
            flag = false;
            random1 = (rand() % 81) + 1;
            for (int j = 0; j < 4; j++)
            {
                if ((random1 == _special_tile_position[j]) || (random1 == _candy_store_position[j]))
                {
                    flag = true;
                }
            }
            if (flag == true)
            {
                continue;
            }
            done = true;
        }
        _special_tile_position[i] = random1;
        special_tiles[i].position = random1;
    }
}

// places treasures on board
void Board::placeTreasures(Treasure treasures[3])
{
    int random = 0, random1 = 0;
    bool done = false, flag = false;
    string treasures_available[5] = {"Stamina Refill", "Gold Windfall", "Robber's repel", "Jellybean of Vigor", "Treasure Hunter's Truffle"};
    for (int i = 0; i < 3; i++)
    {
        random = rand() % 101;
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
            random = rand() % 101;
            if ((random >= 0) && (random <= 70))
            {
                random = 3;
            }
            else if ((random > 70) && (random <= 100))
            {
                random = 4;
            }
        }
        treasures[i].name = treasures_available[random];
    }

    for (int i = 0; i < 3; i++)
    {
        done = false;
        flag = false;
        while (!done)
        {
            flag = false;
            random1 = (rand() % 81) + 1;
            for (int j = 0; j < 3; j++)
            {
                if (random1 == _treasure_position[j])
                {
                    flag = true;
                }
            }
            for (int k = 0; k < 4; k++)
            {
                if ((random1 == _candy_store_position[k]) || (random1 == _special_tile_position[k]))
                {
                    flag = true;
                }
            }
            if (flag == true)
            {
                continue;
            }
            done = true;
        }
        _treasure_position[i] = random1;
        treasures[i].position = random1;
    }
}

// loads in riddles from file and stores them in a vector
vector<Riddle> Board::loadRiddles(vector<Riddle> riddles, string file_name)
{
    ifstream file;
    file.open(file_name);
    if(file.fail())
    {
        cout << "Failed to open file" << endl;
        return riddles;
    }
    string line, riddle;
    int length = line.length();
    while (!file.eof())
    {
        getline(file, line);
        length = line.length();
        Riddle riddle;
        if (length != 0)
        {   
            for (int i = 0; i < length; i++)
            {
              if(line[i] == '|')
                {
                    riddle.question = line.substr(0, i);
                    riddle.answer = line.substr(i+1);
                    riddles.push_back(riddle);
                    break;
                }
            }
        }
    }
    return riddles;
}

// gives the player a riddle and checks if they enter the right answer
bool Board::giveRiddle(vector<Riddle> riddles)
{
    string answer;
    int riddle = rand() % riddles.size();
    cout << riddles.at(riddle).question << endl;
    cout << "Enter answer: ";
    getline(cin, answer);
    if (answer == riddles.at(riddle).answer)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// loads in scrambled words from file and stores them in a vector
vector<ScrambledWord> Board::loadScrambledWords(vector<ScrambledWord> scrambled_words, string file_name)
{
    ifstream file;
    file.open(file_name);
    if(file.fail())
    {
        cout << "Failed to open file" << endl;
        return scrambled_words;
    }
    string line, riddle;
    int length = line.length();
    while (!file.eof())
    {
        getline(file, line);
        length = line.length();
        ScrambledWord word;
        if (length != 0)
        {   
            for (int i = 0; i < length; i++)
            {
              if(line[i] == '|')
                {
                    word.question = line.substr(0, i);
                    word.answer = line.substr(i+1);
                    scrambled_words.push_back(word);
                    break;
                }
            }
        }
    }
    return scrambled_words;
}

// gives the player a scrambled word and checks if they enter the right answer
bool Board::giveScrambledWord(vector<ScrambledWord> scrambled_words)
{
    string answer;
    int word = rand() % scrambled_words.size();
    cout << scrambled_words.at(word).question << endl;
    cout << "Enter answer: ";
    cin.ignore();
    getline(cin, answer);
    for (int i = 0; i < (int)answer.length(); i++)
    {
        answer[i] = tolower(answer[i]);
    }
    if (answer == scrambled_words.at(word).answer)
    {
        return true;
    }
    else
    {
        return false;
    }
}