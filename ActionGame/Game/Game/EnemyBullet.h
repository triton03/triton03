/*
	�G�l�~�[�̍U���̒e
*/
#pragma once
class EnemyBullet :public IGameObject
{
public:
	EnemyBullet();
	~EnemyBullet();
	void Init(CVector3 pos);
	void Update();
	void Render(CRenderContext& renderContext);

	void SetFlag(bool F) {
		flag = F;
	}
	bool GetFlag() {
		return flag;
	}

	void setAngle(CVector3 ang) {
		angle = ang;
	}

private:
	CVector3		position;		//�|�W�V����

	CVector3		origin;			//�ŏ��̈ʒu
	CSkinModelData	modelData;		//���f���f�[�^
	CSkinModel		model;			//���f��

	CVector3		angle;

	const float		speed = 1.8f;
	bool			flag;	//���Ńt���O
};

extern CSkinModelData	eb_OriginSkinModelData;	//�X�L�����f���f�[�^
extern bool				eb_flag;		//���łɓǂݍ���ł��邩