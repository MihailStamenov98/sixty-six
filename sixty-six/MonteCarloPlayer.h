#pragma once
#include "Player.h"
#include <math.h> 
#include<vector>

class MonteCarloPlayer: Player
{
private:

	enum Anounces
	{
		no = 0,
		twenty = 20,
		forty = 40
	};

	struct Node
	{
		double t;
		int n;
		vector<Node*> children;
	};

	Color trump;
	int iterations;
	bool hasTrunkMax = false;
	bool hasTrunkMin = false;
	int myPoints;
	int oponentPoints;

	/*vector<Card> getRemainingCards(vector<Card> myCards, vector<Card> passedCards);*/
	int getRandomIndex(int elementsCount);
	double otherPlayerSimulation(vector<Card> myCards, vector<Card> remainingCards);
	double otherPlayerSimulationResposnse(Card firstCard, vector<Card> myCards, vector<Card> remainingCards);
	double rollOutFirstPlay(vector<Card> myCards, vector<Card> remainingCards);
	double rollOutSecondPlay(Card firstCard, vector<Card> myCards, vector<Card> remainingCards);
	double evaluateNode(double t, int N, int ni);

	vector<Node*> createChildren(vector<Card> cards);
	vector<Card> constructMyCardsForChild(int i, vector<Card> myCards);
	vector<Card> constructRemainingCardsForChild(int i, vector<Card> remainingCards);

	double treeExploaringFirstMove(Node* root, vector<Card> myCards, vector<Card> remainingCards);
	Node* chooseChilde(Node* root);

	void deleteTree(Node* root);
	void startIterationsFirst(vector<Card> myCards, vector<Card> remainingCards, int initialMaxPoints, int initialMinPoints, bool initialHasTrunkMax, bool initialHasTrunkMin);
public:
	MonteCarloPlayer(Color trump, int iterations);
	void printCards(vector<Card> maxCards);
	int chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards);
	int chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards);

};