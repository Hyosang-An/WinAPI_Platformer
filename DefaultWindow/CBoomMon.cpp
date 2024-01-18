#include "stdafx.h"
#include "CBoomMon.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "PushBullet.h"

CBoomMon::CBoomMon() :
	m_bTrace(false)
{
}

CBoomMon::~CBoomMon()
{
}

void CBoomMon::Initialize()
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 10.f;
	m_OBJID = MONSTER;
	m_iHealth = 100;
	m_iMaxHealth = 100;
	m_iAttack = 50;

	m_vecSpecial[int(OBJSPECIAL::BOOM)] = true;
}

int CBoomMon::Update()
{
	if ((true == m_bTrace) && (0 == GetTickCount() % 10))
		--m_iHealth;

	if (0 >= m_iHealth)
		m_bDead = true;

	if (m_bDead)
		return OBJ_DEAD;

	Set_Pos(m_tInfo + m_vVelocity * 0.1f);
	m_vVelocity = m_vVelocity + m_vGravity * 0.1f;

	return OBJ_NOEVENT;
}

void CBoomMon::Late_Update()
{
	CLineMgr::Get_Instance()->Collision_Line(this);
	CLineMgr::Get_Instance()->Collision_Box(this);

	CObj* Player = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	if (abs(Player->Get_Info().fX - m_tInfo.fX) < 500)
	{
		m_bTrace = true;

		if (Player->Get_Info().fX < m_tInfo.fX)
			m_vVelocity.x = -1 * m_fSpeed;
		else
			m_vVelocity.x = 1 * m_fSpeed;

		if (Player->Get_Info().fY < m_tInfo.fY)
		{
			if (CLineMgr::Get_Instance()->Collision_Line(this) || CLineMgr::Get_Instance()->Collision_Box(this))
				m_vVelocity.y = -120.f;
		}
	}
	else
	{
		m_bTrace = false;
		m_vVelocity.x = 0;
	}

	__super::Update_Rect();
}

void CBoomMon::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		m_tRect.right + iScrollX,
		m_tRect.bottom + iScrollY);

	TCHAR	szCnt[32] = L"";

	swprintf_s(szCnt, L"B");

	TextOut(hDC, m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY - 20, szCnt, lstrlen(szCnt));

	ShowHpBar(hDC, false, iScrollX, iScrollY);
}

void CBoomMon::Release()
{
}

void CBoomMon::OnColision(CObj* Oppnent)
{
}

void CBoomMon::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{
	if (OBJID::PLAYER == Oppnent->Get_OBJID())
		m_bDead = true;
}
