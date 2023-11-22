#pragma once
#include <iostream>
#include <ostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

class Card {
	friend ostream& operator<<(ostream&, const Card&);
public:
	Card(string card);
	//~Card();

	char getRank();
	char getSuit();

private:
	char rank;
	char suit;
};

