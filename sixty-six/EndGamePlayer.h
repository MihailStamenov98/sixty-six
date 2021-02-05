#pragma once
#include "Card.h"
#include "Player.h"
#include "RulesClosed.h"
class EndGamePlayer: public Player
{
private:
	Color trump;
	RulesClosed rules;

	int maxFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints);
	int minFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints);

	int maxSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard);
	int minSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard);

public:
	EndGamePlayer(Color trump);
	void printCards(vector<Card> maxCards);
	int chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards);
	int chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards);
	
};
