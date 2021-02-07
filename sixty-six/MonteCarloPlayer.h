#pragma once
#include "Player.h"
#include <math.h> 
#include<vector>

class MonteCarloPlayer
{
private:

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

	vector<Node*> createChildren(int count);

	double treeExploaringFirstMove(Node* root, vector<Card> myCards, vector<Card> remainingCards);
	double treeExploaringSecondMove(Card firstCard, Node* root, vector<Card> myCards, vector<Card> remainingCards);
	double treeExploaringOponentSecondMove(Card firstCard, Node* root, vector<Card> myCards, vector<Card> remainingCards);
	double treeExploaringOponentFirstMove(Node* root, vector<Card> myCards, vector<Card> remainingCards);

	int chooseChild(Node* root);

	void deleteTree(Node* root);
	
public:
	MonteCarloPlayer(Color trump, int iterations);
	void printCards(vector<Card> maxCards);
	int startIterationsFirst(vector<Card> myCards, vector<Card> remainingCards,
		int initialMaxPoints, int initialMinPoints, bool initialHasTrunkMax, bool initialHasTrunkMin);
	int startIterationsSecond(Card firstCard, vector<Card> myCards, vector<Card> remainingCards,
		int initialMaxPoints, int initialMinPoints, bool initialHasTrunkMax, bool initialHasTrunkMin);

};