/*
	エネミーの攻撃の弾
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
	CVector3		position;		//ポジション

	CVector3		origin;			//最初の位置
	CSkinModelData	modelData;		//モデルデータ
	CSkinModel		model;			//モデル

	CVector3		angle;

	const float		speed = 1.8f;
	bool			flag;	//消滅フラグ
};

extern CSkinModelData	eb_OriginSkinModelData;	//スキンモデルデータ
extern bool				eb_flag;		//すでに読み込んでいるか