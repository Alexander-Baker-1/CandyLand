#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<vector>

using namespace std;

struct Candy
{
    string name;
    string description;
    string effect_type;
    double effect_value; 
    string candy_type;
    double price;
    int position;
};

struct Character
{
    string name;
    double stamina;
    double gold;
    Candy candies[9];
};


class Player
{
    private:
        const static int _MAX_CANDY_AMOUNT = 9;
        string _name;
        double _stamina;
        double _gold;
        Candy _inventory[_MAX_CANDY_AMOUNT];
        string _effect;
        int	_candy_amount = 0;
        int _position = 0;
        Candy _candy;
        Character _character;
        bool _skipped = false;
        bool _repel = false;
        int _skipped_for = -1;

    public:
        Player();
        Player(string, Character, int, double, string, Candy[], const int, int, bool, int);

        void setName(string);
        void setStamina(int);
        void setGold(double);
        void setEffect(string);
        void setCandyAmount(int);
        void setCharacter(Character);
        void setPosition(int);
        void setSkipped(bool);
        void setRepel(bool);
        void setSkippedFor(int);

        string getName() const;
        int getStamina() const;
        double getGold() const;
        string getEffect() const;
        int getCandyAmount() const;
        Character getCharacter() const;
        int getPosition() const;
        bool getSkipped() const;
        bool getRepel() const;
        int getSkippedFor() const;

        void printInventory();
        Candy findCandy(string);
        bool addCandy(Candy);
        bool removeCandy(string);
        Candy getCandy(int);
        string findCandyType(string, int);
};

bool playRockPaperScissors(Player);

vector<Candy> readCandy(string, vector<Candy>);
void printVector(vector<Candy>);

vector<Character> readCharacters(string, vector<Character>, vector<Candy>);
void displayCharacters(vector<Character>);
Character findCharacter(string, vector<Character>);
vector<Character> removeCharacter(string, vector<Character>);

#endif