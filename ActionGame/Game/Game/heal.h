/*
	回復アイテム
*/

#pragma once

#include "Item.h"

class Heal : public Item
{
public:
	Heal();
	~Heal();
	void Work();
};

