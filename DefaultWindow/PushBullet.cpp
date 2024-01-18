#include "stdafx.h"
#include "PushBullet.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

PushBullet::PushBullet()
	:m_fPushPower(50.f), m_iTime(0)
{
}

PushBullet::~PushBullet()
{
}

void PushBullet::Initialize() 
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 50.f;

	m_vVelocity = Vector2D(m_fSpeed * cos(m_fAngle * PI / 180.f), m_fSpeed * sin(m_fAngle * PI / 180.f));
	m_iAttack = 10.0f;
	m_OBJID = BULLET;
	m_vecSpecial[int(OBJSPECIAL::PUSH)] = true;
	m_iTime = GetTickCount();
}

int PushBullet::Update()
{
	if(m_iTime + 2000 < GetTickCount())
		return OBJ_DEAD;

	if (m_bDead)
		return OBJ_DEAD;


	Set_Pos(m_tInfo + m_vVelocity * 0.1f);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void PushBullet::Late_Update()
{
	//m_vVelocity = Vector2D(m_fSpeed * cos(m_fAngle * PI / 180.f), m_fSpeed * sin(m_fAngle * PI / 180.f));

}

void PushBullet::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	TCHAR	szCnt[32] = L"";

	swprintf_s(szCnt, L"P");

	TextOut(hDC, m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY, szCnt, lstrlen(szCnt));
}

void PushBullet::Release()
{
}

void PushBullet::OnColision(CObj* Oppnent)
{
}

void PushBullet::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{
	if ((OBJID::PLAYER == Oppnent->Get_OBJID())&&(!m_bPlayer))
		if (dynamic_cast<CPlayer*>(Oppnent)->Get_Reflect())
		{
			m_vVelocity.x *= -1;
			m_bPlayer = true;
		}

	if (m_bPlayer != Oppnent->Get_IsPlayer())
		m_bDead = true;
}
