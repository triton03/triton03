/*
	�N���A�}�[�J�[
*/

#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"

class ClearMarker : public IGameObject
{
public:
	ClearMarker();
	~ClearMarker();
	void Init(CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CSkinModel			skinModel;		//�X�L�����f��
	CSkinModelData		skinModelData;	//�X�L�����f���f�[�^

	CVector3			position;	//�}�[�J�[�̈ʒu
	CQuaternion			rotation;
	bool				flag = false;	//�N���A�t���O
};

