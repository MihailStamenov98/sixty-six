#include"ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(Color trump): endPlayer(trump), MCPlayer(trump,10000)
{
	trickCount = 0;
	this->trump = trump;
}

void ComputerPlayer::printCards(vector<Card> maxCards)
{
	MCPlayer.printCards(maxCards);
}
int ComputerPlayer::chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards, int myPoints, int oponentPoints, bool hasTrickMax, bool hasTrickMin)
{
	
	shouldCloseGame();
	++trickCount;
	if (isGameClosed)
	{
		ClosedPlayer cp(trump);
		return cp.chooseCardFirstMove(maxCards, minCards, myPoints, oponentPoints, hasTrickMax, hasTrickMin);

	}
	else if (trickCount <= 6)
	{
		return MCPlayer.startIterationsFirst(maxCards, minCards, myPoints, oponentPoints, hasTrickMax, hasTrickMin);
	}
	else
	{
		return endPlayer.chooseCardFirstMove(maxCards, minCards, myPoints, oponentPoints, hasTrickMax, hasTrickMin).first;
	}
	
}
int ComputerPlayer::chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards, int myPoints, int oponentPoints, bool hasTrickMax, bool hasTrickMin)
{
	++trickCount;
	if (isGameClosed)
	{
		ClosedPlayer cp(trump);
		return cp.chooseCardSecondMove(firstCard, maxCards, minCards, myPoints, oponentPoints, hasTrickMax, hasTrickMin);
	}
	else if (trickCount <= 6)
	{
		return MCPlayer.startIterationsSecond(firstCard, maxCards, minCards, myPoints, oponentPoints, hasTrickMax, hasTrickMin);
	}
	else
	{
		return endPlayer.chooseCardSecondMove(firstCard, maxCards, minCards, myPoints, oponentPoints, hasTrickMax, hasTrickMin).first;
	}
}

void ComputerPlayer::closeGame()
{
	isGameClosed = true;
}

bool ComputerPlayer::shouldCloseGame()
{
	if (trickCount >= 2)
	{
		closeGame();
		return true;
	}
	return false;
}