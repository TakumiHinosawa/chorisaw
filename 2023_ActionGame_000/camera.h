//=========================================================================================
//
//カメラ [camera.h]
//Author:日野澤匠泉
//
//=========================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************************
//インクルード
//*****************************************************************************************
#include "main.h"

//*****************************************************************************************
//クラス宣言
//*****************************************************************************************
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void RotCamera(void);
	static D3DXVECTOR3 GetRotCamera(void);

private:
	D3DXMATRIX m_mtxView;				//ビューマトリックス
	D3DXMATRIX m_mtxProjection;			//プロジェクションマトリックス
	D3DVIEWPORT9 m_viewport;				//ビューポート
	D3DXVECTOR3 m_posV;					//視点
	D3DXVECTOR3 m_posR;					//注視点
	D3DXVECTOR3 m_posVDest;				//目的の視点
	D3DXVECTOR3 m_posRDest;				//目的の注視点
	D3DXVECTOR3 m_vecR;					//上方向ベクトル
	static D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_move;					//移動量
	D3DXVECTOR3 m_rotDest;				//目標の角度
	int m_nType;						//タイプ
};

#endif
