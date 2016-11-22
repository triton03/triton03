#include "stdafx.h"
#include "heal.h"
#include "Camera.h"
#include "Player.h"


CSkinModelData	h_OriginSkinModelData;	//�X�L�����f���f�[�^
bool			h_flag = false;

Heal::Heal()
{
}


Heal::~Heal()
{
}

void Heal::Init(CVector3 position, CQuaternion rotation)
{
	//���f���f�[�^�����[�h
	if (!h_flag) {
		h_OriginSkinModelData.LoadModelData("Assets/modelData/item.x", NULL);
		h_flag = true;
	}
	//CSkinModel��������
	skinModelData.CloneModelData(h_OriginSkinModelData, NULL);
	skinModel.Init(&skinModelData);

	//�f�t�H���g���C�g�ݒ�
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//���[���h�s����쐬(��񂾂�)
	skinModel.Update(position, rotation, CVector3::One);

	m_position = position;		//�ʒu���L�^

}

void Heal::Update()
{
	//�G�ƃv���C���[�̋������v�Z
	float length = g_player->Distance(m_position);

	//�v���C���[�ƐڐG���������
	if (length <= 2.0f) {
		//�v���C���[���񕜂����������
		if (g_player->healing()) {
			DeleteGO(this);
		}
	}

}

void Heal::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}