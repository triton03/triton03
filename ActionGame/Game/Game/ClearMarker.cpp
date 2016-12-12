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
	//CSkinModel��������
	skinModelData.LoadModelData("Assets/modelData/clearMarker.x", NULL);
	skinModel.Init(&skinModelData);

	//�f�t�H���g���C�g�ݒ�
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//���[���h�s����쐬(��񂾂�)
	skinModel.Update(position, rotation, CVector3::One);

	m_position = position;		//�ʒu���L�^

	//�T�E���h�\�[�X�̃C���X�^���X�𐶐����āA�Q�[���I�u�W�F�N�g�}�l�[�W���[�ɓo�^����B 
	clearSound = NewGO<CSoundSource>(0); //BGM�����[�h���ď������B
	clearSound->Init("Assets/sound/clear.wav");
}

void ClearMarker::Update()
{
	if (scene->isDelete()) {
		DeleteGO(this);
	}

	//�Ȃ񂩃N���A�����Ƃ�
	CVector3 pos = g_player->GetPosition();

	if (m_position.x > pos.x && !flag) {
		//�Đ��B
		clearSound->Play(false);
		flag = true;
		g_player->SetClear();
	}
}

void ClearMarker::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}