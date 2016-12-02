/*
	コイン
*/

#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"

class Coin : public IGameObject
{
public:
	Coin();
	~Coin();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CSkinModel		skinModel;		//スキンモデル
	CSkinModelData	skinModelData;	//スキンモデルデータ

	CVector3	m_position;	//コインの位置
	bool get_flag = false;	//ゲットしたか
};

