/*
	マップ管理
*/

#pragma once
class Map : public IGameObject
{
public:
	Map();
	~Map();
	void Start();
	void Update();

	CSoundSource*	bgm;		//サウンド
};

