#pragma once
#include<vector>
#include "Card.h"
class Player
{
private:
	Color trump;
public:
	virtual void printCards(vector<Card> maxCards) = 0;
	virtual int chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards, bool hasTrickMax, bool hasTrickMin) = 0;
	virtual int chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards, bool hasTrickMax, bool hasTrickMin) = 0;
};