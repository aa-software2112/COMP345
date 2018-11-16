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
#include "Country.h"

using namespace std;

enum cardType {
	INFANTRY = 0,
	ARTILLERY = 1,
	CAVALRY = 2
};

class Card {

public:
	static int CardId;

	Card();
	Card(cardType thisCardType);

	void card_setType(cardType thisCardType);

	cardType card_getType();
	int card_getId();

	void card_printType();

	friend ostream& operator<<(ostream& output, Card &c);

private:
	int id;
	cardType thisCardType;
};


#endif /* RISKAPPLICATION_H_CARD_H_ */
