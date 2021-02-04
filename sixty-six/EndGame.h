#pragma once
#include "Card.h"
#include "RulesClosed.h"
class EndGame
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

	pair<int, int> trickComputerFirst(int computerResult, int oponentResult);
	pair<int, int> trickComputerSecond(int computerResult, int oponentResult);
public:
	EndGame(Color trump, vector<Card> maxPlayerCards, vector<Card> minPlayerCards);
	int chooseCardFirstMove();
	int chooseCardSecondMove(Card firstCard);
	void play();
	void printCards();
};
