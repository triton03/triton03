/*
	カメラ
	(プレイヤー追従)
*/

#pragma once
class Camera:public IGameObject
{
public:
	Camera();
	~Camera();
	void Start();
	void Update();

	const CMatrix& GetViewMatrix() const 
	{
		return camera.GetViewMatrix();
	}

	const CMatrix& GetProjectionMatrix() const
	{
		return camera.GetProjectionMatrix();
	}

private:
	CCamera		camera;			//カメラ
	CVector3	playerDist;		//カメラの位置
	CVector3	cameraPos;
	CVector3	target;
	float		timer;
};

extern Camera* gameCamera;

