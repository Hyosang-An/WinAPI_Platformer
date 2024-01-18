#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
	
public:
	INFO		Get_Info() { return m_tInfo; }
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_Direction(DIRECTION eDir) { m_eDir = eDir; }
	RECT		Get_Rect() { return m_tRect; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

	void		Move_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Move_PosY(float _fY) { m_tInfo.fY += _fY; }
	void		Set_Pos(Vector2D _pos) { m_tInfo.fX = _pos.x; m_tInfo.fY = _pos.y; }
	Vector2D	Get_Pos() { return Vector2D(m_tInfo.fX, m_tInfo.fY); }
	bool		Get_Dead() { return m_bDead; }

	Vector2D	Get_Velocity() { return m_vVelocity; }
	float		Get_Speed() { return sqrt(m_vVelocity.x * m_vVelocity.x + m_vVelocity.y * m_vVelocity.y); }
	void		Set_YVelocity(float _yspeed) { m_vVelocity.y = _yspeed; }
	OBJID		Get_OBJID() { return m_OBJID; } // <- OBJ Ÿ�� Ȯ�� �Լ�
	int			Get_Health() { return m_iHealth; } // <- ü�� Ȯ�� �Լ�
	int			Get_Attack() { return m_iAttack; } // <- ���� Ȯ�� �Լ�
	bool		Get_Special(OBJSPECIAL input) { return m_vecSpecial[int(input)]; }
	bool		Get_IsPlayer() { return m_bPlayer; }
	void		Set_IsPlayer(bool Isplayer) { m_bPlayer = Isplayer; }
	void		ShowHpBar(HDC hDC, bool IsPlayer, float ScrollX, float ScrollY);
	void		Set_Special_True(OBJSPECIAL input) { m_vecSpecial[int(input)] = true; }

public:
	virtual void Initialize()		PURE;
	virtual int	 Update()			PURE;
	virtual void Late_Update()		PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release()			PURE;
	virtual void OnColision(CObj* Oppnent)		PURE; // ���浹 ��, this���� ������ ���� ����
	virtual void OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)		PURE; // ��Ʈ�浹 ��, this���� ������ ���� ����
	

protected:
	void		Update_Rect();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	Vector2D	m_vVelocity = Vector2D();
	Vector2D	m_vGravity{ 0, 1.7 * 9.8 };

	float		m_fSpeed;
	float		m_fAngle;
	float		m_fDistance;

	DIRECTION	m_eDir;
	bool		m_bDead;

	CObj*		m_pTarget;
	int			m_iHealth; // <- ü�� ����
	int			m_iMaxHealth; // <- �ִ� ü�� ����
	int			m_iAttack; // <- ���� ���� 
	int			m_iMaxAttack; // <- �ִ� ���ݷ�
	OBJID		m_OBJID; // <- Obj Ÿ��
	vector<bool>	m_vecSpecial; // <- ����� Ư�� �ο�
	bool		m_bPlayer;
};

