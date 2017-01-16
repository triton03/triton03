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

	this->position = position;		//位置を記録
	this->rotation = rotation;

}

void Item::Update()
{
	if (scene->isDelete()) {
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	//敵とプレイヤーの距離を計算
	length = g_player->Distance(position);

	if (!workFlag) {
		if (length > Limit) { return; }
		workFlag = true;
	}

	//プレイヤーと接触したら消す
	if ((length <= 2.0f) && (g_player->GetInfo()==Player::None)) {
		//動作
		Work();
	}
	skinModel.Update(position, rotation, CVector3::One);
}

void Item::Render(CRenderContext& renderContext)
{
	if (length > Limit) { return; }
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}

void Item::Work() {};