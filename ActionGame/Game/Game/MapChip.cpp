#include "stdafx.h"
#include "MapChip.h"
#include "Camera.h"


MapChip::MapChip()
{
}


MapChip::~MapChip()
{
}

void MapChip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	//�t�@�C���p�X�쐬
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);

	//���f���f�[�^�����[�h
	skinModelData.LoadModelData(filePath, NULL);
	//CSkinModel��������
	skinModel.Init(&skinModelData);

	//�f�t�H���g���C�g�ݒ�
	skinModel.SetLight(&g_defaultLight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//���[���h�s����쐬(��񂾂�)
	skinModel.Update(position, rotation, CVector3::One);

	//���b�V���R���C�_�[�쐬
	meshColloder.CreateFromSkinModel(&skinModel, skinModelData.GetRootBoneWorldMatrix());

	RigidBodyInfo rbInfo;				//���̂̍쐬
	rbInfo.collider = &meshColloder;	//���̂̃R���C�_�[��n��

	rbInfo.mass = 0.0f;		//���̂̎���(0.0���Ɠ����Ȃ��I�u�W�F�N�g)
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rigidBody.Create(rbInfo);

	//�쐬�������̂𕨗����[���h�ɒǉ�
	PhysicsWorld().AddRigidBody(&rigidBody);
}

void MapChip::Update()
{
	//�������Ȃ�
}

void MapChip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext,gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}