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

	//�f�t�H���g���C�g�ݒ�
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//���[���h�s����쐬(��񂾂�)
	skinModel.Update(position, rotation, CVector3::One);

	m_position = position;		//�ʒu���L�^

}

void Item::Update()
{
	if (scene->isDelete()) {
		DeleteGO(this);
	}

	//�G�ƃv���C���[�̋������v�Z
	float length = g_player->Distance(m_position);

	//�v���C���[�ƐڐG���������
	if (length <= 2.0f) {
		//����
		Work();
	}

}

void Item::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}

void Item::Work() {};