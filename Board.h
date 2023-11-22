#pragma once

#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

#include "Card.h"
#include "Hand.h"


class Board : public Hand {
public:
	Board(vector<string>);
	void join(Hand&);
	vector<Hand>& getHands();
	void printBoardCards();
	string whoWinsHi();
	string whoWinsLo();


	/*******************  Hands Check  *********************/

	bool flush(vector<Card>&, int);
	bool fourKinds(vector<Card>&, int*, int);
	bool fullHouse(vector<Card>&, int*);
	bool straight(vector<Card>&, int*);
	bool threeKinds(vector<Card>&, int*, int);
	bool twoPair(vector<Card>&, int*);
	string fight(int);

private:
	vector<Hand> hands;

	int scoreHandA;
	int scoreHandB;

};

