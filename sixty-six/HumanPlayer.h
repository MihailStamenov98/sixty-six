#pragma once
#include "Player.h"
#include "RulesClosed.h"
class HumanPlayer: public Player
{
private:
	Color trump;
	RulesClosed rules;

public:
	HumanPlayer(Color trump);
	void printCards(vector<Card> maxCards);
	int chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin);
	int chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin);
};
