#include "stdafx.h"
#include "Coin.h"
#include "Camera.h"
#include "Player.h"

CSkinModelData	OriginSkinModelData;	//�X�L�����f���f�[�^
bool			flag = false;

Coin::Coin()
{
}


Coin::~Coin()
{
}

void Coin::Init(CVector3 position, CQuaternion rotation)
{
	//���f���f�[�^�����[�h
	if (!flag) {
		OriginSkinModelData.LoadModelData("Assets/modelData/coin.x", NULL);
		flag = true;
	}
	//CSkinModel��������
	skinModelData.CloneModelData(OriginSkinModelData, NULL);
	skinModel.Init(&skinModelData);

	//�f�t�H���g���C�g�ݒ�
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//���[���h�s����쐬(��񂾂�)
	skinModel.Update(position, rotation, CVector3::One);

	m_position = position;	//�ʒu���L��

}

void Coin::Update()
{

	//�G�ƃv���C���[�̋������v�Z
	float length = g_player->Distance(m_position);

	//�v���C���[�ƐڐG���������
	if (length <= 2.0f) {
		g_player->CoinGet();
		DeleteGO(this);
	}

}

void Coin::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}