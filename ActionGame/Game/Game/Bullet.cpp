#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Camera.h"

CSkinModelData	b_OriginSkinModelData;	//�X�L�����f���f�[�^
bool			b_flag = false;		//���łɓǂݍ���ł��邩

Bullet*				bullet[BulletMAX];		//�e���i�[

Bullet::Bullet()
{
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
	flag = false;

	CSoundSource* SE = NewGO<CSoundSource>(0);
	SE->Init("Assets/sound/Shot.wav");
	SE->Play(false);
}


Bullet::~Bullet()
{
}

void Bullet::Update() {
	if (flag) { return; }

	CVector3 diff;

	//�ړ������������v�Z
	diff.Subtract(position, origin);
	float lendth = diff.Length();

	//���C
	if (lendth > 30.0f) {
		flag = true;
	}

	//�e�ړ�
	position.x += angle.x* speed;
	position.z += angle.z* speed;

	model.Update(position, CQuaternion::Identity, CVector3::One);
}

void Bullet::Render(CRenderContext& renderContext) {
	if (flag) { return; }
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}

//�e�ƑΏۂ̋������v�Z
float Bullet::Distance(CVector3& objectPos)
{
	if (flag) { return 10; }

	CVector3 diff;

	//�v���C���[�̍��W����G�̍��W�����Z
	diff.Subtract(position, objectPos);
	//�G�ƃv���C���[�̋������v�Z
	return diff.Length();
}