/*
	ƒXƒPƒ‹ƒgƒ“
*/

#include "stdafx.h"
#include "SkeltonFighter.h"
#include "Player.h"
#include "Camera.h"


SkeltonFighter::SkeltonFighter()
{
	sprintf(filePath, "Assets/modelData/skelton_fighter.X");
	state.hp = 2;
	state.score = 200;
}

SkeltonFighter::~SkeltonFighter()
{

}
