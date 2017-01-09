#include "stdafx.h"
#include "EnemyBullet.h"
#include "Player.h"
#include "Camera.h"
#include "SkeltonMage.h"
#include "SceneManager.h"


CSkinModelData	eb_OriginSkinModelData;	//�X�L�����f���f�[�^
bool			eb_flag = false;		//���łɓǂݍ���ł��邩

EnemyBullet::EnemyBullet()
{
	//CSkinModel��������
	modelData.CloneModelData(eb_OriginSkinModelData, NULL);
	model.Init(&modelData);

	//�f�t�H���g���C�g�Z�b�g
	model.SetLight(&g_defaultLight);

	position = CVector3::Zero;

	position.x +=  0.1f;

	origin = position;		//�ŏ��̈ʒu���L�^
	flag = false;

	SE = NewGO<CSoundSource>(0);
	SE->Init("Assets/sound/e_shot.wav");
	SE->Play(false);
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Init(CVector3 pos) {
	position = pos;
	origin = position;
}

void EnemyBullet::Update() {
	if (flag) { 
		DeleteGO(this);
	}

	CVector3 diff;

	//�ړ������������v�Z
	diff.Subtract(position, origin);
	float lendth = diff.Length();

	//���C
	if (lendth > 70.0f) {
		flag = true;
	}
	if ((scene->isDelete() )||(g_player->Distance(position) <= 3.0f)) {
		g_player->Damage(position);
		flag = true;
	}

	//�e�ړ�
	position.x +=  speed;

	model.Update(position, CQuaternion::Identity, CVector3::One);
}

void EnemyBullet::Render(CRenderContext& renderContext) {
	if (flag) { return; }
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}