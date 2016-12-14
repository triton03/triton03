/*
	�A�C�e���̊�{�N���X
*/

#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"

class Item : public IGameObject
{
public:
	Item();
	~Item();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	virtual void Work();

protected:
	CSkinModel		skinModel;		//�X�L�����f��
	CSkinModelData	skinModelData;	//�X�L�����f���f�[�^

	CVector3			position;	//�A�C�e���̈ʒu
	CQuaternion			rotation;

	bool get_flag = false;	//�Q�b�g������

};

