#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"
#include "Skelton.h"
#include "SkeltonFighter.h"
#include "Coin.h"
#include "heal.h"
#include "ClearMarker.h"
#include "Player.h"
#include "Back.h"

Map::Map()
{
}


Map::~Map()
{
}

void Map::Start()
{
	
}

void Map::Update()
{
}

void Map::Create(SMapInfo* mapLocInfo,int numObject)
{
	NewGO<Back>(0);

	//置かれているオブジェクトの数のマップチップを生成
	for (int i = 0; i < numObject; i++) {
		if (strcmp("skelton", mapLocInfo[i].modelName) == 0) {
			Skelton* skelton = NewGO<Skelton>(0);
			skelton->Init(mapLocInfo[i].position);
		}
		else if (strcmp("skelton_fighter", mapLocInfo[i].modelName) == 0) {
			SkeltonFighter* skelton = NewGO<SkeltonFighter>(0);
			skelton->Init(mapLocInfo[i].position);
		}
		else if (strcmp("coin", mapLocInfo[i].modelName) == 0) {
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
}