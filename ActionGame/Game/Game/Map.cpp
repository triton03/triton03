#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"
#include "Skelton.h"
#include "Coin.h"
#include "heal.h"
#include "ClearMarker.h"
#include "Player.h"

struct SMapInfo {
	const char*	modelName;
	CVector3	position;
	CQuaternion	rotation;
};

//�}�b�v�̔z�u���
SMapInfo mapLocInfo[] = {
#include "locationInfo.h"
};

Map::Map()
{
}


Map::~Map()
{
}

void Map::Start()
{
	//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);

	//�u����Ă���I�u�W�F�N�g�̐��̃}�b�v�`�b�v�𐶐�
	for (int i = 0; i < numObject; i++) {
		if (strcmp("skelton", mapLocInfo[i].modelName) == 0) {
			Skelton* skelton = NewGO<Skelton>(0);
			skelton->Init(mapLocInfo[i].position);
		}
		else if (strcmp("coin", mapLocInfo[i].modelName)==0) {
			Coin* coin = NewGO<Coin>(0);
			coin->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("item", mapLocInfo[i].modelName) == 0) {
			Heal* heal = NewGO<Heal>(0);
			heal->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("clearMarker", mapLocInfo[i].modelName) == 0) {
			ClearMarker* marker = NewGO<ClearMarker>(0);
			marker->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else {
			MapChip* mapChip = NewGO<MapChip>(0);
			mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
	}

	bgm = NewGO<CSoundSource>(0);
	bgm->InitStreaming("Assets/sound/bgm1.wav");
	bgm->Play(true);
}

void Map::Update()
{
	if (g_player->GetInfo() == Player::isClear) {
		DeleteGO(bgm);
	}
}
