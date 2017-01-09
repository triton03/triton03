/*
	敵：スケルトン
*/

#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Enemy.h"

class Skelton : public Enemy
{
public:
	Skelton();
	~Skelton();
	void Move();
private:
	float				timer = 0.0f;	//タイマー。
};

