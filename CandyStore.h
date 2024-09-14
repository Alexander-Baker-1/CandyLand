#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include "Player.h"
#include<vector>

class CandyStore
{
    private:
        const static int _MAX_CANDY_AMOUNT = 3;
        vector<Candy> _candy_stock;
        Candy _available_candy[_MAX_CANDY_AMOUNT];
        int _position;
        int _section;

    public:
        CandyStore();
        CandyStore(Candy[_MAX_CANDY_AMOUNT], int);
        void stockStore(vector<Candy>);
        void displayStock();
        bool buyCandy(string, Player&, int, double);

        int getSection() const;
        int getPosition() const;

        void setSection(int);
        void setPosition(int);
};

#endif