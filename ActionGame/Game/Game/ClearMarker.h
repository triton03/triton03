/*
	クリアマーカー
*/

#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"

class ClearMarker : public IGameObject
{
public:
	ClearMarker();
	~ClearMarker();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CSkinModel			skinModel;		//スキンモデル
	CSkinModelData		skinModelData;	//スキンモデルデータ

	CVector3			m_position;	//マーカーの位置
	bool				flag = false;	//クリアフラグ

	CSoundSource*		clearSound;
};

