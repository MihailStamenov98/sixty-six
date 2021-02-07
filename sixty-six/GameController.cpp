#include "GameController.h"
#include <algorithm>
#include <random>
#include <chrono>
GameController::GameController()
{

	/*vector<Card> deck = getDeck();
	vector<Card>::const_iterator first = deck.begin() + 0;
	vector<Card>::const_iterator last = deck.begin() + 6;
	vector<Card> newVec(first, last);
	first = deck.begin() + 7;
	last = deck.begin() + 13;
	vector<Card> secVec(first, last);*/
	vector<Card> newVec = { Card(diamonds,jack), Card(diamonds,ace), Card(hearts,ace), Card(clubs,ten), Card(clubs,jack), Card(spades,jack) };
	vector<Card> secVec = { Card(hearts, jack), Card(hearts, queen), Card(diamonds,nine), Card(spades,king), Card(hearts,ten), Card(clubs,king) };

	minPlayerCards = secVec;
	maxPlayerCards = newVec;
	trump = diamonds;
	computerPlayer = new MonteCarloPlayer(trump, 10000);
	humanPlayer = new HumanPlayer(trump);
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

void GameController::printCards()
{
	computerPlayer->printCards(maxPlayerCards);
	humanPlayer->printCards(minPlayerCards);
	cout << "Trump is " << getColorString(trump);
	cout << endl;
}

pair<int, int> GameController::trickComputerFirst(int computerResult, int oponentResult, bool hasTrickMax, bool hasTrickMin)
{
	if (maxPlayerCards.size() == 0)
	{
		return make_pair(computerResult, oponentResult);
	}
	printCards();
	///should pass remaining cards not minPlayerCards
	int cardIndex = computerPlayer->startIterationsFirst(maxPlayerCards, minPlayerCards, computerResult, oponentResult, hasTrickMax, hasTrickMin);
	Card firstCard = maxPlayerCards[cardIndex];
	maxPlayerCards.erase(maxPlayerCards.begin() + cardIndex);
	cout << "The computer chose card: (" << firstCard.getColorName() << ", " << firstCard.getName() << ")" << endl;

	cardIndex = humanPlayer->chooseCardSecondMove(firstCard, maxPlayerCards, minPlayerCards, hasTrickMax, hasTrickMin);
	Card secondCard = minPlayerCards[cardIndex];
	minPlayerCards.erase(minPlayerCards.begin() + cardIndex);
	cout << "Human chose card: (" << secondCard.getColorName() << ", " << secondCard.getName() << ")" << endl;

	if (firstCard.isGreater(secondCard, trump))
	{
		computerResult += firstCard.getValue();
		computerResult += secondCard.getValue();
		hasTrickMax = true;
		return trickComputerFirst(computerResult, oponentResult, hasTrickMax, hasTrickMin);
	}
	else
	{
		oponentResult += firstCard.getValue();
		oponentResult += secondCard.getValue();
		hasTrickMin = true;
		return trickComputerSecond(computerResult, oponentResult, hasTrickMax, hasTrickMin);
	}
}

pair<int, int> GameController::trickComputerSecond(int computerResult, int oponentResult, bool hasTrickMax, bool hasTrickMin)
{
	if (maxPlayerCards.size() == 0)
	{
		return make_pair(computerResult, oponentResult);
	}
	printCards(); 

	int cardIndex = humanPlayer->chooseCardFirstMove(maxPlayerCards, minPlayerCards, hasTrickMax, hasTrickMin);;
	Card firstCard(minPlayerCards[cardIndex]);
	minPlayerCards.erase(minPlayerCards.begin() + cardIndex);
	cout << "You chose card: (" << firstCard.getColorName() << ", " << firstCard.getName() << ")" << endl;

	///should pass remaining cards not minPlayerCards
	cardIndex = computerPlayer->startIterationsSecond(firstCard, maxPlayerCards, minPlayerCards, computerResult, oponentResult, hasTrickMax, hasTrickMin);
	Card secondCard = maxPlayerCards[cardIndex];
	maxPlayerCards.erase(maxPlayerCards.begin() + cardIndex);
	cout << "The computer chose card: (" << secondCard.getColorName() << ", " << secondCard.getName() << ")" << endl;

	if (firstCard.isGreater(secondCard, trump))
	{
		oponentResult += firstCard.getValue();
		oponentResult += secondCard.getValue();
		hasTrickMin = true;
		return trickComputerSecond(computerResult, oponentResult, hasTrickMax, hasTrickMin);
	}
	else
	{
		computerResult += firstCard.getValue();
		computerResult += secondCard.getValue();
		hasTrickMax = true;
		return trickComputerFirst(computerResult, oponentResult, hasTrickMax, hasTrickMin);
	}
}

void GameController::play()
{
	cout << "Do you want to be first? (y/n)";
	char response;
	cin >> response;
	if (response == 'n')
	{
		auto result = trickComputerFirst(0, 0, false, false);
		cout << "comp result: " << result.first << ", your result: " << result.second << endl;
	}
	else
	{
		auto result = trickComputerSecond(0, 0, false, false);
		cout << result.first << " " << result.second << endl;;
	}
}