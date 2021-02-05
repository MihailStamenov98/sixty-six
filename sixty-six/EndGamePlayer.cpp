#include "EndGamePlayer.h"
#include<algorithm>
#include<iterator>
#include<iostream>
using namespace std;

EndGamePlayer::EndGamePlayer(Color trump, vector<Card> maxPlayerCards, vector<Card> minPlayerCards): rules(trump)
{
	this->trump = trump;
	this->maxPlayerCards = maxPlayerCards;
	this->minPlayerCards = minPlayerCards;
}

int EndGamePlayer:: minSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard)
{
	if (maxCards.size() == 0)
	{
		if (firstCard.isGreater(minCards[0], trump))
		{
			maxPoints += firstCard.getValue();
			maxPoints += minCards[0].getValue();
			return maxPoints - minPoints;
		}


		minPoints += firstCard.getValue();
		minPoints += minCards[0].getValue();
		return maxPoints - minPoints;
	}

	int value = 1000;
	auto possiblePlays = rules.takeAlternatives(minCards, firstCard);
	for (int i = 0; i < possiblePlays.size(); ++i)
	{
		vector<Card> minCardsReduced;
		std::copy_if(minCards.begin(), minCards.end(), std::back_inserter(minCardsReduced), [possiblePlays, i](Card c) {return c != possiblePlays[i];});
		int temp;
		if (firstCard.isGreater(possiblePlays[i], trump))
		{
			maxPoints += firstCard.getValue();
			maxPoints += possiblePlays[i].getValue();
			temp = maxFirstMove(maxCards, minCardsReduced, alpha, beta, maxPoints, minPoints);
		}
		else
		{
			minPoints += firstCard.getValue();
			minPoints += possiblePlays[i].getValue();
			temp = minFirstMove(maxCards, minCardsReduced, alpha, beta, maxPoints, minPoints);
		}

		value = min(value, temp);
		beta = min(beta, value);
		if (alpha > beta)
		{
			return value;
		}
	}
	return value;

}

int EndGamePlayer::maxSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard)
{
	if (minCards.size() == 0)
	{
		if (firstCard.isGreater(maxCards[0], trump))
		{
			minPoints += firstCard.getValue();
			minPoints += maxCards[0].getValue();
			return maxPoints - minPoints;
		}
		maxPoints += firstCard.getValue();
		maxPoints += maxCards[0].getValue();
		return maxPoints - minPoints;
	}

	int value = -1000;
	auto possiblePlays = rules.takeAlternatives(maxCards, firstCard);
	for (int i = 0; i < possiblePlays.size(); ++i)
	{
		vector<Card> maxCardsReduced;
		std::copy_if(maxCards.begin(), maxCards.end(), std::back_inserter(maxCardsReduced), [possiblePlays, i](Card c) {return c != possiblePlays[i];});
		int temp;

		if (firstCard.isGreater(possiblePlays[i], trump))
		{
			minPoints += firstCard.getValue();
			minPoints += possiblePlays[i].getValue();
			temp = minFirstMove(maxCardsReduced, minCards, alpha, beta, maxPoints, minPoints);
		}
		else
		{
			maxPoints += firstCard.getValue();
			maxPoints += possiblePlays[i].getValue();
			temp = maxFirstMove(maxCardsReduced, minCards, alpha, beta, maxPoints, minPoints);
		}

		value = max(value, temp);
		beta = max(beta, value);
		if (alpha > beta)
		{
			return value;
		}
	}
	return value;

}

int EndGamePlayer::maxFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints)
{
	int value = -1000;
	for (int i = 0; i < maxCards.size(); ++i)
	{
		vector<Card> maxCardsReduced = maxCards;
		maxCardsReduced.erase(maxCardsReduced.begin() + i);
		int temp = minSecondMove(maxCardsReduced, minCards, alpha, beta, maxPoints, minPoints, maxCards[i]);
		value = max(value, temp);
		alpha = max(alpha, value);
		if (alpha > beta)
		{
			return value;
		}
	}
	return value;
}

int EndGamePlayer::minFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints)
{
	int value = 1000;
	for (int i = 0; i < minCards.size(); ++i)
	{
		vector<Card> minCardsReduced = minCards;
		minCardsReduced.erase(minCardsReduced.begin() + i);
		int temp = minSecondMove(minCardsReduced, minCards, alpha, beta, maxPoints, minPoints, minCards[i]);
		value = min(value, temp);
		beta = min(beta, value);
		if (alpha > beta)
		{
			return value;
		}
	}
	return value;
}

int EndGamePlayer::chooseCardFirstMove()
{
	int value = -1000;
	int index = -1;
	for (int i = 0; i < maxPlayerCards.size(); ++i)
	{
		vector<Card> maxCardsReduced = maxPlayerCards;
		maxCardsReduced.erase(maxCardsReduced.begin() + i);
		int temp = minSecondMove(maxCardsReduced, minPlayerCards, -1000, 1000, 0, 0, maxPlayerCards[i]);
		if (value < temp)
		{
			value = temp;
			index = i;
		}
	}
	return index;
}

int EndGamePlayer::chooseCardSecondMove(Card firstCard)
{
	int index = -1;
	int value = -1000;
	auto possiblePlays = rules.takeAlternatives(maxPlayerCards, firstCard);
	for (int i = 0; i < possiblePlays.size(); ++i)
	{
		vector<Card> maxCardsReduced;
		std::copy_if(maxPlayerCards.begin(), maxPlayerCards.end(), std::back_inserter(maxCardsReduced), [possiblePlays, i](Card c) {return c != possiblePlays[i]; });
		int temp;

		if (firstCard.isGreater(possiblePlays[i], trump))
		{
			int minPoints = firstCard.getValue();
			minPoints += possiblePlays[i].getValue();
			temp = minFirstMove(maxCardsReduced, minPlayerCards, -1000, 1000, 0, minPoints);
		}
		else
		{
			int maxPoints = firstCard.getValue();
			maxPoints += possiblePlays[i].getValue();
			temp = maxFirstMove(maxCardsReduced, minPlayerCards, -1000, 1000, maxPoints, 0);
		}

		if (value < temp)
		{
			value = temp;
			index = i;
		}
	}
	int j = 0;
	while (maxPlayerCards[j] != possiblePlays[index])
	{
		++j;
	}
	return j;
}

