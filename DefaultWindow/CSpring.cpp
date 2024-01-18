#include "stdafx.h"
#include "CSpring.h"
#include "CPlatform.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

CSpring::CSpring()
{
}

CSpring::~CSpring()
{
}

void CSpring::Initialize()
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 2.f;
	m_iHealth = 100.0f;
	m_iMaxHealth = 100.0f;
	m_OBJID = PLATFORM;
	m_vecSpecial[int(OBJSPECIAL::SPRING)] = true;
}

int CSpring::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
}

void CSpring::Late_Update()
{
}

void CSpring::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		m_tRect.right + iScrollX,
		m_tRect.bottom + iScrollY);

	TCHAR	szCnt[32] = L"";

	swprintf_s(szCnt, L"Spring");

	TextOut(hDC, m_tRect.left + iScrollX + 10, m_tRect.top + iScrollY + 10, szCnt, lstrlen(szCnt));

	__super::Update_Rect();
}

void CSpring::Release()
{
}

void CSpring::OnColision(CObj* Oppnent)
{
}

void CSpring::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{

}
