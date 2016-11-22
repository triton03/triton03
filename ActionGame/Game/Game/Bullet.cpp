#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Camera.h"

CSkinModelData	b_OriginSkinModelData;	//�X�L�����f���f�[�^
bool			b_flag = false;		//���łɓǂݍ���ł��邩

Bullet::Bullet()
{
	//���f���f�[�^�����[�h(1�񂾂�)
	if (!b_flag) {
		b_OriginSkinModelData.LoadModelData("Assets/modelData/bullet.x", NULL);
		b_flag = true;
	}
	//CSkinModel��������
	modelData.CloneModelData(b_OriginSkinModelData, NULL);
	model.Init(&modelData);

	//�f�t�H���g���C�g�Z�b�g
	model.SetLight(&g_defaultLight);

	position = g_player->GetPosition();

	angle = g_player->GetMoveAngle();
	angle.Normalize();			//���K��

	position.x += angle.x * 0.1f;
	position.z += angle.z * 0.1f;

	origin = position;		//�ŏ��̈ʒu���L�^
}


Bullet::~Bullet()
{
}

void Bullet::Update() {
	CVector3 diff;

	//�ړ������������v�Z
	diff.Subtract(position, origin);
	float lendth = diff.Length();

	//���C
	if (lendth > 80.0f || lendth < -80.0f) {
		DeleteGO(this);
	}

	//�e�ړ�
	position.x += angle.x* speed;
	position.z += angle.z* speed;

	model.Update(position, CQuaternion::Identity, CVector3::One);
}

void Bullet::Render(CRenderContext& renderContext) {
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}