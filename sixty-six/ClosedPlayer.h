#pragma once
#include "Player.h"
#include "EndGamePlayer.h"

class ClosedPlayer : public Player
{
private:
	Color trump;
	vector<Card> maxCards;
	int maxPoints; 
	int minPoints;
	bool hasTrickMax;
	bool hasTrickMin;
	Card firstCard;
	int cardsCallsTimes[6] = {0, 0, 0, 0, 0, 0};
	double cardCallsPoints[6] = { 0, 0, 0, 0, 0, 0 };
	void combinationUtil(vector<Card> arr, vector<Card> data,
		int start, int end,
		int index, int r, bool isComputerFirst);
	int getMax();

	int m = 0;
public:
	ClosedPlayer(Color trump);
	void printCards(vector<Card> maxCards);
	int chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin);
	int chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin);
};