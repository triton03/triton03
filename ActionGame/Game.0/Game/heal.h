/*
	回復アイテム
*/

#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"

class Heal : public IGameObject
{
public:
	Heal();
	~Heal();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CSkinModel		skinModel;		//スキンモデル
	CSkinModelData	skinModelData;	//スキンモデルデータ

	CVector3	m_position;	//コインの位置
	bool get_flag = false;	//ゲットしたか
};

