/*
	プレイヤーの攻撃の弾
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
	CVector3		position;		//ポジション
	CVector3		angle;			//弾の方向?

	CVector3		origin;			//最初の位置
	CSkinModelData	modelData;		//モデルデータ
	CSkinModel		model;			//モデル

	CSoundSource*	SE;

	const float		speed = 1.8f;
	bool			flag;	//消滅フラグ

};

extern Bullet*				bullet[BulletMAX];