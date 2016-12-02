/*
	�}�b�v�`�b�v
*/

#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class MapChip : public IGameObject
{
public:
	MapChip();
	~MapChip();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CSkinModel		skinModel;		//�X�L�����f��
	CSkinModelData	skinModelData;	//�X�L�����f���f�[�^
	CMeshCollider	meshColloder;	//���b�V���R���C�_�[
	CRigidBody		rigidBody;		//����
};

