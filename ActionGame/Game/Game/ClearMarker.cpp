#include "stdafx.h"
#include "ClearMarker.h"
#include "Camera.h"
#include "Player.h"
#include "SceneManager.h"


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

	//サウンドソースのインスタンスを生成して、ゲームオブジェクトマネージャーに登録する。 
	clearSound = NewGO<CSoundSource>(0); //BGMをロードして初期化。
	clearSound->Init("Assets/sound/clear.wav");
}

void ClearMarker::Update()
{
	if (scene->isDelete()) {
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	//なんかクリア条件とか
	CVector3 pos = g_player->GetPosition();

	if (position.x > pos.x && !flag) {
		//再生。
		clearSound->Play(false);
		flag = true;
		g_player->SetClear();
	}

	skinModel.Update(position, rotation, CVector3::One);
}

void ClearMarker::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}