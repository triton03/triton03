/*
敵：スケルトンメイジ
*/

#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Enemy.h"
#include "EnemyBullet.h"

class SkeltonMage : public Enemy
{
public:
	SkeltonMage();
	~SkeltonMage();
	void Move();

private:
	float				timer = 0.0f;	//タイマー。
};

