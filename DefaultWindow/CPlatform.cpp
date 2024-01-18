#include "stdafx.h"
#include "CPlatform.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

CPlatform::CPlatform()
{
}

CPlatform::~CPlatform()
{
}

void CPlatform::Initialize()
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 2.f;
	m_iHealth = 100.0f;
	m_iMaxHealth = 100.0f;
	m_OBJID = PLATFORM;
}

int CPlatform::Update()
{
	if ((0 == GetTickCount() % 20) && (m_iMaxHealth > m_iHealth))
		++m_iHealth;

	if (0 >= m_iHealth)
		m_bDead = true;

	if (m_bDead)
		return OBJ_DEAD;
}

void CPlatform::Late_Update()
{
}

void CPlatform::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		m_tRect.right + iScrollX,
		m_tRect.bottom + iScrollY);

	TCHAR	szCnt[32] = L"";

	swprintf_s(szCnt, L"Platform");

	TextOut(hDC, m_tRect.left + iScrollX + 10, m_tRect.top + iScrollY + 10, szCnt, lstrlen(szCnt));

	ShowHpBar(hDC, false, iScrollX, iScrollY);

	__super::Update_Rect();
}

void CPlatform::Release()
{
}

void CPlatform::OnColision(CObj* Oppnent)
{
}

void CPlatform::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{
	if ((OBJID::PLAYER == Oppnent->Get_OBJID()) && (INVADEDIRC::TOP == Direc))
	{
		if (0 == GetTickCount() % 10)
			m_iHealth-=5;
	}
}
