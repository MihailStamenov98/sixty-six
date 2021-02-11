#pragma once
#include "Card.h"
#include "Player.h"
#include "RulesClosed.h"
class EndGamePlayer: public Player
{
private:
	Color trump;
	RulesClosed rules;
	
	int maxSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard, bool hasTrickMax, bool hasTrickMin);
	int minSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard, bool hasTrickMax, bool hasTrickMin);
	int getGameValue(int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin);
	int suitAnnouncements(Color trump, vector<Card> Cards, Card playedCard);
public:
	EndGamePlayer(Color trump);
	int maxFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin);
	int minFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin);

	void printCards(vector<Card> maxCards);
	int chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin);
	int chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin);
	
};
