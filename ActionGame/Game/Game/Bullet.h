/*
	プレイヤーの攻撃の弾
*/

#pragma once
class Bullet :public IGameObject
{
public:


	Bullet();
	~Bullet();
	void Update();
	void Render(CRenderContext& renderContext);
	float Distance(CVector3& objectPos);
	bool flag = false;	//消滅フラグ

private:
	CVector3		position;		//ポジション
	CVector3		angle;			//弾の方向?

	CVector3		origin;			//最初の位置
	CSkinModelData	modelData;		//モデルデータ
	CSkinModel		model;			//モデル

	const float		speed = 1.8f;
};

extern Bullet*				bullet[8];