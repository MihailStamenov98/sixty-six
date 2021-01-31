#include<iostream>
#include<vector>
using namespace std;

enum Value
{
	nine = 0,
	jack = 2,
	queen = 3,
	king = 4,
	ten = 10,
	ace
};

enum Color
{
	clubs,
	diamonds,
	hearts,
	spades
};

Color coz;

struct Card
{
	Color color;
	Value value;
	Card(Color c, Value v)
	{
		color = c;
		value = v;
	}

	bool isGreater(Card secondCard, Color coz) 
	{
		if (color == coz && secondCard.color == coz)
		{
			return value > secondCard.value;
		}
		else if (color == coz)
		{
			return true;
		}
		else if (secondCard.color == coz)
		{
			return false;
		}
		return value >= secondCard.value;
	}

	int getValue()
	{
		return value;
	}
};


int maxFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints);
int minFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints);

int minSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard)
{
	if (maxCards.size() == 0)
	{
		if (firstCard.isGreater(minCards[0], coz))
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
	for (int i = 0; i < minCards.size(); ++i)
	{
		vector<Card> minCardsReduced = minCards;
		minCardsReduced.erase(minCardsReduced.begin() + i);
		int temp;

		if (firstCard.isGreater(minCards[i], coz))
		{
			maxPoints += firstCard.getValue();
			maxPoints += minCards[i].getValue();
			temp = maxFirstMove(maxCards, minCardsReduced, alpha, beta, maxPoints, minPoints);
		}
		else
		{
			minPoints += firstCard.getValue();
			minPoints += minCards[i].getValue();
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

int maxSecondMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints, Card firstCard)
{
	if (minCards.size() == 0)
	{
		if (firstCard.isGreater(maxCards[0], coz))
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
	for (int i = 0; i < maxCards.size(); ++i)
	{
		vector<Card> maxCardsReduced = maxCards;
		maxCardsReduced.erase(maxCardsReduced.begin() + i);
		int temp;

		if (firstCard.isGreater(maxCards[i], coz))
		{
			minPoints += firstCard.getValue();
			minPoints += maxCards[i].getValue();
			temp = minFirstMove(maxCardsReduced, minCards, alpha, beta, maxPoints, minPoints);
		}
		else
		{
			maxPoints += firstCard.getValue();
			maxPoints += maxCards[i].getValue();
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

int maxFirstMove(vector<Card> maxCards, vector<Card> minCards,int alpha, int beta,  int maxPoints, int minPoints)
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

int minFirstMove(vector<Card> maxCards, vector<Card> minCards, int alpha, int beta, int maxPoints, int minPoints)
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

int main()
{

	return 0;
}