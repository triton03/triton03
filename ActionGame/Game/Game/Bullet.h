/*
	�v���C���[�̍U���̒e
*/
#define BulletMAX 5

#pragma once
class Bullet :public IGameObject
{
public:


	Bullet();
	~Bullet();
	void Update();
	void Render(CRenderContext& renderContext);
	float Distance(CVector3& objectPos);

	void SetFlag(bool F) {
		flag = F;
	}
	bool GetFlag() {
		return flag;
	}

private:
	CVector3		position;		//�|�W�V����
	CVector3		angle;			//�e�̕���?

	CVector3		origin;			//�ŏ��̈ʒu
	CSkinModelData	modelData;		//���f���f�[�^
	CSkinModel		model;			//���f��

	CSoundSource*	SE;

	const float		speed = 1.8f;
	bool			flag;	//���Ńt���O

};

extern Bullet*				bullet[BulletMAX];