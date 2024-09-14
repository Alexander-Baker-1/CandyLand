#ifndef BOARD_H
#define BOARD_H
#include "CandyStore.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Player.h"
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

struct Tile
{
    string color;
    string tile_type;
};

struct SpecialTile
{
    string name;
    string description;
    int position;
};

struct Calamity
{
    string name;
    string description;
};

struct Card
{
    string color;
    string card_type;
};

struct Treasure
{
    string name;
    int position;
};

struct Riddle
{
    string question;
    string answer;
};

struct ScrambledWord
{
    string question;
    string answer;
};

class Board
{
    private:
        const static int _BOARD_SIZE = 83;
        Tile _tiles[_BOARD_SIZE];
        const static int _MAX_CANDY_STORE = 4;
        int _candy_store_position[_MAX_CANDY_STORE];
        CandyStore _candy_stores[_MAX_CANDY_STORE];
        int _candy_store_count = 1;
        int _player_position = 0;
        int _treasure_position[3];
        int _special_tile_position[4];

    public:
        Board();

        void resetBoard();
        void displayTile(int, vector<Player>);
        void displayBoard(vector<Player>);

        int getBoardSize() const;
        int getCandyStoreCount() const;

        bool addCandyStore(int);
        bool isPositionCandyStore(int);
        bool isPositionSpecialTile(int); 
        bool isPositionTreasure(int);
        int drawCard(Player);
        void placeStores(CandyStore[]);
        void placeSpecialTiles(SpecialTile[]);
        void placeTreasures(Treasure[]);
        vector<Riddle> loadRiddles(vector<Riddle>, string);
        bool giveRiddle(vector<Riddle>);
        vector<ScrambledWord> loadScrambledWords(vector<ScrambledWord>, string);
        bool giveScrambledWord(vector<ScrambledWord>);
};

#endif