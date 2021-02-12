#pragma once
#include "EndGamePlayer.h"
#include "MonteCarloPLayer.h"
#include "ClosedPlayer.h"
class ComputerPlayer: public Player
{
public:
	
	ComputerPlayer(Color trump);

	//void setInfoForGame(int myPoints, int oponentPoints);
	void closeGame();
	void printCards(vector<Card> maxCards);
	int chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards, int myPoints, int oponentPoints, bool hasTrickMax, bool hasTrickMin);
	int chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards, int myPoints, int oponentPoints, bool hasTrickMax, bool hasTrickMin);
	bool shouldCloseGame();
private:

	EndGamePlayer endPlayer;
	MonteCarloPlayer MCPlayer;
	bool isGameClosed = false;
	Color trump;
	int trickCount;
};