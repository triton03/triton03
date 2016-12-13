/*
	É}ÉbÉvä«óù
*/

#pragma once

struct SMapInfo {
	const char*	modelName;
	CVector3	position;
	CQuaternion	rotation;
};

class Map : public IGameObject
{
public:
	Map();
	~Map();
	void Start();
	void Update();
	void Create(SMapInfo* mapLocInfo, int numObject);
};

