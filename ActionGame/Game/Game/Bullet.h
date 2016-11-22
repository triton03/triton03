/*
	�U���̒e
*/

#pragma once
class Bullet :public IGameObject
{
public:


	Bullet();
	~Bullet();
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CVector3		position;		//�|�W�V����
	CVector3		angle;			//�e�̕���?

	CVector3		origin;			//�ŏ��̈ʒu
	CSkinModelData	modelData;		//���f���f�[�^
	CSkinModel		model;			//���f��

	const float		speed = 1.8f;
};