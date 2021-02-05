#pragma once
#include "Card.h"
#include "RulesClosed.h"
class EndGamePlayer
{
private:
	Color trump;
	vector<Card> maxPlayerCards;
	vector<Card> minPlayerCards;
	RulesClosed rules;

	int maxFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints);
	int minFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints);

	int maxSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard);
	int minSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard);

public:
	EndGamePlayer(Color trump, vector<Card> maxPlayerCards, vector<Card> minPlayerCards);
	int chooseCardFirstMove();
	int chooseCardSecondMove(Card firstCard);
	
};
