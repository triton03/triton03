#include "stdafx.h"
#include "ClearMarker.h"
#include "Camera.h"
#include "Player.h"
#include "SceneManager.h"
#include "ShowSprite.h"


ClearMarker::ClearMarker()
{
}


ClearMarker::~ClearMarker()
{
}

void ClearMarker::Init(CVector3 position, CQuaternion rotation)
{
	//CSkinModelを初期化
	skinModelData.LoadModelData("Assets/modelData/clearMarker.x", NULL);
	skinModel.Init(&skinModelData);

	//デフォルトライト設定
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//ワールド行列を作成(一回だけ)
	//skinModel.Update(position, rotation, CVector3::One);

	this->position = position;		//位置を記録
	this->rotation = rotation;		//回転を記録

}

void ClearMarker::Update()
{
	if (scene->isDelete()) {
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	if (scene->getBossFlag() || (g_player->GetInfo()!=Player::None)) { return; }

	//なんかクリア条件とか
	CVector3 pos = g_player->GetPosition();

	if (position.x > pos.x && !flag) {
		//再生。
		CSoundSource* clearSound = NewGO<CSoundSource>(0);
		clearSound->Init("Assets/sound/clear.wav");
		clearSound->Play(false);
		flag = true;
		g_player->SetClear();
		int stage = scene->getStage();

		ShowSprite* ss = NewGO<ShowSprite>(0);

		if (scene->getStage()==isStage1) {
			ss->Init(clear1);
		}
		else {
			ss->Init(clear2);
		}
	}

	skinModel.Update(position, rotation, CVector3::One);
}

void ClearMarker::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}