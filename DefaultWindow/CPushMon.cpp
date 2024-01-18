#include "stdafx.h"
#include "CPushMon.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "PushBullet.h"

CPushMon::CPushMon()
	:m_fPushPower(100.f)
{
}

CPushMon::~CPushMon()
{
    Release();
}

void CPushMon::Initialize()
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 2.f;
	m_OBJID = MONSTER;
	m_iHealth = 100;
	m_iMaxHealth = 100;
}

int CPushMon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Set_Pos(m_tInfo + m_vVelocity * 0.1f);
	m_vVelocity = m_vVelocity + m_vGravity * 0.1f;

	CObj* Player = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	if (0 == GetTickCount() % 100)
		if (abs(Player->Get_Info().fX - m_tInfo.fX) < 500)
		{
			if (Player->Get_Info().fX > m_tInfo.fX)
			{
				CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<PushBullet>::Create(m_tInfo.fX, m_tInfo.fY, 0));
				CObjMgr::Get_Instance()->Last_Obj(BULLET)->Set_IsPlayer(false);
			}
			else
			{
				CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<PushBullet>::Create(m_tInfo.fX, m_tInfo.fY, 180));
				CObjMgr::Get_Instance()->Last_Obj(BULLET)->Set_IsPlayer(false);
			}
		}
	return OBJ_NOEVENT;
}

void CPushMon::Late_Update()
{
	CLineMgr::Get_Instance()->Collision_Line(this);
	CLineMgr::Get_Instance()->Collision_Box(this);

	__super::Update_Rect();
	if (0 >= m_iHealth)
		m_bDead = true;
}

void CPushMon::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		m_tRect.right + iScrollX,
		m_tRect.bottom + iScrollY);

	TCHAR	szCnt[32] = L"";

	swprintf_s(szCnt, L"P");

	TextOut(hDC, m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY - 20, szCnt, lstrlen(szCnt));

	ShowHpBar(hDC, false, iScrollX, iScrollY);
}

void CPushMon::Release()
{
	if (0 >= m_iHealth)
		m_bDead = true;
}

void CPushMon::OnColision(CObj* Oppnent)
{
}

void CPushMon::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{
	if ((OBJID::BULLET == Oppnent->Get_OBJID()) && (Oppnent->Get_IsPlayer()))
		m_iHealth -= 10;
}
