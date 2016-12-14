/*
	�v���C���[
*/

#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Bullet.h"

class Player : public IGameObject
{
public:
	//�v���C���[�̏��
	enum PlayerInfo {
		None,		//�ʏ�
		isDamage,	//�_���[�W�󂯂�
		isDeath,	//���ꂿ�����
		isClear,	//�N���A
	};
	const int	HP_MAX = 3;	//�v���C���[�̍ő�HP
	const CVector3	central = { 0.0f, 1.8f,0.0f };	//�v���C���[�̐^�񒆂̍���

/*�����o�֐�*/
	Player();
	~Player();
	void Start();
	void Reset();
	void Update();
	CVector3 Move();
	void Render(CRenderContext& renderContext);

	float Distance(CVector3& objectPos);	//�v���C���[�Ƃ̋�����Ԃ�
	void Damage(CVector3 e_pos);		//�_���[�W����
	bool healing();

/*�Q�b�^�[*/
	CVector3 GetPosition() {	//�v���C���[�̈ʒu��Ԃ�
		return centralPos;
	}

	CVector3 GetMoveAngle() {	//����?��Ԃ�
		return angle;
	}

	int GetHP() const		//����HP�Ԃ�
	{
		return state.hp;
	}
	PlayerInfo GetInfo() {		//���̏�Ԃ�Ԃ�
		return info;
	}
	float GetTime() {
		return state.time;
	}
	int GetScore() {
		return state.score;
	}

	bool isStop() {
		return StopFlag;
	}

/*�Z�b�^�[*/
	void SetScore(int s) {
		state.score += s;
	}
	void SetClear() {
		info = isClear;
	}
	void SetFullHP() {
		state.hp = HP_MAX;
	}
	void ReStart() {
		StopFlag = false;
		info = None;
	}

private:
	//�v���C���[�̃X�e�[�^�X
	struct Status
	{
		int			hp;			//�v���C���[��HP
		int			score;		//�l���X�R�A
		float		time;
	};

//���[�V����
	enum AnimationNo {
		AnimationStand,		//����
		AnimationRun,		//����
		AnimationDeath,		//�W�����v
	};

/*�����o�ϐ�*/

	CSkinModel				skinModel;					//�X�L�����f��
	CSkinModelData			skinModelData;				//�X�L�����f���f�[�^�B
	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[

	CVector3				position ;					//�v���C���[�̍��W
	CVector3				centralPos;					//�v���C���[�̒��S�̍��W
	CQuaternion				rotation = CQuaternion::Identity;	//��]
	CVector3				angle = { 0.0f,0.0f,1.0f };			//��]�l?

	CAnimation			animation;			//�A�j���[�V�����B
	AnimationNo			currentAnimSetNo;	//���̃��[�V����
	AnimationNo			anim;				//�ύX�O�̃��[�V����

	CSoundSource		JumpSound;		//�W�����v�{�C�X
	CSoundSource		damageSound;	//�_���[�W�{�C�X
	CSoundSource		deathSound;		//����{�C�X

	Status				state;			//�v���C���[�̃X�e�[�^�X
	Status				total;			//���v
	PlayerInfo			info = None;	//�v���C���[�̏��

	int					bulletNum = 0;
	bool				isBullet=true;	//�e�t���O
	bool				StopFlag;

	float				timer = 0.0f;	//�^�C�}�[�B

};
extern Player* g_player;