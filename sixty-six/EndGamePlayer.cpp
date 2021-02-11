#include "EndGamePlayer.h"
#include<algorithm>
#include<iterator>
#include<iostream>
using namespace std;

EndGamePlayer::EndGamePlayer(Color trump): rules(trump)
{
	this->trump = trump;
}

void EndGamePlayer::printCards(vector<Card> maxCards)
{
	cout << endl << "EndGamePlayer cards are are:";
	for (int i = 0; i < maxCards.size(); ++i)
	{
		cout << "(" << maxCards[i].getColorName() << "," << maxCards[i].getName() << "), ";
	}
}

int EndGamePlayer::getGameValue(int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin)
{
	if (hasTrickMin)
	{
		if (hasTrickMax)
		{
			if (minPoints < 33)
			{
				return 2;
			}
			else
			{
				if (maxPoints < 33)
				{
					return -2;
				}
				else
				{
					if (maxPoints > minPoints)
						return 1;
					else
						return -1;
				}
			}
		}
		else
		{
			return -3;
		}
	}
	else
	{
		return 3;
	}

	//return maxPoints - minPoints;
}

int EndGamePlayer::suitAnnouncements(Color trump, vector<Card> Cards, Card playedCard)
{
	if (playedCard.getValue() == Value::king)
	{
		for (int i = 0; i < Cards.size(); ++i)
		{
			if (Cards[i].getValue() == Value::queen)
			{
				if (Cards[i].getColor() == playedCard.getColor())
				{
					if (trump == playedCard.getColor())
						return 40;
					else
						return 20;
				}
			}
		}
	}
	else if (playedCard.getValue() == Value::queen)
	{
		for (int i = 0; i < Cards.size(); ++i)
		{
			if (Cards[i].getValue() == Value::king)
			{
				if (Cards[i].getColor() == playedCard.getColor())
				{
					if (trump == playedCard.getColor())
						return 40;
					else
						return 20;
				}
			}
		}
	}
	return 0;
}

int EndGamePlayer:: minSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard, bool hasTrickMax, bool hasTrickMin)
{
	if (maxCards.size() == 0)
	{
		if (firstCard.isGreater(minCards[0], trump))
		{
			maxPoints += firstCard.getValue();
			maxPoints += minCards[0].getValue();
			maxPoints += 10;
			hasTrickMax = true;
			return getGameValue(maxPoints,minPoints, hasTrickMax, hasTrickMin); // 0 bez ryka -3, 0 s ryka -2
		}


		minPoints += firstCard.getValue();
		minPoints += minCards[0].getValue();
		minPoints += 10;
		hasTrickMin = true;
		return getGameValue( maxPoints, minPoints, hasTrickMax, hasTrickMin);
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
			hasTrickMax = true;
			temp = maxFirstMove(maxCards, minCardsReduced, alpha, beta, maxPoints, minPoints, hasTrickMax, hasTrickMin);
		}
		else
		{
			minPoints += firstCard.getValue();
			minPoints += possiblePlays[i].getValue();
			hasTrickMin = true;
			temp = minFirstMove(maxCards, minCardsReduced, alpha, beta, maxPoints, minPoints, hasTrickMax, hasTrickMin);
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

int EndGamePlayer::maxSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard, bool hasTrickMax, bool hasTrickMin)
{
	if (minCards.size() == 0)
	{
		if (firstCard.isGreater(maxCards[0], trump))
		{
			minPoints += firstCard.getValue();
			minPoints += maxCards[0].getValue();
			minPoints += 10;
			hasTrickMin = true;
			return getGameValue(maxPoints, minPoints, hasTrickMax, hasTrickMin);
		}
		maxPoints += firstCard.getValue();
		maxPoints += maxCards[0].getValue();
		maxPoints += 10;
		hasTrickMax = true;
		return getGameValue( maxPoints, minPoints, hasTrickMax, hasTrickMin);
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
			hasTrickMin = true;
			temp = minFirstMove(maxCardsReduced, minCards, alpha, beta, maxPoints, minPoints, hasTrickMax, hasTrickMin);
		}
		else
		{
			maxPoints += firstCard.getValue();
			maxPoints += possiblePlays[i].getValue();
			hasTrickMax = true;
			temp = maxFirstMove(maxCardsReduced, minCards, alpha, beta, maxPoints, minPoints, hasTrickMax, hasTrickMin);
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

int EndGamePlayer::maxFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin)
{
	int value = -1000;
	for (int i = 0; i < maxCards.size(); ++i)
	{
		vector<Card> maxCardsReduced = maxCards;
		maxCardsReduced.erase(maxCardsReduced.begin() + i);

		maxPoints += suitAnnouncements(trump, maxCards, maxCards[i]);

		int temp = minSecondMove(maxCardsReduced, minCards, alpha, beta, maxPoints, minPoints, maxCards[i], hasTrickMax, hasTrickMin);
		value = max(value, temp);
		alpha = max(alpha, value);
		if (alpha > beta)
		{
			return value;
		}
	}
	return value;
}

int EndGamePlayer::minFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin)
{
	int value = 1000;
	for (int i = 0; i < minCards.size(); ++i)
	{
		vector<Card> minCardsReduced = minCards;
		minCardsReduced.erase(minCardsReduced.begin() + i);

		minPoints += suitAnnouncements(trump, minCards, minCards[i]);

		int temp = minSecondMove(minCardsReduced, minCards, alpha, beta, maxPoints, minPoints, minCards[i], hasTrickMax, hasTrickMin);
		value = min(value, temp);
		beta = min(beta, value);
		if (alpha > beta)
		{
			return value;
		}
	}
	return value;
}

int EndGamePlayer::chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin)
{
	cout << "It is EndGamePlayer turn:\n";
	int value = -1000;
	int index = -1;
	for (int i = 0; i < maxCards.size(); ++i)
	{
		vector<Card> maxCardsReduced = maxCards;
		maxCardsReduced.erase(maxCardsReduced.begin() + i);
		int temp = minSecondMove(maxCardsReduced, minCards, -1000, 1000, maxPoints, minPoints, maxCards[i],hasTrickMax, hasTrickMin);
		if (value < temp)
		{
			value = temp;
			index = i;
		}
	}
	return index;
}

int EndGamePlayer::chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin)
{
	cout << "It is EndGamePlayer turn:\n";
	int index = -1;
	int value = -1000;
	auto possiblePlays = rules.takeAlternatives(maxCards, firstCard);
	for (int i = 0; i < possiblePlays.size(); ++i)
	{
		vector<Card> maxCardsReduced;
		std::copy_if(maxCards.begin(), maxCards.end(), std::back_inserter(maxCardsReduced), [possiblePlays, i](Card c) {return c != possiblePlays[i]; });
		int temp;

		if (firstCard.isGreater(possiblePlays[i], trump))
		{
			minPoints += firstCard.getValue();
			minPoints += possiblePlays[i].getValue();
			hasTrickMin = true;
			temp = minFirstMove(maxCardsReduced, minCards, -1000, 1000, maxPoints, minPoints, hasTrickMax, hasTrickMin);
		}
		else
		{
			maxPoints += firstCard.getValue();
			maxPoints += possiblePlays[i].getValue();
			hasTrickMax = true;
			temp = maxFirstMove(maxCardsReduced, minCards, -1000, 1000, maxPoints, minPoints, hasTrickMax, hasTrickMin);
		}

		if (value < temp)
		{
			value = temp;
			index = i;
		}
	}
	int j = 0;
	while (maxCards[j] != possiblePlays[index])
	{
		++j;
	}
	return j;
}

