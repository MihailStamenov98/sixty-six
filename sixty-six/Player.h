#pragma once
#include<vector>
#include "Card.h"
class Player
{
private:
	Color trump;
	vector<Card> maxPlayerCards;
public:
	virtual void printCards() = 0;
	virtual int chooseCardFirstMove() = 0;
	virtual int chooseCardSecondMove(Card firstCard) = 0;
};