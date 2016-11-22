/*
	�񕜃A�C�e��
*/

#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"

class Heal : public IGameObject
{
public:
	Heal();
	~Heal();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CSkinModel		skinModel;		//�X�L�����f��
	CSkinModelData	skinModelData;	//�X�L�����f���f�[�^

	CVector3	m_position;	//�R�C���̈ʒu
	bool get_flag = false;	//�Q�b�g������
};

