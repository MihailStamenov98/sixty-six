#pragma once
#include "EndGamePlayer.h"
#include "MonteCarloPLayer.h"
class ComputerPlayer: public Player
{
public:
	
	ComputerPlayer(Color trump);

	//void setInfoForGame(int myPoints, int oponentPoints);

	void printCards(vector<Card> maxCards);
	int chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards, int myPoints, int oponentPoints, bool hasTrickMax, bool hasTrickMin);
	int chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards, int myPoints, int oponentPoints, bool hasTrickMax, bool hasTrickMin);

private:

	EndGamePlayer endPlayer;
	MonteCarloPlayer MCPlayer;

	Color trump;
	int trickCount;
};