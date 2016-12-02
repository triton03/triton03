#include "stdafx.h"
#include "Coin.h"
#include "Camera.h"
#include "Player.h"

CSkinModelData	OriginSkinModelData;	//スキンモデルデータ
bool			flag = false;

Coin::Coin()
{
}


Coin::~Coin()
{
}

void Coin::Init(CVector3 position, CQuaternion rotation)
{
	//モデルデータをロード
	if (!flag) {
		OriginSkinModelData.LoadModelData("Assets/modelData/coin.x", NULL);
		flag = true;
	}
	//CSkinModelを初期化
	skinModelData.CloneModelData(OriginSkinModelData, NULL);
	skinModel.Init(&skinModelData);

	//デフォルトライト設定
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//ワールド行列を作成(一回だけ)
	skinModel.Update(position, rotation, CVector3::One);

	m_position = position;	//位置を記憶

}

void Coin::Update()
{

	//敵とプレイヤーの距離を計算
	float length = g_player->Distance(m_position);

	//プレイヤーと接触したら消す
	if (length <= 2.0f) {
		g_player->CoinGet();
		DeleteGO(this);
	}

}

void Coin::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}