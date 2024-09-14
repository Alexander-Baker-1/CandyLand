#include<iostream>
#include "Player.h"
#include "CandyStore.h"
#include<vector>
#include<iomanip>
#include<fstream>

using namespace std;

Player::Player()
{
    _name = "";
    _stamina = 0;
    _gold = 0;
    _candy_amount = 0;
    _position = 0;
    _skipped = false;
    _repel = false;
    _skipped_for = -1;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        _inventory[i] = _candy;
    }
}

Player::Player(string name, Character character, int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE, int position, bool skipped, int skipped_for)
{
    _name = name;
    _character = character;
    _stamina = stamina;
    _gold = gold;
    _effect = effect;
    _candy_amount = 0;
    _position = position;
    _skipped = skipped;
    _skipped_for = skipped_for;
    for (int i = 0; i < CANDY_ARR_SIZE; i++)
    {
        if (candy_array[i].name != "")
        {
            _candy_amount++;
        }
        _inventory[i] = candy_array[i];
    } 
}



void Player::setName(string name)
{
    _name = name;
}

void Player::setStamina(int stamina)
{
    _stamina = stamina;
}

void Player::setGold(double gold)
{
    _gold = gold;
}

void Player::setEffect(string effect)
{
    _effect = effect;
}

void Player::setCandyAmount(int candy_amount)
{
    _candy_amount = candy_amount;
}

void Player::setCharacter(Character character)
{
    _character = character;
}

void Player::setPosition(int position)
{
    _position = position;
}

void Player::setSkipped(bool skipped)
{
    _skipped = skipped;
}

void Player::setRepel(bool repel)
{
    _repel = repel;
}

void Player::setSkippedFor(int skipped_for)
{
    _skipped_for = skipped_for;
}


string Player::getName() const
{
    return _name;
}

int Player::getStamina() const
{
    return _stamina;
}

double Player::getGold() const
{
    return _gold;
}

string Player::getEffect() const
{
    return _effect;
}

int Player::getCandyAmount() const
{
    return  _candy_amount;
}

Character Player::getCharacter() const
{
    return _character;
}

int Player::getPosition() const
{
    return _position;
}

bool Player::getSkipped() const
{
    return _skipped;
}

bool Player::getRepel() const
{
    return _repel;
}

int Player::getSkippedFor() const
{
    return _skipped_for;
}

Candy Player::getCandy(int i)
{
    return _inventory[i];
}



// prints the player's candy inventory
void Player::printInventory()
{
    int count = 0;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        if (_inventory[i].name == "")
        {
            cout << "[Empty]   ";
        }
        else
        {
            cout << "[" << _inventory[i].name << "]   ";
        }
        
        count++;

        if (count == 3)
        {
            cout << endl;
            count = 0;
        }
    }
}

// searches for and returns candy in player's inventory
Candy Player::findCandy(string candy_name)
{
    string temp;
    Candy empty;
    int length = candy_name.length();
    for (int i = 0; i < length; i++)
    {
        candy_name[i] = tolower(candy_name[i]);
    }

    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        temp = _inventory[i].name;
        length = candy_name.length();
        for (int j = 0; j < length; j++)
        {
            _inventory[i].name[j] = tolower(_inventory[i].name[j]);
        }
        if (_inventory[i].name == candy_name)
        {
            _inventory[i].name = temp;
            return _inventory[i];
        }
        _inventory[i].name = temp;
    }
    return empty;
}

// adds candy to player's inventory
bool Player::addCandy(Candy candy)
{
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        if (_inventory[i].name == "")
        {
            _inventory[i] = candy;
            _candy_amount++;
            return true;
        }
    }
    return false;
}

// removes candy from player's inventory
bool Player::removeCandy(string candy_name)
{
    int length = candy_name.length();
    string temp;
    for (int i = 0; i < length; i++)
    {
        candy_name[i] = tolower(candy_name[i]);
    }

    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        temp = _inventory[i].name;
        
        for (int k = 0; k < (int)_inventory[i].name.length(); k++)
        {
            _inventory[i].name[k] = tolower(_inventory[i].name[k]);
        }

        if (_inventory[i].name == candy_name)
        {
            Candy empty;
            _inventory[i] = empty;
            _candy_amount--;
            for (int j = i; j < _MAX_CANDY_AMOUNT; j++)
            {
                if (j == _MAX_CANDY_AMOUNT-1)
                {
                    _inventory[j] = empty;
                    return true;
                }
                _inventory[j] = _inventory[j+1];
                _inventory[j+1] = empty;

            }
            return true;
        }
        else
        {
            _inventory[i].name = temp;
        }
    }    
    return false;
}

// finds a type of candy in players's inventory
string Player::findCandyType(string type, int n)
{
    for (int i = n; i < _candy_amount; i++)
    {
        if (_inventory[i].candy_type == type)
        {
            return _inventory[i].name;
        }
    }
    return "";
}

// rock paper scissors minigame
bool playRockPaperScissors(Player player)
{
    bool selected = false, playing = true;
    char choice1, choice2;
    int random;

    while(playing)
    {
        cout << "Player: Enter r, p, or s" << endl;
        while (!selected)
        {
            cin >> choice1;
            if ((choice1 != 'r') && (choice1 != 'p') && (choice1 != 's'))
            {
                cout << "Invalid selection!" << endl;
                continue;
            }
            selected = true;
        }
        selected = false;

        cout << "Computer: Enter r, p, or s" << endl;
        random = rand() % 3;
        if (random == 0)
        {
            choice2 = 'r';
        }
        else if (random == 1)
        {
            choice2 = 'p';
        }
        else if (random == 2)
        {
            choice2 = 's';
        }
        else
        {
            cout << "Error" << endl;
        }
        cout << choice2 << endl;
        if (choice1 == choice2)
        {
            cout << "Tie! Play again" << endl;
        }
        else if ((choice1 == 'r' && choice2 == 's') || (choice1 == 'p' && choice2 == 'r') || (choice1 == 's' && choice2 == 'p'))
        {
            cout << "Player has won!" << endl;
            playing = false;
            return true;
        }
        else
        {
            cout << "Computer has won " << endl;
            playing = false;
            return false;
        }
    }
    return false;
}

// loads in candy from file and stores them in a vector of candies
vector<Candy> readCandy(string file_name, vector<Candy> candies)
{
    ifstream file;
    file.open(file_name);

    if(file.fail())
    {
        cout << "Failed to open file" << endl;
        return candies;
    }
    string line, candy;
    int length = line.length(), start = 0, counter = 0;
    getline(file, line);
    while (!file.eof())
    {
        getline(file, line);
        length = line.length();
        start = 0;
        counter = 0;
        Candy candy;
        if (length != 0)
        {   
            for (int i = 0; i < length; i++)
            {
                if ((i == length - 1) && (counter == 5))
                {
                    candy.price = stod(line.substr(start));
                    candies.push_back(candy);
                }
                
                else if((line[i] == '|') && (counter == 0))
                {
                    candy.name = line.substr(0, i);
                    start = i+1;
                    counter++;
                }
                else if((line[i] == '|') && (counter == 1))
                {
                    candy.description = line.substr(start, i-start);
                    start = i+1;
                    counter++;
                }
                else if((line[i] == '|') && (counter == 2))
                {
                    candy.effect_type = line.substr(start, i-start);
                    start = i+1;
                    counter++;
                }
                else if((line[i] == '|') && (counter == 3))
                {
                    candy.effect_value = stod(line.substr(start, i-start));
                    start = i+1;
                    counter++;
                }
                else if((line[i] == '|') && (counter == 4))
                {
                    candy.candy_type = line.substr(start, i-start);
                    start = i+1;
                    counter++;
                }
            }
        }
    }
    return candies;
}

// prints all candies
void printVector(vector<Candy> candies)
{

    for (int i = 0; i < (int)candies.size(); i++)
    {
        cout << fixed << setprecision(2) << "Name: " << candies.at(i).name << ". Description: " << candies.at(i).description << ". Price: " << candies.at(i).price << ". Type: " << candies.at(i).candy_type << endl; 
    }
}

// loads in characters from file and stores them in a vector of characters
vector<Character> readCharacters(string file_name, vector<Character> characters, vector<Candy> candies)
{
    ifstream file;
    file.open(file_name);

    if(file.fail())
    {
        cout << "Failed to open file" << endl;
        return characters;
    }
    string line, character;
    int length = line.length(), start = 0, counter = 0;
    getline(file, line);
    while (!file.eof())
    {
        getline(file, line);
        length = line.length();
        start = 0;
        counter = 0;
        int j = 0;
        Character character;
        if (length != 0)
        {   
            for (int i = 0; i < length; i++)
            {
                if (i == length - 1)
                {
                    for (int h = 0; h < (int)candies.size(); h++)
                    {
                        if (candies[h].name == line.substr(start))
                        {
                            character.candies[j] = candies[h];
                            j++;
                        }
                    }
                    characters.push_back(character);
                }
                else if ((line[i] == '|') && (counter == 0))
                {
                    character.name = line.substr(0, i);
                    start = i+1;
                    counter++;
                }
                else if ((line[i] == '|') && (counter == 1))
                {
                    character.stamina = stod(line.substr(start, i-start));
                    start = i+1;
                    counter++;
                }
                else if ((line[i] == '|') && (counter == 2))
                {
                    character.gold = stod(line.substr(start, i-start));
                    start = i+1;
                    counter++;
                }
               
                else if (line[i] == ',')
                {
                    for (int k = 0; k < (int)candies.size(); k++)
                    {
                        if (candies[k].name == line.substr(start, i-start))
                        {
                            character.candies[j] = candies[k];
                            j++;
                        }
                    }
                    start = i+1;
                }
            }
        }
    }
    return characters;
}

// prints all characters
void displayCharacters(vector<Character> characters)
{
    int count = 0;
    for (int i = 0; i < (int)characters.size(); i++)
    {
        cout << "Name: " << characters.at(i).name << endl;
        cout << "Stamina: " << characters.at(i).stamina << endl;
        cout << "Gold: " << characters.at(i).gold << endl;
        cout << "Candies:" << endl;
        for (int j = 0; j < 9; j++)
        {
            cout << "[" << characters.at(i).candies[j].name << "]" << "   ";
            count++;
            if (count == 3)
            {
                count = 0;
                cout << endl;
            }
        }
        cout << "------------------------------------------------" << endl;
    }
}

// searches for and returns character from character vector
Character findCharacter(string character_name, vector<Character> characters)
{
    int length = character_name.length();
    string temp;
    Character character;
    for (int i = 0; i < length; i++)
    {
        character_name[i] = tolower(character_name[i]);
    }

    for (int i = 0; i < (int)characters.size(); i++)
    {
        temp = characters.at(i).name;
        
        for (int k = 0; k < (int)characters.at(i).name.length(); k++)
        {
            characters.at(i).name[k] = tolower(characters.at(i).name[k]);
        }

        if (characters.at(i).name == character_name)
        {
            characters.at(i).name = temp;
            return characters.at(i);
        }
        else
        {
            characters.at(i).name = temp;
        }
    }    
    cout << "Character not found." << endl;
    return character;
}

// removes character from character vector
vector<Character> removeCharacter(string character_name, vector<Character> characters)
{
    int length = character_name.length();
    string temp;

    if (characters.size() == 1)
    {
        characters.erase(characters.begin());
        return characters;
    }

    for (int i = 0; i < length; i++)
    {
        character_name[i] = tolower(character_name[i]);
    }

    for (int i = 0; i < (int)characters.size(); i++)
    {
        temp = characters.at(i).name;
        for (int k = 0; k < (int)characters.at(i).name.size(); k++)
        {
            characters.at(i).name[k] = tolower(characters.at(i).name[k]);
        }
        if (characters.at(i).name == character_name)
        {
            characters.erase(characters.begin()+i);
            return characters;
        }
        else
        {
            characters.at(i).name = temp;
        }
    }    
    return characters;
}