/*
	ÉRÉCÉì
*/

#pragma once
#include "Item.h"

class Coin : public Item
{
public:
	Coin();
	~Coin();
	void Work();
	int GetScore() {
		return score;
	}

private:
	CSoundSource*	SE;
	int				score;
};

