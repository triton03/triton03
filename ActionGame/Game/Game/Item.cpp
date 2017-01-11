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

	this->position = position;		//�ʒu���L�^
	this->rotation = rotation;

}

void Item::Update()
{
	if (scene->isDelete()) {
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	//�G�ƃv���C���[�̋������v�Z
	length = g_player->Distance(position);

	if (!workFlag) {
		if (length > 40.0f) { return; }
		workFlag = true;
	}

	//�v���C���[�ƐڐG���������
	if ((length <= 2.0f) && (g_player->GetInfo()==Player::None)) {
		//����
		Work();
	}
	skinModel.Update(position, rotation, CVector3::One);
}

void Item::Render(CRenderContext& renderContext)
{
	if (length > 40.0f) { return; }
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}

void Item::Work() {};