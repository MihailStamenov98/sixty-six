#pragma once
# include "Player.h"
# include "HumanPlayer.h"
#include "ComputerPlayer.h"
class GameController
{
private:

	int computerResult = 0;
	int oponentResult = 0;
	bool hasTrickMax = false;
	bool hasTrickMin = false;

	bool isGAmeClosed = false;

	vector<Card> minPlayerCards;
	vector<Card> maxPlayerCards;
	Color trump;
	vector<Card> deck;
	ComputerPlayer* computerPlayer;//uses maxCards
	Player* humanPlayer;
	bool trickComputerFirst();
	bool trickComputerSecond();
	vector<Card> getDeck();
	vector<Card> getRemainingCards();
	bool trickPlay(bool isComputerFirst);

	int suitAnnouncements(vector<Card> Cards, Card playedCard);
public:
	GameController();
	void play();
	void printCards();
};