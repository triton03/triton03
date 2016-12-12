#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "Bullet.h"
#include "SceneManager.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	characterController.RemoveRigidBoby();
}

void Enemy::Init(CVector3 pos)
{
	skinModelData.LoadModelData(filePath, NULL);

	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_defaultLight);			//�f�t�H���g���C�g��ݒ�B
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	position = pos;
	centralPos.Add(position, central);

	characterController.Init(0.5f, 1.0f, position);	//�L�����N�^�R���g���[���̏������B

	//animation.SetAnimationEndTime(AnimationRun, 0.8);
	//animation.PlayAnimation(AnimationStand);
}

void Enemy::Update()
{
	//�A�j���[�V�����X�V
	//animation.Update(1.0f / 30.0f);
	//anim = currentAnimSetNo;

	//������
	if (position.y < -5.0f) {
		state.hp = 0;
	}

	float length = g_player->Distance(centralPos);

	if (length <= 3.0f) {
		g_player->Damage(centralPos);
	}

	this->Damage();

	//HP��0�ɂȂ���
	if (scene->isDelete()|| state.hp <= 0) {
		g_player->SetScore(state.score);
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	//����
	Move();

	//characterController.SetMoveSpeed(move);		//�ړ����x��ݒ�
	characterController.Execute();					//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
	centralPos.Add(position, central);

	skinModel.Update(position, rotation, CVector3::One);
}

void Enemy::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}

//����
void Enemy::Move()
{

}

void Enemy::Damage()
{
	for (int i = 0; i < 8; i++) {
		if (bullet[i] == nullptr) {	continue;}

		if (bullet[i]->Distance(position) < 3.0) {
			state.hp--;
			bullet[i]->flag = true;
		}
	}
}