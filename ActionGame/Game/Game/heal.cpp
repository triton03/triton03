#include "stdafx.h"
#include "heal.h"
#include "Camera.h"
#include "Player.h"


CSkinModelData	h_OriginSkinModelData;	//スキンモデルデータ
bool			h_flag = false;

Heal::Heal()
{
}


Heal::~Heal()
{
}

void Heal::Init(CVector3 position, CQuaternion rotation)
{
	//モデルデータをロード
	if (!h_flag) {
		h_OriginSkinModelData.LoadModelData("Assets/modelData/item.x", NULL);
		h_flag = true;
	}
	//CSkinModelを初期化
	skinModelData.CloneModelData(h_OriginSkinModelData, NULL);
	skinModel.Init(&skinModelData);

	//デフォルトライト設定
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//ワールド行列を作成(一回だけ)
	skinModel.Update(position, rotation, CVector3::One);

	m_position = position;		//位置を記録

}

void Heal::Update()
{
	//敵とプレイヤーの距離を計算
	float length = g_player->Distance(m_position);

	//プレイヤーと接触したら消す
	if (length <= 2.0f) {
		//プレイヤーが回復したら消える
		if (g_player->healing()) {
			DeleteGO(this);
		}
	}

}

void Heal::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}