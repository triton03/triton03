/*
	スケルトン
*/

#include "stdafx.h"
#include "Skelton.h"
#include "Player.h"
#include "Camera.h"


Skelton::Skelton()
{
	sprintf(filePath, "Assets/modelData/skelton.X");
	state.hp = 1;
	state.score = 150;
}

Skelton::~Skelton()
{

}
