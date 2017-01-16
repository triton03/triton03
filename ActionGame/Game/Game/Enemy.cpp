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

	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_defaultLight);			//�f�t�H���g���C�g��ݒ�B
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	position = pos;
	centralPos.Add(position, central);

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(90.0f));

	characterController.Init(0.5f, 1.0f, position);	//�L�����N�^�R���g���[���̏������B

	//animation.SetAnimationEndTime(AnimationRun, 0.8);
	//animation.PlayAnimation(AnimationStand);
}

void Enemy::Update()
{
	//HP��0�ɂȂ���
	if (scene->isDelete() || state.hp <= 0) {
		g_player->SetScore(state.score);
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	length = g_player->Distance(centralPos);
	if (!workFlag) {
		if (length > Limit) { return; }
		workFlag = true;
	}

	//�A�j���[�V�����X�V
	//animation.Update(1.0f / 30.0f);
	//anim = currentAnimSetNo;

	//������
	if (centralPos.y < -10.0f) {
		state.hp = 0;
	}

	if (length <= 3.0f) {
		g_player->Damage(centralPos);
	}

	this->Damage();

	move = characterController.GetMoveSpeed();

	//����
	Move();

	characterController.SetMoveSpeed(move);		//�ړ����x��ݒ�
	characterController.Execute();					//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
	centralPos.Add(position, central);

	skinModel.Update(position, rotation, CVector3::One);
}

//����
void Enemy::Move()
{

}

void Enemy::Damage()
{
	if (g_player->GetInfo() == Player::isClear) { return; }
	if (length > (Limit-4.5f)) { return; }

	for (int i = 0; i < BulletMAX; i++) {

		if (bullet[i] == nullptr) { continue; }

		if (bullet[i]->Distance(centralPos) < 3.0) {
			state.hp--;
			bullet[i]->SetFlag(true);
			DeleteGO(bullet[i]);
			bullet[i] = nullptr;

			CSoundSource* SE = NewGO<CSoundSource>(0);
			if (state.hp > 0) {
				SE->Init("Assets/sound/hit.wav");
			}
			else {
				SE->Init("Assets/sound/enemy_death.wav");
			}
			SE->Play(false);
		}
	}
}

void Enemy::Render(CRenderContext& renderContext)
{
	if (length > Limit) { return; }
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}