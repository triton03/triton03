/*
	数字表示クラス
*/

#pragma once
class Number : public IGameObject
{
public:
	Number();
	~Number();
	void Start() override;
	void Init(CVector2 pos);
	void Update() override;
	void NumSet(int n);
	void PostRender(CRenderContext& renderContext) override;

private:
	CSprite		m_number[10];		//数字のスプライト
	CTexture	m_numberTex[10];	//数字のテクスチャ
	int			num=0;				//表示する数字
};