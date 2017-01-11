/*
	敵：スケルトンファイター
*/

#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Enemy.h"

class SkeltonFighter : public Enemy
{
public:
	SkeltonFighter();
	~SkeltonFighter();
	void Move();

private:
	const float		speed = 5.0f;
	float			timer = 0.0f;	//タイマー。
};

