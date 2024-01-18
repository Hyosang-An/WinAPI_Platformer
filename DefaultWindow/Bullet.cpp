#include "stdafx.h"
#include "Bullet.h"
#include "LineMgr.h"
#include "ScrollMgr.h"

CBullet::CBullet() :
	m_iTime(0)
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
	m_iAttack = 10.0f;
	m_OBJID = BULLET;
	m_bPlayer = false;
	m_iTime = GetTickCount();
}

int CBullet::Update()
{
	if (CLineMgr::Get_Instance()->Collision_Line(this) || CLineMgr::Get_Instance()->Collision_Box(this))
		m_bDead = true;

	if (m_iTime + 2000 < GetTickCount())
		return OBJ_DEAD;

	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}
void CBullet::Late_Update()
{
	m_tInfo.fX += m_fSpeed * cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sin(m_fAngle * (PI / 180.f));

	__super::Update_Rect();
}

void CBullet::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CBullet::Release()
{
}

void CBullet::OnColision(CObj* Oppnent)
{
	if ((OBJID::PLAYER == Oppnent->Get_OBJID()) && (!m_bPlayer)) 
		m_bDead = true;
}

void CBullet::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{
	if ((OBJID::PLAYER == Oppnent->Get_OBJID()) && (!m_bPlayer))
		m_bDead = true;
}

