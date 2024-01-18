#include "stdafx.h"
#include "CGhost.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "Bullet.h"
#include "ObjMgr.h"

CGhost::CGhost()
{
}

CGhost::~CGhost()
{
}

void CGhost::Initialize()
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 10.f;
	m_iHealth = 10.0f;
	m_iMaxHealth = 10.0f;
	m_OBJID = MONSTER;
	m_vGravity = {0, 0};
}

int CGhost::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Set_Pos(m_tInfo + m_vVelocity * 0.1f);
	m_vVelocity = m_vVelocity + m_vGravity * 0.1f;

	CObj* Player = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	if ((0 == GetTickCount() % 100) && (0 == m_vGravity.y))
		if (abs(Player->Get_Info().fX - m_tInfo.fX) < 500)
		{
			if (Player->Get_Info().fX < m_tInfo.fX)
				m_vVelocity.x = -1 * m_fSpeed;
			else
				m_vVelocity.x = 1 * m_fSpeed;

			CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 270));
			CObjMgr::Get_Instance()->Last_Obj(BULLET)->Set_IsPlayer(false);
		}

	return OBJ_NOEVENT;
}

void CGhost::Late_Update()
{
	CLineMgr::Get_Instance()->Collision_Line(this);
	CLineMgr::Get_Instance()->Collision_Box(this);

	if (0 >= m_iHealth)
		m_bDead = true;

	__super::Update_Rect();
}

void CGhost::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		m_tRect.right + iScrollX,
		m_tRect.bottom + iScrollY);

	TCHAR	szCnt[32] = L"";

	swprintf_s(szCnt, L"G");

	TextOut(hDC, m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY - 20, szCnt, lstrlen(szCnt));

	ShowHpBar(hDC, false, iScrollX, iScrollY);
}

void CGhost::Release()
{

}

void CGhost::OnColision(CObj* Oppnent)
{

}

void CGhost::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{
	if ((OBJID::PLAYER == Oppnent->Get_OBJID()) && (INVADEDIRC::TOP == Direc))
		m_bDead = true;

	if ((OBJID::BULLET == Oppnent->Get_OBJID()) && (true == Oppnent->Get_Special(OBJSPECIAL::GRAVITY)))
		m_vGravity = { 0,100 };

	//Oppnent->Set_YSpeed(-50);
}
// 플레이어가 고스트를 위에서 밟은 것 구현 