#include "stdafx.h"
#include "Item.h"
#include "Camera.h"
#include "Player.h"
#include "SceneManager.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::Init(CVector3 position, CQuaternion rotation)
{
	skinModel.Init(&skinModelData);

	//デフォルトライト設定
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//ワールド行列を作成(一回だけ)
	skinModel.Update(position, rotation, CVector3::One);

	m_position = position;		//位置を記録

}

void Item::Update()
{
	if (scene->isDelete()) {
		DeleteGO(this);
	}

	//敵とプレイヤーの距離を計算
	float length = g_player->Distance(m_position);

	//プレイヤーと接触したら消す
	if (length <= 2.0f) {
		//動作
		Work();
	}

}

void Item::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}

void Item::Work() {};