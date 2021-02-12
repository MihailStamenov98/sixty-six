#include "ClosedPlayer.h"

ClosedPlayer::ClosedPlayer(Color trump)
{
	this->trump = trump;
    this->maxCards = {};
    this->maxPoints = 0;
    this->minPoints - 0;
    this->hasTrickMax = false;
    this->hasTrickMin = false;
}
int ClosedPlayer::chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin)
{
    this->maxCards = maxCards;
    this->maxPoints = maxPoints;
    this->minPoints - minPoints;
    this->hasTrickMax = hasTrickMax;
    this->hasTrickMin = hasTrickMin;
    int r = maxCards.size();
    vector<Card> data(r);
    combinationUtil(minCards, data, 0, minCards.size()-1, 0, r, true);
    return getMax();
}

int ClosedPlayer::chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards, int maxPoints, int minPoints, bool hasTrickMax, bool hasTrickMin)
{
    this->maxCards = maxCards;
    this->maxPoints = maxPoints;
    this->minPoints - minPoints;
    this->hasTrickMax = hasTrickMax;
    this->hasTrickMin = hasTrickMin;
    this->firstCard = firstCard;
    int r = maxCards.size();
    vector<Card> data(r);
    combinationUtil(minCards, data, 0, minCards.size()-1, 0, r-1, false);
    return getMax();
}

void ClosedPlayer::printCards(vector<Card> maxCards)
{

}

int ClosedPlayer::getMax()
{
    int maxIndex = 0;
    for (int i = 1; i < 6; i++)
    {
        /*if (cardCallsPoints[i]/((double)cardsCallsTimes[i]) > cardCallsPoints[maxIndex]/((double)cardsCallsTimes[maxIndex]))
            maxIndex = i;*/
        if ((double)cardsCallsTimes[i]> (double)cardsCallsTimes[maxIndex])
            maxIndex = i;
    }
    return maxIndex;
}

void ClosedPlayer::combinationUtil(vector<Card> arr, vector<Card> data,
    int start, int end,
    int index, int r, bool isComputerFirst)
{
    if (index == r)
    {
        ++m;
        /*for (int j = 0; j < r; j++)
            cout <<"("<< data[j].getColorName() << ", "<< data[j].getName()<<"); ";
        cout << endl;*/
        EndGamePlayer ePlayer(trump);
        pair<int,int> x;
        if (isComputerFirst)
        {
            x = ePlayer.chooseCardFirstMove(maxCards, data, maxPoints, minPoints, hasTrickMax, hasTrickMin);
        }
        else
        {
            x = ePlayer.chooseCardSecondMove(firstCard, maxCards, data, maxPoints, minPoints, hasTrickMax, hasTrickMin);
        }
        ++cardsCallsTimes[x.first];
        cardCallsPoints[x.first] += x.second;
        return;
    }

    for (int i = start; i <= end &&
        end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i + 1,
            end, index + 1, r, isComputerFirst);
    }
}