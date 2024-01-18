#pragma once
#include "Obj.h"
class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnColision(CObj* Oppnent) override;
	virtual void OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize) override;
	bool		 Get_Reflect() { return m_bReflect; }

private:
	void		Key_Input();
	void		Offset();

private:
	POINT			m_tPosin;

	bool			m_bJump;		// 점프 상태 확인	
	bool			m_bJumpStart = false;
	float			m_fInitialY;
	float			m_fJumpPower;	// 힘의 크기
	float			m_fTime;		// 점프 중 진행 시간 

	float			m_fSpeed_y = 0;
	bool			m_bReflect;
	int				m_iGravityGun;

	ULONGLONG		m_lBeforeTickCnt = 0;

	Vector2D		prev_Pos;
};

