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
	//CSkinModel��������
	skinModelData.LoadModelData("Assets/modelData/clearMarker.x", NULL);
	skinModel.Init(&skinModelData);

	//�f�t�H���g���C�g�ݒ�
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//���[���h�s����쐬(��񂾂�)
	//skinModel.Update(position, rotation, CVector3::One);

	this->position = position;		//�ʒu���L�^
	this->rotation = rotation;		//��]���L�^

}

void ClearMarker::Update()
{
	if (scene->isDelete()) {
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	if (scene->getBossFlag() || (g_player->GetInfo()!=Player::None)) { return; }

	//�Ȃ񂩃N���A�����Ƃ�
	CVector3 pos = g_player->GetPosition();

	if (position.x > pos.x && !flag) {
		//�Đ��B
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