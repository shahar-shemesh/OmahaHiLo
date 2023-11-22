#include <string>
#include <limits>
#include "Board.h"

enum handRank {
    STRAIGHTFLUSH = 9,
    FOUROFKIND = 8,
    FULLHOUSE = 7,
    FLUSH = 6,
    STRAIGHT = 5,
    THREEOFKIND = 4,
    TWOPAIRS = 3,
    ONEPAIR = 2,
    HIGHCARD = 1
};


map<char, int> suits = {
    {'c',1},	// CLUBS
    {'d',2},	// DIAMONDS
    {'h',3},	// HEARTS
    {'s',4}		// SPADES
};


map<char, int> ranks = {
    {'A',1},	// ACE
    {'2',2},
    {'3',3},
    {'4',4},
    {'5',5},
    {'6',6},
    {'7',7},
    {'8',8},
    {'9',9},
    {'T',10},
    {'J',11},	// PRINCE
    {'Q',12},	// QUEEN
    {'K',13}	// KING
};


char valueToKeyRanksMap(int val) {
    char suit;
    for (auto it = ranks.begin(); it != ranks.end(); ++it)
    {
        if (it->second == val) {
            suit = it->first;
            break;
        }
    }
    return suit;
}


int indexOfMaxValue(int* arr, int sizeArr) {
    int* maxValue = arr;
    maxValue = max_element(arr, arr + sizeArr);
    int index = maxValue - arr;
    return index;
}


Board::Board(vector<string> cards) : Hand(cards), scoreHandA(0), scoreHandB(0) {};


void Board::join(Hand& hand) {
	hands.push_back(hand);
}

vector<Hand>& Board::getHands() {
	return this->hands;
}

void Board::printBoardCards() {
    vector<Card>::iterator it = cards.begin();
    cout << "Board:";
    while (it != cards.end() - 1)
    {
        cout << *it << "-";
        it++;
    }
    cout << *it << endl;
}


string Board::whoWinsHi(){

    int* ptrScore = &scoreHandA;

    for (Hand hand : hands) {

        int countRanksArr[14] = { 0 };
        int countSuitsArr[5] = { 0 };

        for (Card card : hand.getCards()) {
            countRanksArr[ranks[card.getRank()]]++;
            countSuitsArr[suits[card.getSuit()]]++;
        }

        for (Card card : this->cards) {
            countRanksArr[ranks[card.getRank()]]++;
            countSuitsArr[suits[card.getSuit()]]++;
        }

        int indexMaxRank = indexOfMaxValue(countRanksArr, 14);
        int indexMaxSuit = indexOfMaxValue(countSuitsArr, 5);


        //------------- Straight -------------
        bool hasStraight = straight(hand.getCards(), countRanksArr); 
        

        //------------- Flush -------------
        bool hasFlush(0);
        if (countSuitsArr[indexMaxSuit] >= 5)
            hasFlush = flush(hand.getCards(), indexMaxSuit);



        //------------- Straight Flush -------------
        bool hasStraightFlush(0);
        if (hasFlush && hasStraight) {
            hasStraightFlush = true;
            *ptrScore = STRAIGHTFLUSH;
            ptrScore = &scoreHandB; 
            continue;
        }

        //------------- 4-of-a-Kind -------------
        bool hasFourKind(0);
        if (countRanksArr[indexMaxRank] >= 4)
            hasFourKind = fourKinds(hand.getCards(), countRanksArr, indexMaxRank);
        if (hasFourKind){
            *ptrScore = FOUROFKIND; 
            ptrScore = &scoreHandB;
            continue;
        }

        //------------- 3-of-a-Kind -------------
        bool hasThreeKind(0);
        if (countRanksArr[indexMaxRank] >= 3)
            hasThreeKind = threeKinds(hand.getCards(), countRanksArr, indexMaxRank);


        //------------- One pair -------------
        int countPairs = count_if(countRanksArr, countRanksArr + 14, [](int i) {return i >= 2; });
        bool hasOnePair(countPairs);


        //------------- Two pair -------------
        bool hasTwoPair = twoPair(hand.getCards(), countRanksArr);


        //------------- Full House -------------
        bool hasFullHouse(0);
        if (hasThreeKind) {
            hasFullHouse = fullHouse(hand.getCards(), countRanksArr);
            if (hasFullHouse)
            {
                *ptrScore = FULLHOUSE;
                ptrScore = &scoreHandB;
                continue;
            }
        }


        if (hasFlush)
            *ptrScore = FLUSH;
        else if (hasStraight)
            *ptrScore = STRAIGHT;
        else if (hasThreeKind)
            *ptrScore = THREEOFKIND; 
        else if (hasTwoPair)
            *ptrScore = TWOPAIRS;
        else if (hasOnePair)
            *ptrScore = ONEPAIR;
        else
            *ptrScore = HIGHCARD;

        ptrScore = &scoreHandB;
    }
 
    string winner;
    int winnerScore;
    if (scoreHandA > scoreHandB)
    {
        winner = "HandA";
        winnerScore = scoreHandA;
    }
    else if (scoreHandA < scoreHandB) {
        winner = "HandB";
        winnerScore = scoreHandB;
    }
    else if (scoreHandA == scoreHandB) {
        winner = fight(scoreHandA);
        winnerScore = (winner == "HandA") ? scoreHandA : scoreHandB;
    }

    string winnerHandRank;
    switch (winnerScore)
    {
    case 2:
        winnerHandRank = "One Pair";
        break;
    case 3:
        winnerHandRank = "Two Pair";
        break;
    case 4:
        winnerHandRank = "3-of-a-Kind";
        break;
    case 5:
        winnerHandRank = "Straight";
        break;
    case 6:
        winnerHandRank = "Flush";
        break;
    case 7:
        winnerHandRank = "Full House";
        break;
    case 8:
        winnerHandRank = "4-of-a-Kind";
        break;
    case 9:
        winnerHandRank = "Straight Flush";
        break;
    }

    if (winner != "HandA" && winner != "HandB")
        return (winner + " (" + winnerHandRank + ")");

    return (winner + " wins Hi (" + winnerHandRank + ")");
    
}
/////////////////////////////////////////////////////////////////////////////////


int getHighCard(Hand& hand) {
    int highCard = 0;
    for (Card card : hand.getCards()) {
        if (highCard < ranks[card.getRank()])
            highCard = ranks[card.getRank()];
    }
    return highCard;
}

int getKicker(Hand& hand) {
    int kicker = 100;
    for (Card card : hand.getCards()) {
        if (kicker > ranks[card.getRank()])
            kicker = ranks[card.getRank()];
    }
    return kicker;
}
/////////////////////////////////////////////////////////////////////////////////


// fight :: function to determine the winner when there's a tie in high hands
string Board::fight(int scoreHand) {
    if (scoreHand == 5)
        return "Split Pot Hi";

    int highCardOfA, highCardOfB, kickerA, kickerB;

    vector<Hand>::iterator it = hands.begin();
    while (it != hands.end()-1)
    {
        highCardOfA = getHighCard(*it);
        kickerA = getKicker(*it);
        it++;
    }
    highCardOfB = getHighCard(*it);
    kickerB = getKicker(*it);


    if (highCardOfA > highCardOfB)
        return "HandA";
    else if (highCardOfA < highCardOfB)
        return "HandB";
    else if (highCardOfA == highCardOfB && kickerA > kickerB)
        return "HandA";
    else if (highCardOfA == highCardOfB && kickerA < kickerB)
        return "HandB";
    else
        return "Split Pot Hi";
}
/////////////////////////////////////////////////////////////////////////////////

// whoWinsLo :: function to determine the winner for the low hand
string Board::whoWinsLo() {

    int* ptrScore = &scoreHandA;

    for (Hand hand : hands) {
        
        set<int> card;
        int higherEighth = 0;

        for (Card c : hand.getCards()) {
            if (ranks[c.getRank()] > 8)
                higherEighth++;
            else
                card.insert(ranks[c.getRank()]);
        }
        if (higherEighth > 2){
            *ptrScore = -1;
            ptrScore = &scoreHandB;
            continue;
        }

        for (Card c : this->cards) {
            if (ranks[c.getRank()] < 8)
                card.insert(ranks[c.getRank()]);
        }

        if (card.size() < 5){
            *ptrScore = -1;
            ptrScore = &scoreHandB;
            continue;
        }

        vector<int> sortedRanks(card.begin(), card.end());
        sort(sortedRanks.begin(), sortedRanks.end());
        reverse(sortedRanks.begin(), sortedRanks.end());

        if (sortedRanks.size() > 5) {
            vector<int>::iterator it = sortedRanks.begin();
            while (sortedRanks.size() > 5)
            {
                sortedRanks.erase(it);
                it = sortedRanks.begin();
            }
        }

        int result = 0;
        for (auto i : sortedRanks)
            result = result * 10 + i;

        *ptrScore = result;
        ptrScore = &scoreHandB;
    }

    string winner;
    int winnerScore;
    if (scoreHandA != -1 && scoreHandB != -1)
    {
        winner = (scoreHandA < scoreHandB) ? "HandA" : "HandB";
        winnerScore = (scoreHandA < scoreHandB) ? scoreHandA : scoreHandB;
    }
    else if (scoreHandA != -1 && scoreHandB == -1) {
        winner = "HandA";
        winnerScore = scoreHandA;
    }
    else if(scoreHandB != -1 && scoreHandA == -1){
        winner = "HandB";
        winnerScore = scoreHandB;
    }
    else
        return "No hand qualified for Low";

    string winnerHandRank = to_string(winnerScore);
    replace(winnerHandRank.begin(), winnerHandRank.end(), '1', 'A');
    return (winner + " wins Lo (" + winnerHandRank + ")");
}
/////////////////////////////////////////////////////////////////////////////////


// twoPair :: Function to check for two pairs in a hand
bool Board::twoPair(vector<Card>& handCards, int* countRanksArr ) {
    
    vector<int> pairs;
    for (int i = 0; i < 14; i++)
    {
        if (countRanksArr[i] == 2)
            pairs.push_back(i);
    }

    if (pairs.size() <= 1)
        return false;

    int sharedPair = 0;

    for (auto item : pairs) {
        int handAppears = 0;
        for (Card c : handCards) {
            if (c.getRank() == valueToKeyRanksMap(item))
                handAppears++;
        }

        int boardAppears = 0;
        for (Card c : this->cards) {
            if (c.getRank() == valueToKeyRanksMap(item))
                boardAppears++;
        }

        if (boardAppears >= 1 && handAppears >= 1)
            sharedPair++;
    }

    if (sharedPair >= 2)
        return true;
    return false;
}
/////////////////////////////////////////////////////////////////////////////////


bool Board::fullHouse(vector<Card>& handCards, int* countRanksArr) {
    int threeValue = 0;
    for (int i = 0; i < 14; i++)
    {
        if (countRanksArr[i] >= 3) {
            threeValue = i;
            break;
        }
    }

    vector<int> pairs;

    for (int i = 0; i < 14; i++)
    {
        if (countRanksArr[i] >= 2)
            pairs.push_back(i);
    }
    vector<int>::iterator it;
    it = find(pairs.begin(), pairs.end(), threeValue);
    pairs.erase(it);

    if (pairs.size() >= 1) {
        int boardAppears = 0;
        for (Card c : this->cards) {
            if (c.getRank() == valueToKeyRanksMap(threeValue))
                boardAppears++;
        }

        if (boardAppears <= 3)
        {
            for (auto item : pairs) {
                int handAppears = 0;
                for (Card c : this->cards) {
                    if (c.getRank() == valueToKeyRanksMap(item))
                        handAppears++;
                }
                if (handAppears == 1) {
                    return true;
                }
            }            
        }
    }
    return false;
}
/////////////////////////////////////////////////////////////////////////////////


bool Board::threeKinds(vector<Card>& handCards, int* countRanksArr, int indexMaxRank) {

    int handAppears = 0;
    for (Card c : handCards) {
        if (c.getRank() == valueToKeyRanksMap(indexMaxRank))
            handAppears++;
    }

    int boardAppears = 0;
    for (Card c : this->cards) {
        if (c.getRank() == valueToKeyRanksMap(indexMaxRank))
            boardAppears++;
    }

    if (handAppears >= 3 || boardAppears == 0)
        return false;

    return true;
}
/////////////////////////////////////////////////////////////////////////////////


bool Board::fourKinds(vector<Card>&handCards, int* countRanksArr, int indexMaxRank) {

    int handAppears = 0;
    for (Card c : handCards) {
        if (c.getRank() == valueToKeyRanksMap(indexMaxRank))
            handAppears++;
    }

    int boardAppears = 0;
    for (Card c : this->cards) {
        if (c.getRank() == valueToKeyRanksMap(indexMaxRank))
            boardAppears++;
    }

    if (handAppears + boardAppears == 4) {
        //if (boardAppears > 3 || handAppears > 3)
        //    return false;
        if (handAppears >= 1 && boardAppears >= 2)
            return true;
    }

    return false;
}
/////////////////////////////////////////////////////////////////////////////////


bool Board::flush(vector<Card>& handCards, int s) {

    char suit;
    int suitCountBoard = 0;
    int suitCountHand = 0;

    for (auto it = suits.begin(); it != suits.end(); ++it)
    {
        if (it->second == s) {
            suit = it->first;
            break;
        }
    }

    for (Card c : handCards) {
        if (c.getSuit() == suit)
            suitCountHand++;
    }

    for (Card c : this->cards) {
        if (c.getSuit() == suit)
            suitCountBoard++;
    }

    if (suitCountHand >= 2 && suitCountBoard >= 3)
        return true;

    return false;
    
}
/////////////////////////////////////////////////////////////////////////////////


bool Board::straight(vector<Card>& handCards, int* countRanksArr) {

    int sequence = 0;
    int startIndex;
    for (int i = 1; i < 14; i++)
    {
        if (countRanksArr[i]) {
            sequence++;
            if (sequence == 5) {
                startIndex = i - 5;
                break;
            }
        }
        else
            sequence = 0;
    }

    if (sequence == 4 && countRanksArr[1])   // for  T -> J -> Q -> K -> A
        return true;
    if (sequence == 5)
        return true;

    return false;
}




