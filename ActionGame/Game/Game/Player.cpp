#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player* g_player;

namespace {
	const CVector3 FirstPosition = { 0.0f, 3.5f ,0.0f};	//�ŏ��̈ʒu
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start() {
	skinModelData.LoadModelData("Assets/modelData/sorcerer_A.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_defaultLight);			//�f�t�H���g���C�g��ݒ�B

	position = FirstPosition;
	centralPos.Add(position, central);
	characterController.Init(0.5f, 1.0f, position);	//�L�����N�^�R���g���[���̏������B

	//animation.SetAnimationEndTime(AnimationRun, 0.8);
	//animation.PlayAnimation(AnimationStand);

//���ʉ��Z�b�g
	JumpSound.Init("Assets/sound/Jump.wav");
	damageSound.Init("Assets/sound/damage.wav");
	deathSound.Init("Assets/sound/death.wav");
	ShotSound.Init("Assets/sound/Shot.wav");
	GetCoinSound.Init("Assets/sound/get.wav");
	HealingSound.Init("Assets/sound/cure.wav");

	state.hp = HP_MAX;
	state.coinNum = 0;
}

//�X�e�[�^�X���Z�b�g
void Player::Reset() {
	info = None;

	position = FirstPosition;		//�v���C���[�̍��W���Z�b�g
	characterController.SetPosition(position);

	rotation = CQuaternion::Identity;	//��]
	angle = { 0.0f,0.0f,1.0f };			//��]�l?

	state.hp = HP_MAX;
	state.coinNum = 0;

	timer = 0.0f;
}

void Player::Update()
{
	//�T�E���h�X�V
	JumpSound.Update();
	damageSound.Update();
	deathSound.Update();
	ShotSound.Update();
	GetCoinSound.Update();
	HealingSound.Update();

	//�A�j���[�V�����X�V
	//animation.Update(1.0f / 30.0f);
	//anim = currentAnimSetNo;

	if (info == isDeath){
		timer += GameTime().GetFrameDeltaTime();

		//����ł���o��������
		if (timer > 1.3) {
			Reset();
		}
	}
	else if (info == isDamage) {
		timer += GameTime().GetFrameDeltaTime();

		//�_���[�W�󂯂Ă���o��������
		if (timer > 0.4) {
			info = None;
		}
	}

	//������
	if (centralPos.y < -10.0f) {
		state.hp = 0;
		info = isDeath;
		deathSound.Play(false);
	}

	if (info == None) {
		characterController.SetMoveSpeed(Move());	//�ړ����x��ݒ�
	}


	characterController.Execute();			//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
	centralPos.Add(position, central);

//���[�V�������ς���Ă���ύX����
	//if (currentAnimSetNo != anim) {
	//	animation.PlayAnimation(currentAnimSetNo);
	//}
	skinModel.Update(position, rotation, CVector3::One);

}


//�v���C���[�̓���
CVector3 Player::Move()
{
	//�L�����N�^�[�̈ړ����x
	CVector3 move = characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * speed;
	move.z = -Pad(0).GetLStickYF() * speed;

	//A�{�^���ŃW�����v
	if (Pad(0).IsTrigger(enButtonA) && !characterController.IsJump()) {
		move.y = 10.0f;
		characterController.Jump();
		JumpSound.Play(false);	//���ʉ��Đ�
	}

	if (!isBullet) {
		timer += GameTime().GetFrameDeltaTime();

		//�O�̒e���łĂ���o��������
		if (timer > 0.4) {
			isBullet = true;
			timer = 0.0f;
		}
	}
	//B�{�^���Œe����
	if (Pad(0).IsPress(enButtonB) && isBullet) {
		ShotSound.Play(false);
		bullet[bulletNum] = NewGO<Bullet>(0);
		bulletNum = (bulletNum + 1) % 8;
		isBullet = false;
	}
	if (move.x != 0.0f || move.z != 0.0f)
	{
		angle.x = -Pad(0).GetLStickXF();
		angle.z = -Pad(0).GetLStickYF();

		//�����ύX
		rotation.SetRotation(CVector3::AxisY, atan2f(angle.x, angle.z));
	}

	return move;
}

void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
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
	float b_speed = 12.0f;
	back.x *= b_speed;
	back.y *= b_speed;

	characterController.SetMoveSpeed(back);	//�ړ����x��ݒ�
	characterController.Execute();			//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
	centralPos.Add(position, central);
	skinModel.Update(position, rotation, CVector3::One);

	timer = 0.0f;
}

//�R�C���l��
void Player::CoinGet() 
{
	state.coinNum++;
	GetCoinSound.Play(false);	//���ʉ��Đ�
}


//�񕜃A�C�e���l��(�񕜂�������Ԃ�)
bool Player::healing()
{	//HP�����^���Ȃ̂ŉ񕜂ł��Ȃ�
	if (state.hp == HP_MAX || info==isDeath) { return false; }

	state.hp++;
	HealingSound.Play(false);
	return true;
}