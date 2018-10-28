/*
 * Card.h
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */

#ifndef RISKAPPLICATION_H_CARD_H_
#define RISKAPPLICATION_H_CARD_H_

#include <cstdio>
#include <string>
using namespace std;

enum cardType {
	INFANTRY = 0,
	ARTILLERY = 1,
	CAVALRY = 2
};

class Card {

public:
	static int CardId;
	Card(cardType thisCardType);
	Card();

	void setType(cardType thisCardType);
	void printType();
	cardType getType();
	int card_getId();
	friend ostream& operator<<(ostream& output, Card &c);

private:
	int id;
	cardType thisCardType;

};


#endif /* RISKAPPLICATION_H_CARD_H_ */
