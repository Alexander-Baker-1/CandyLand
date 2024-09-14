#include "CandyStore.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<ctime>

using namespace std;

CandyStore::CandyStore()
{
    Candy candy;
    _position = 0;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        _available_candy[i] = candy;
    }
}

CandyStore::CandyStore(Candy available_candy[_MAX_CANDY_AMOUNT], int position)
{
    _position = position;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        _available_candy[i] = available_candy[i];
    }
}



int CandyStore::getSection() const
{
    return _section;
}

int CandyStore::getPosition() const
{
    return _position;
}

void CandyStore::setSection(int section)
{
    _section = section;
}

void CandyStore::setPosition(int position)
{
    _position = position;
}



// fills stores with 3 random candies
void CandyStore::stockStore(vector<Candy> candy_stock)
{
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        int candy = rand() % 12;
        _available_candy[i] = candy_stock.at(candy);
    }
}

// prints out store's inventory
void CandyStore::displayStock()
{
    for (int i = 0; i < 3; i++)
    {
        cout << "Name: " << _available_candy[i].name << endl;
        cout << "Description: " << _available_candy[i].description << endl;
        cout << "Effect: " << _available_candy[i].effect_type << endl;
        cout << "Effect value: " << _available_candy[i].effect_value << endl;
        cout << "Candy type: " << _available_candy[i].candy_type << endl;
        cout << "Price: " << _available_candy[i].price << endl;
        if (i != 2)
        {
            cout << "------------------------------------------------" << endl;
        }
    }
    cout << endl;
    cout << endl;
}

// allows player to buy a candy from a candy store if they have enough gold and adds it into their inventory
bool CandyStore::buyCandy(string candy_name, Player& player, int candy_amount, double percent)
{
    string candy_sub;
    char choice;
    int length = candy_name.length();
    string temp;
    Candy candy, candy1;

    for (int i = 0; i < length; i++)
    {
        candy_name[i] = tolower(candy_name[i]);
    }

    for (int i = 0; i < 3; i++)
    {

        temp = _available_candy[i].name;

        for (int j = 0; j < (int)_available_candy[i].name.length(); j++)
        {
            _available_candy[i].name[j] = tolower(_available_candy[i].name[j]);
        }
        if (_available_candy[i].name == candy_name)
        {
            if (player.getGold() < (_available_candy[i].price * percent))
            {
                cout << "You do not have enough gold for this candy" << endl;
                return true;
            }
            if (candy_amount == 9)
            {
                cout << "You do not have sufficient space in the candy inventory. Would you like to substitute your candy with any existing candy?(y/n)" << endl;
                cin >> choice;
                while ((cin.fail()) || ((tolower(choice) != 'y') && (tolower(choice) != 'n')))
                {
                    cin.clear();
                    cout << "Invalid input." << endl;
                    cin >> choice;
                }
                if (choice == 'y')
                {
                    cout << "Which candy would you like to substitute?" << endl;
                    cin.ignore();
                    getline(cin, candy_sub);
                    candy = player.findCandy(candy_sub);
                    while (candy.name == "")
                    {
                        cout << "Candy not found." << endl;
                        getline(cin, candy_sub);
                        candy = player.findCandy(candy_sub);
                    }
                    player.removeCandy(candy_sub);
                
                    _available_candy[i].name = temp;
                    candy1 = _available_candy[i];
                    player.addCandy(candy1);
                    player.setGold(player.getGold() - (candy1.price * percent));

                    cout << "Here is your updated candy inventory:" << endl;
                    player.printInventory();
                    return true;
                }
                else if (choice == 'n')
                {
                    _available_candy[i].name = temp;
                    return true;
                }
            }
            else
            {
                player.addCandy(candy1);
                return true;
            }
        }
        else
        {
            _available_candy[i].name = temp;
        }
    }
    return false;
}