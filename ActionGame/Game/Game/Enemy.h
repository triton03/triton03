/*
	�G�̊�{�N���X
*/

#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Init(CVector3 FirstPosition);
	void Update();
	void Render(CRenderContext& renderContext);
	virtual void Move();			//����
	virtual void Damage();

protected:
	//���[�V����
	enum AnimationNo {
		AnimationDeath,		//��
		AnimationRun,		//����
		AnimationStand,		//����
	};

	CAnimation			animation;			//�A�j���[�V�����B
	AnimationNo			currentAnimSetNo;	//���̃��[�V����
	AnimationNo			anim;				//�ύX�O�̃��[�V����

	char filePath[256];	//�t�@�C���p�X

	struct Status
	{
		int					hp;		//�̗�
		int					score;	//�|�����Ƃ��̃X�R�A
	};

	CSkinModel				skinModel;					//�X�L�����f��
	CSkinModelData			skinModelData;				//�X�L�����f���f�[�^�B
	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[

	CVector3				position;					//�v���C���[�̍��W
	CVector3				centralPos;					//�v���C���[�̒��S�̍��W
	const CVector3			central = { 0.0f, 1.8f,0.0f };	//�v���C���[�̐^�񒆂̍���

	CVector3				move = CVector3::Zero;

	CQuaternion				rotation = CQuaternion::Identity;	//��]

	//CAnimation		animation;			//�A�j���[�V�����B
	//AnimationNo		currentAnimSetNo;	//���̃��[�V����
	//AnimationNo		anim;				//�ύX�O�̃��[�V����

	Status state;	//�G�̃X�e�[�^�X

	float length = 0.0f;	//�v���C���[�Ƃ̋���

	bool workFlag = false; 
};