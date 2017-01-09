#include "stdafx.h"
#include "Player.h"
#include "Camera.h"
#include "SceneManager.h"

Player* g_player;

namespace {
	const CVector3 FirstPosition = { 0.0f, 5.0f ,0.0f};	//�ŏ��̈ʒu
}

Player::Player()
{
}

Player::~Player()
{
	skinModel.SetShadowCasterFlag(false);
	skinModel.SetShadowReceiverFlag(false);
	characterController.RemoveRigidBoby();
}

void Player::Start() {
	//�e�̃��f���f�[�^�����[�h(1�񂾂�)
	if (!b_flag) {
		b_OriginSkinModelData.LoadModelData("Assets/modelData/bullet.x", NULL);
		b_flag = true;
	}

	//���f���̓ǂݍ���
	skinModelData.LoadModelData("Assets/modelData/sorcerer_A.X", &animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_defaultLight);	//�f�t�H���g���C�g��ݒ�B
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	CVector3 lightPos = CVector3(0.0f, 25.5f, 24.5f);
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(position);
	toLightPos.Subtract(lightPos, position);
	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(270.0f));

	position = FirstPosition;			//�|�W�V�����̐ݒ�
	centralPos.Add(position, central);	//���f���̒��S��ݒ�
	characterController.Init(0.5f, 1.0f, position);	//�L�����N�^�R���g���[���̏������B

	animation.SetAnimationLoopFlag(AnimationDeath, false);
	animation.PlayAnimation(AnimationStand);

//���ʉ��Z�b�g
	JumpSound.Init("Assets/sound/Jump.wav");
	damageSound.Init("Assets/sound/damage.wav");
	deathSound.Init("Assets/sound/death.wav");

	state.hp = HP_MAX;
	state.score = 0;
	state.time = 0.0f;

	total.score = 0;
	total.time = 0.0f;

	StopFlag=false;
}

//���Z�b�g
void Player::Reset() {
	position = FirstPosition;		//�v���C���[�̍��W���Z�b�g
	characterController.SetPosition(position);
	characterController.SetMoveSpeed(CVector3::Zero);
	characterController.Execute();

	//rotation = CQuaternion::Identity;	//��]
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(270.0f));
	angle = { -1.0f,0.0f,0.0f };			//��]�l?

	state.score = 0;
	state.time = 0.0f;

	timer = 0.0f;

	currentAnimSetNo = AnimationStand;
	animation.PlayAnimation(currentAnimSetNo);
	centralPos.Add(position, central);

	bulletNum = 0;
	for (int i = 0; i < BulletMAX; i++) {
		bullet[i] = nullptr;
	}

	skinModel.Update(position, rotation, CVector3::One);
}

void Player::Update()
{

	//�T�E���h�X�V
	JumpSound.Update();
	damageSound.Update();
	deathSound.Update();

	//�A�j���[�V�����X�V
	animation.Update(1.0f / 30.0f);
	anim = currentAnimSetNo;

	//�e�Ǘ�
	for (int i = 0; i < BulletMAX; i++) {
		if (bullet[i] != nullptr && bullet[i]->GetFlag()) {
			DeleteGO(bullet[i]);
			bullet[i] = nullptr;
		}
	}

	//�v���C���[��~��Ԃ�
	if (StopFlag) { return; }

	//����łȂ��Ƃ��̏���
	if (info != isDeath) {
		//�v���C���ԉ��Z
		if (info != isClear) {
			state.time += GameTime().GetFrameDeltaTime();	//�v���C���ԃJ�E���g
		}
		//������
		if (centralPos.y < -10.0f) {
			state.hp = 0;
			info = isDeath;
			deathSound.Play(false);
		}
	}

	switch (info) {
	//�ʏ펞
	case None:
		characterController.SetMoveSpeed(Move());	//�ړ����x��ݒ�
		break;

	//�_���[�W�󂯂�
	case isDamage:
		timer += GameTime().GetFrameDeltaTime();

		//�_���[�W�󂯂Ă���o��������
		if (timer > 0.5) {
			info = None;
		}
		break;

	//����
	case isDeath:
		currentAnimSetNo = AnimationDeath;
		timer += GameTime().GetFrameDeltaTime();

		//����ł���o��������
		if (timer > 1.3) {
			StopFlag = true;
		}
		break;

	//�N���A�����Ƃ��̓���
	case isClear:
		timer += GameTime().GetFrameDeltaTime();
		if (timer >= 1.0f) {
			rotation = CQuaternion::Identity;	//����������
		}
		if (timer >= 5.0f) {
			total.score += state.score;
			total.time += state.time;
			StopFlag=true;	//�v���C���[��~
		}
		characterController.SetMoveSpeed({0.0f,-5.0f,0.0f});
		break;
	}
	characterController.Execute();			//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
	centralPos.Add(position, central);

//���[�V�������ς���Ă���ύX����
	if (currentAnimSetNo != anim) {
		animation.PlayAnimation(currentAnimSetNo);
	}
	skinModel.Update(position, rotation, CVector3::One);

	//�e
	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);
}

//�v���C���[�̓���
CVector3 Player::Move()
{
	float		speed = 10.0f;
	//�W�����v���̑��x�␳
	if (characterController.IsJump()) {
		speed = speed * 0.8f;
	}

	//�L�����N�^�[�̈ړ����x
	CVector3 move = characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * speed;
	move.z = -Pad(0).GetLStickYF() * speed;

	//A�{�^���ŃW�����v
	if (Pad(0).IsTrigger(enButtonA) && !characterController.IsJump()) {
		move.y = 14.0f;
		characterController.Jump();
		JumpSound.Play(false);	//���ʉ��Đ�
	}

	if (!isBullet) {
		timer += GameTime().GetFrameDeltaTime();

		//�O�̒e���łĂ���o��������
		if (timer > 0.5) {
			isBullet = true;
			timer = 0.0f;
		}
	}
	//B�{�^���Œe����
	if (Pad(0).IsPress(enButtonB) && isBullet) {
		bullet[bulletNum] = NewGO<Bullet>(0);
		bulletNum = (bulletNum + 1) % BulletMAX;
		isBullet = false;
	}

	//�ړ����Ă�
	if (move.x != 0.0f || move.z != 0.0f)
	{
		if ((position.z > Range) && (move.z > 0)) {
			move.z = 0.0f;
		}
		else if ((position.z < -Range) && (move.z < 0)) {
			move.z = 0.0f;
		}
		if ((position.x > 2.5) && (move.x > 0)) {
			move.x = 0.0f;
		}

		angle.x = -Pad(0).GetLStickXF();
		angle.z = -Pad(0).GetLStickYF();

		currentAnimSetNo = AnimationRun;

		//�����ύX
		rotation.SetRotation(CVector3::AxisY, atan2f(angle.x, angle.z));
	}
	else {
		currentAnimSetNo = AnimationStand;	//�������[�V����
	}

	return move;
}

//�v���C���[�ƑΏۂ̋������v�Z���ĕԂ�
float Player::Distance(CVector3& objectPos) 
{
	CVector3 diff;

	//�v���C���[�̍��W����G�̍��W�����Z
	diff.Subtract(centralPos, objectPos);
	//�G�ƃv���C���[�̋������v�Z
	return diff.Length();
}

void Player::Damage(CVector3 ePos)
{
	if (info != None) { return; }

	state.hp --;

	if (state.hp == 0) { 
		deathSound.Play(false);
		info = isDeath;
	}
	else {
		info = isDamage;
		damageSound.Play(false);
	}

	CVector3 back;

	//�G�ƂԂ������炿����Ɣ���
	back = characterController.GetMoveSpeed();
	back.Subtract(centralPos, ePos);
	back.Normalize();

	//�����̂͂₳
	float b_speed = 4.3f;
	back.x *= b_speed;
	back.y *= b_speed;

	characterController.SetMoveSpeed(back);			//�ړ����x��ݒ�
	characterController.Execute();					//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
	centralPos.Add(position, central);
	skinModel.Update(position, rotation, CVector3::One);

	timer = 0.0f;
}

//�񕜃A�C�e���l��(�񕜂�������Ԃ�)
bool Player::healing()
{	//HP�����^���Ȃ̂ŉ񕜂ł��Ȃ�
	if (state.hp == HP_MAX) { return false; }

	state.hp++;
	return true;
}

void Player::Render(CRenderContext& renderContext)
{
	if (scene->isDelete()) { return; }

	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}