/*
	アイテムの基本クラス
*/

#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"

class Item : public IGameObject
{
public:
	Item();
	~Item();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	virtual void Work();

protected:
	CSkinModel		skinModel;		//スキンモデル
	CSkinModelData	skinModelData;	//スキンモデルデータ

	CVector3	m_position;	//コインの位置
	bool get_flag = false;	//ゲットしたか

};

