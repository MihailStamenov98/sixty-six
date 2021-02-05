#include "GameController.h"
void GameController::printCards()
{
	cout << "Your cards are:";
	for (int i = 0; i < minPlayerCards.size(); ++i)
	{
		cout << "(" << minPlayerCards[i].getColorName() << "," << minPlayerCards[i].getName() << ",index:" << i << "), ";
	}
	cout << endl << "My cards are:";
	for (int i = 0; i < maxPlayerCards.size(); ++i)
	{
		cout << "(" << maxPlayerCards[i].getColorName() << "," << maxPlayerCards[i].getName() << "), ";
	}
	cout << endl;
}

pair<int, int> GameController::trickComputerFirst(int computerResult, int oponentResult)
{
	if (maxPlayerCards.size() == 0)
	{
		return make_pair(computerResult, oponentResult);
	}
	printCards();
	int cardIndex = chooseCardFirstMove();
	Card firstCard = maxPlayerCards[cardIndex];
	maxPlayerCards.erase(maxPlayerCards.begin() + cardIndex);
	cout << "The computer chose card: (" << firstCard.getColorName() << ", " << firstCard.getName() << ")" << endl;
	cout << "It is your turn (enter index of your card): ";
	cin >> cardIndex;
	cout << endl;
	Card secondCard = minPlayerCards[cardIndex];
	minPlayerCards.erase(minPlayerCards.begin() + cardIndex);
	cout << "You chose card: (" << secondCard.getColorName() << ", " << secondCard.getName() << ")" << endl;

	if (firstCard.isGreater(secondCard, trump))
	{
		computerResult += firstCard.getValue();
		computerResult += secondCard.getValue();
		return trickComputerFirst(computerResult, oponentResult);
	}
	else
	{
		oponentResult += firstCard.getValue();
		oponentResult += secondCard.getValue();
		return trickComputerSecond(computerResult, oponentResult);
	}
}

pair<int, int> GameController::trickComputerSecond(int computerResult, int oponentResult)
{
	if (maxPlayerCards.size() == 0)
	{
		return make_pair(computerResult, oponentResult);
	}
	printCards();
	cout << "It is your turn (enter index of your card): ";
	int cardIndex;
	cin >> cardIndex;
	cout << endl;
	Card firstCard(minPlayerCards[cardIndex]);
	minPlayerCards.erase(minPlayerCards.begin() + cardIndex);
	cout << "You chose card: (" << firstCard.getColorName() << ", " << firstCard.getName() << ")" << endl;
	cardIndex = chooseCardSecondMove(firstCard);
	Card secondCard = maxPlayerCards[cardIndex];
	maxPlayerCards.erase(maxPlayerCards.begin() + cardIndex);
	cout << "The computer chose card: (" << secondCard.getColorName() << ", " << secondCard.getName() << ")" << endl;

	if (firstCard.isGreater(secondCard, trump))
	{
		oponentResult += firstCard.getValue();
		oponentResult += secondCard.getValue();
		return trickComputerSecond(computerResult, oponentResult);
	}
	else
	{
		computerResult += firstCard.getValue();
		computerResult += secondCard.getValue();
		return trickComputerFirst(computerResult, oponentResult);
	}
}

void GameController::play()
{
	cout << "Do you want to be first? (y/n)";
	char response;
	cin >> response;
	if (response == 'n')
	{
		auto result = trickComputerFirst(0, 0);
		cout << "comp result: " << result.first << ", your result: " << result.second << endl;
	}
	else
	{
		auto result = trickComputerSecond(0, 0);
		cout << result.first << " " << result.second << endl;;
	}
}