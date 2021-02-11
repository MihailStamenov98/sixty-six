#include "MonteCarloPlayer.h"
#include "EndGamePlayer.h"
#include<random>
#include<iostream>
using namespace std;

MonteCarloPlayer::MonteCarloPlayer(Color trump, int iterations)
{
	this->trump = trump;
	this->iterations = iterations;
}

void MonteCarloPlayer::printCards(vector<Card> maxCards)
{
	cout << endl << "EndGamePlayer cards are are:";
	for (int i = 0; i < maxCards.size(); ++i)
	{
		cout << "(" << maxCards[i].getColorName() << "," << maxCards[i].getName() << "), ";
	}
}

double MonteCarloPlayer::evaluateNode(double t, int N, int ni)
{
	if (ni == 0)
		return 1000000;
	return (t / (double)ni) +  sqrt(2 * log(double(N)) / double(ni));
}

int MonteCarloPlayer::getRandomIndex(int elementsCount)
{
	random_device rd;
	mt19937 mt(rd());
	if (elementsCount == 0)
	{
		cout<<"elements are 0"<<endl;
	}
	uniform_int_distribution<> distribution(0, elementsCount-1);
	return distribution(mt);
}

/*vector<Card> getRemainingCards(vector<Card> myCards, vector<Card> passedCards)
{
	vector<Card> knownCards;
	knownCards.insert(knownCards.end(), myCards.begin(), myCards.end());
	knownCards.insert(knownCards.end(), passedCards.begin(), passedCards.end());
	sort(knownCards.begin(), knownCards.end());
	vector<Card> remainingCards = Card::getRemainingCards(knownCards);
	return remainingCards;
}*/

double MonteCarloPlayer::rollOutFirstPlay(vector<Card> myCards, vector<Card> remainingCards)
{
	if (remainingCards.size() == 6)
	{
		EndGamePlayer endPlayer(trump);
		return (double)endPlayer.maxFirstMove(myCards, remainingCards, -1000, 1000, myPoints, oponentPoints, hasTrunkMax, hasTrunkMin);
	}
	if (myCards.size() == 0)
	{
		cout << "myCards are 0\n";
	}
	int randIndex = getRandomIndex(myCards.size());
	Card firstCard = myCards[randIndex];
	myCards.erase(myCards.begin() + randIndex);

	return otherPlayerSimulationResposnse(firstCard, myCards, remainingCards);
}

double MonteCarloPlayer::otherPlayerSimulation(vector<Card> myCards, vector<Card> remainingCards)
{
	if (remainingCards.size() == 6)
	{
		EndGamePlayer endPlayer(trump);
		return (double)endPlayer.minFirstMove(myCards, remainingCards, -1000, 1000, myPoints, oponentPoints, hasTrunkMax, hasTrunkMin);
	}
	int randIndex = getRandomIndex(remainingCards.size());
	Card firstCard = remainingCards[randIndex];
	remainingCards.erase(remainingCards.begin() + randIndex);

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
		oponentPoints = oponentPoints + firstCard.getValue() + secondCard.getValue();
		return otherPlayerSimulation(myCards, remainingCards);
	}
	else
	{
		hasTrunkMax = true;
		myPoints = myPoints + firstCard.getValue() + secondCard.getValue();
		return rollOutFirstPlay(myCards, remainingCards);
	}
}

double MonteCarloPlayer::treeExploaringFirstMove(Node* root, vector<Card> myCards, vector<Card> remainingCards)
{

	if (root->n == 0 || remainingCards.size() == 6)
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
	if (root->n == 0 || remainingCards.size() == 6)
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

		int randIndex = getRandomIndex(remainingCards.size());
		myCards.push_back(remainingCards[randIndex]);
		remainingCards.erase(remainingCards.begin() + randIndex);

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
	if (root->n == 0 || remainingCards.size() == 6)
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
		if (root->children.size() == 0)
		{
			return 0;
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
	if (root->n == 0 || remainingCards.size() == 6)
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

		int randIndex = getRandomIndex(remainingCards.size());
		myCards.push_back(remainingCards[randIndex]);
		remainingCards.erase(remainingCards.begin() + randIndex);

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


int  MonteCarloPlayer::startIterationsFirst(vector<Card> myCards, vector<Card> remainingCards, int initialMaxPoints, int initialMinPoints, bool initialHasTrunkMax, bool initialHasTrunkMin)
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
	if (root->children.size() == 0)
	{
		return 0;
	}
	int bestMove = chooseChild(root);
	deleteTree(root);
	return bestMove;
}

int MonteCarloPlayer::startIterationsSecond(Card firstCard, vector<Card> myCards, vector<Card> remainingCards, int initialMaxPoints, int initialMinPoints, bool initialHasTrunkMax, bool initialHasTrunkMin)
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
	if (root->children.size() == 0)
	{
		return -1;
	}
	int bestMove = chooseChild(root);
	deleteTree(root);
	return bestMove;
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

int MonteCarloPlayer::chooseChild(Node* root)
{
	if (root->children.size() == 0)
	{
		return 0;
	}
	int bestChild = 0;
	double bestValue = evaluateNode(root->children[0]->t, root->n, root->children[0]->n);
	for (int i = 1; i < root->children.size(); ++i)
	{
		double currentValue = evaluateNode(root->children[i]->t, root->n, root->children[i]->n);
		if (bestValue < currentValue)
		{
			bestChild = i;
			bestValue = currentValue;
		}
	}
	return bestChild;
}
