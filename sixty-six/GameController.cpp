#include "GameController.h"
#include <algorithm>
#include <random>
#include <chrono>
GameController::GameController()
{

	deck = getDeck();
	vector<Card>::const_iterator first = deck.begin() + 0;
	vector<Card>::const_iterator last = deck.begin() + 6;
	vector<Card> newVec(first, last);
	deck.erase(first, last);
	first = deck.begin() + 7;
	last = deck.begin() + 13;
	vector<Card> secVec(first, last);
	deck.erase(first, last);

	minPlayerCards = secVec;
	maxPlayerCards = newVec;
	trump = deck.back().getColor();
	computerPlayer = new ComputerPlayer(trump);
	humanPlayer = new HumanPlayer(trump);
}

int GameController::suitAnnouncements(vector<Card> Cards, Card playedCard)
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

vector<Card> GameController::getDeck()
{
	vector<Card> deck;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			Card temp(colors[i], values[j]);
			deck.push_back(temp);
		}
	}
	unsigned seed = std::chrono::system_clock::now()
		.time_since_epoch()
		.count();
	std::shuffle(std::begin(deck), std::end(deck), std::default_random_engine(seed));
	return deck;
}

vector<Card> GameController::getRemainingCards()
{
	vector<Card> remainingCards;
	remainingCards.insert(remainingCards.end(), minPlayerCards.begin(), minPlayerCards.end());
	remainingCards.insert(remainingCards.end(), deck.begin(), deck.end());
	return remainingCards;
}


void GameController::printCards()
{
	computerPlayer->printCards(maxPlayerCards);
	humanPlayer->printCards(minPlayerCards);
	cout << "Trump is " << getColorString(trump);
	cout << endl;
}

bool GameController::trickComputerFirst()
{
	printCards();
	///should pass remaining cards not minPlayerCards
	int cardIndex = computerPlayer->chooseCardFirstMove(maxPlayerCards, getRemainingCards(), computerResult, oponentResult, hasTrickMax, hasTrickMin);
	Card firstCard = maxPlayerCards[cardIndex];
	maxPlayerCards.erase(maxPlayerCards.begin() + cardIndex);
	int anaunce = suitAnnouncements(maxPlayerCards, firstCard);
	if (anaunce > 0)
	{
		cout << "Computer has anaunce: " << anaunce << endl;
	}
	computerResult += anaunce;
	cout << "The computer chose card: (" << firstCard.getColorName() << ", " << firstCard.getName() << ")" << endl;

	cardIndex = humanPlayer->chooseCardSecondMove(firstCard, maxPlayerCards, minPlayerCards,computerResult, oponentResult, hasTrickMax, hasTrickMin);
	Card secondCard = minPlayerCards[cardIndex];
	minPlayerCards.erase(minPlayerCards.begin() + cardIndex);
	anaunce = suitAnnouncements(minPlayerCards, secondCard);
	if (anaunce > 0)
	{
		cout << "Human has anaunce: " << anaunce << endl;
	}
	oponentResult += anaunce;
	cout << "Human chose card: (" << secondCard.getColorName() << ", " << secondCard.getName() << ")" << endl;

	if (firstCard.isGreater(secondCard, trump))
	{
		computerResult += firstCard.getValue();
		computerResult += secondCard.getValue();
		hasTrickMax = true;
		return true;
	}
	else
	{
		oponentResult += firstCard.getValue();
		oponentResult += secondCard.getValue();
		hasTrickMin = true;
		return false;
	}
}

bool GameController::trickComputerSecond()
{
	printCards(); 

	int cardIndex = humanPlayer->chooseCardFirstMove(maxPlayerCards, minPlayerCards,computerResult, oponentResult, hasTrickMax, hasTrickMin);;
	Card firstCard = minPlayerCards[cardIndex];
	minPlayerCards.erase(minPlayerCards.begin() + cardIndex);
	int anaunce = suitAnnouncements(minPlayerCards, firstCard);
	if (anaunce > 0)
	{
		cout << "Human has anaunce: " << anaunce << endl;
	}
	oponentResult += anaunce;
	cout << "You chose card: (" << firstCard.getColorName() << ", " << firstCard.getName() << ")" << endl;

	///should pass remaining cards not minPlayerCards
	cardIndex = computerPlayer->chooseCardSecondMove(firstCard, maxPlayerCards, getRemainingCards(), computerResult, oponentResult, hasTrickMax, hasTrickMin);
	Card secondCard = maxPlayerCards[cardIndex];
	maxPlayerCards.erase(maxPlayerCards.begin() + cardIndex);
	anaunce = suitAnnouncements(maxPlayerCards, secondCard);
	if (anaunce > 0)
	{
		cout << "Computer has anaunce: " << anaunce << endl;
	}
	computerResult += anaunce;
	cout << "The computer chose card: (" << secondCard.getColorName() << ", " << secondCard.getName() << ")" << endl;

	if (firstCard.isGreater(secondCard, trump))
	{
		oponentResult += firstCard.getValue();
		oponentResult += secondCard.getValue();
		hasTrickMin = true;
		return false;
	}
	else
	{
		computerResult += firstCard.getValue();
		computerResult += secondCard.getValue();
		hasTrickMax = true;
		return true;
	}
}

bool GameController::trickPlay(bool isComuterFirst)
{
	if (isComuterFirst)
	{
		isComuterFirst = trickComputerFirst();
	}
	else
	{
		isComuterFirst = trickComputerSecond();
	}

	if (!isGAmeClosed)
	{
		if (isComuterFirst)
		{
			maxPlayerCards.push_back(deck[0]);
			deck.erase(deck.begin());
			minPlayerCards.push_back(deck[0]);
			deck.erase(deck.begin());
		}
		else
		{
			minPlayerCards.push_back(deck[0]);
			deck.erase(deck.begin());
			maxPlayerCards.push_back(deck[0]);
			deck.erase(deck.begin());
		}
	}
	return isComuterFirst;
}


void GameController::play()
{
	cout << "Do you want to be first? (y/n)";
	char response;
	cin >> response;
	auto iscomputerFirst = (response == 'n');

	while (maxPlayerCards.size() != 0)
	{
		iscomputerFirst = trickPlay(iscomputerFirst);
	}

	cout << "comp result: " << computerResult << ", your result: " << oponentResult << endl;
}