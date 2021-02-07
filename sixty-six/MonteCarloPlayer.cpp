#include "MonteCarloPlayer.h"
#include "EndGamePlayer.h"
#include<random>
double MonteCarloPlayer::evaluateNode(double t, int N, int ni)
{
	if (ni == 0)
		return 1000000;
	return (t / (double)ni) + sqrt(log(double(N)) / double(ni));
}

int MonteCarloPlayer::getRandomIndex(int elementsCount)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> distribution(0, elementsCount - 1);
	return distribution(rd);
}

vector<Card> getRemainingCards(vector<Card> myCards, vector<Card> passedCards)
{
	vector<Card> knownCards;
	knownCards.insert(knownCards.end(), myCards.begin(), myCards.end());
	knownCards.insert(knownCards.end(), passedCards.begin(), passedCards.end());
	sort(knownCards.begin(), knownCards.end());
	vector<Card> remainingCards = Card::getRemainingCards(knownCards);
	return remainingCards;
}

double MonteCarloPlayer::rollOutFirstPlay(vector<Card> myCards, vector<Card> remainingCards)
{
	if (remainingCards.size() == 6)
	{
		EndGamePlayer endPlayer(trump);
		return (double)endPlayer.maxFirstMove(myCards, remainingCards, -1000, 1000, myPoints, oponentPoints, hasTrunkMax, hasTrunkMin);
	}

	int randIndex = getRandomIndex(myCards.size());
	Card firstCard = myCards[randIndex];
	myCards.erase(myCards.begin() + randIndex);

	return otherPlayerSimulationResposnse(firstCard, myCards, remainingCards);
}

double MonteCarloPlayer::otherPlayerSimulation(vector<Card> myCards, vector<Card> remainingCards)
{
	int randIndex = getRandomIndex(remainingCards.size());
	Card firstCard = remainingCards[randIndex];
	remainingCards.erase(remainingCards.begin() + randIndex);
	if (remainingCards.size() == 5)
	{
		EndGamePlayer endPlayer(trump);
		return (double)endPlayer.maxSecondMove(myCards, remainingCards, -1000, 1000, myPoints, oponentPoints, firstCard, hasTrunkMax, hasTrunkMin);
	}

	return rollOutSecondPlay(firstCard, myCards, remainingCards);
}

double MonteCarloPlayer::otherPlayerSimulationResposnse(Card firstCard, vector<Card> myCards, vector<Card> remainingCards)
{
	int randIndex = getRandomIndex(remainingCards.size());
	Card secondCard = remainingCards[randIndex];
	remainingCards.erase(remainingCards.begin() + randIndex);

	randIndex = getRandomIndex(remainingCards.size());
	myCards.push_back(remainingCards[randIndex]);
	remainingCards.erase(remainingCards.begin() + randIndex);
	if (firstCard.isGreater(secondCard, trump))
	{
		hasTrunkMax = true;
		myPoints = myPoints + firstCard.getValue() + secondCard.getValue();
		return rollOutFirstPlay(myCards, remainingCards);
	}
	else
	{
		hasTrunkMin = true;
		oponentPoints = oponentPoints + firstCard.getValue() + secondCard.getValue();
		return otherPlayerSimulation(myCards, remainingCards);
	}
}

double MonteCarloPlayer::rollOutSecondPlay(Card firstCard, vector<Card> myCards, vector<Card> remainingCards)
{
	int randIndex = getRandomIndex(myCards.size());
	Card secondCard = myCards[randIndex];
	myCards.erase(myCards.begin() + randIndex);

	randIndex = getRandomIndex(remainingCards.size());
	myCards.push_back(remainingCards[randIndex]);
	remainingCards.erase(remainingCards.begin() + randIndex);
	if (firstCard.isGreater(secondCard, trump))
	{
		hasTrunkMin = true;
		myPoints = myPoints + firstCard.getValue() + secondCard.getValue();
		return rollOutFirstPlay(myCards, remainingCards);
	}
	else
	{
		hasTrunkMax = true;
		oponentPoints = oponentPoints + firstCard.getValue() + secondCard.getValue();
		return otherPlayerSimulation(myCards, remainingCards);
	}
}

double MonteCarloPlayer::treeExploaringFirstMove(Node* root, vector<Card> myCards, vector<Card> remainingCards)
{
	if (root->n == 0)
	{
		root->t = rollOutFirstPlay(myCards, remainingCards);
		root->n = root->n + 1;
		return root->t;
	}
	else
	{
		if (root->n == 1)
		{
			root->children = createChildren(myCards.size());
		}
		int i = chooseChild(root);
		Node* exploreChild = root->children[i];
		Card firstCard = myCards[i];
		myCards.erase(myCards.begin() + i);
		root->n = root->n + 1;
		root->t += treeExploaringOponentSecondMove(firstCard, exploreChild, myCards, remainingCards);
		return root->t;
	}

}

double MonteCarloPlayer::treeExploaringOponentSecondMove(Card firstCard, Node* root, vector<Card> myCards, vector<Card> remainingCards)
{
	if (root->n == 0)
	{
		root->t = otherPlayerSimulationResposnse(firstCard, myCards, remainingCards);
		root->n = root->n + 1;
		return root->t;
	}
	else
	{
		if (root->n == 1)
		{
			root->children = createChildren(remainingCards.size());
		}
		int i = chooseChild(root);
		Node* exploreChild = root->children[i];
		Card secondCard = remainingCards[i];
		remainingCards.erase(remainingCards.begin() + i);
		if (firstCard.isGreater(secondCard, trump))
		{
			hasTrunkMax = true;
			myPoints += (firstCard.getValue() + secondCard.getValue());
			root->t += treeExploaringFirstMove(root->children[i], myCards, remainingCards);
		}
		else
		{
			hasTrunkMin = true;
			oponentPoints += (firstCard.getValue() + secondCard.getValue());
			root->t += treeExploaringOponentFirstMove(root->children[i], myCards, remainingCards);
		}
		root->n = root->n + 1;
		return root->t;
	}

}

double MonteCarloPlayer::treeExploaringOponentFirstMove(Node* root, vector<Card> myCards, vector<Card> remainingCards)
{
	if (root->n == 0)
	{
		root->t = otherPlayerSimulation( myCards, remainingCards);
		root->n = root->n + 1;
		return root->t;
	}
	else
	{
		if (root->n == 1)
		{
			root->children = createChildren(remainingCards.size());
		}
		int i = chooseChild(root);
		Node* exploreChild = root->children[i];
		Card firstCard = remainingCards[i];
		remainingCards.erase(remainingCards.begin() + i);
		root->n = root->n + 1;
		root->t += treeExploaringSecondMove(firstCard, exploreChild, myCards, remainingCards);
		return root->t;
	}
}

double MonteCarloPlayer::treeExploaringSecondMove(Card firstCard, Node* root, vector<Card> myCards, vector<Card> remainingCards)
{
	if (root->n == 0)
	{
		root->t = rollOutSecondPlay(firstCard, myCards, remainingCards);
		root->n = root->n + 1;
		return root->t;
	}
	else
	{
		if (root->n == 1)
		{
			root->children = createChildren(myCards.size());
		}
		int i = chooseChild(root);
		Node* exploreChild = root->children[i];
		Card secondCard = myCards[i];
		myCards.erase(myCards.begin() + i);
		if (firstCard.isGreater(secondCard, trump))
		{
			hasTrunkMin = true;
			oponentPoints += (firstCard.getValue() + secondCard.getValue());
			root->t += treeExploaringOponentFirstMove(root->children[i], myCards, remainingCards);
		}
		else
		{
			hasTrunkMax = true;
			myPoints += (firstCard.getValue() + secondCard.getValue());
			root->t += treeExploaringFirstMove(root->children[i], myCards, remainingCards);
		}
		root->n = root->n + 1;
		return root->t;
	}

}

void MonteCarloPlayer::deleteTree(Node* root)
{
	if (root == nullptr)
		return;
	if (root->children.size() == 0)
		delete root;
	for (int i = 0; i < root->children.size(); ++i)
	{
		deleteTree(root->children[i]);
	}
}


void  MonteCarloPlayer::startIterationsFirst(vector<Card> myCards, vector<Card> remainingCards, int initialMaxPoints, int initialMinPoints, bool initialHasTrunkMax, bool initialHasTrunkMin)
{
	Node* root = new Node();
	root->t = 0;
	root->n = 0;
	for (int i = 0; i < iterations; i++)
	{
		myPoints = initialMaxPoints;
		oponentPoints = initialMinPoints;
		hasTrunkMax = initialHasTrunkMax;
		hasTrunkMin = initialHasTrunkMin;
		auto x = treeExploaringFirstMove(root, myCards, remainingCards);
	}
	deleteTree(root);
}

void MonteCarloPlayer::startIterationsSecond(Card firstCard, vector<Card> myCards, vector<Card> remainingCards, int initialMaxPoints, int initialMinPoints, bool initialHasTrunkMax, bool initialHasTrunkMin)
{
	Node* root = new Node();
	root->t = 0;
	root->n = 0;
	for (int i = 0; i < iterations; i++)
	{
		myPoints = initialMaxPoints;
		oponentPoints = initialMinPoints;
		hasTrunkMax = initialHasTrunkMax;
		hasTrunkMin = initialHasTrunkMin;
		auto x = treeExploaringSecondMove(firstCard, root, myCards, remainingCards);
	}
	deleteTree(root);
}

vector<MonteCarloPlayer::Node*> MonteCarloPlayer::createChildren(int count)
{
	vector<Node*> children;
	for (int i = 0; i < count; ++i)
	{
		Node* temp = new Node();
		temp->t = 0;
		temp->n = 0;
		children.push_back(temp);
	}
	return children;
}

