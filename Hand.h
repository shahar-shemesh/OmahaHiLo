#pragma once

#include<iostream>
#include<ostream>
#include<vector>
#include<set>
#include<algorithm>
#include <map>

#include "Card.h"

using namespace std;

class Hand{
	friend ostream& operator<<(ostream&, Hand&);
public:
	Hand(vector<string>);
	vector<Card>& getCards();

protected:
	vector<Card> cards;

};

