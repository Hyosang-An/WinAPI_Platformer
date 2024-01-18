#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fAngle(0.f), m_fDistance(0.f), m_pTarget(nullptr),
m_iHealth(100), m_iMaxHealth(100), m_iAttack(10), m_iMaxAttack(10), m_bPlayer(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	m_vecSpecial.resize(int(OBJSPECIAL::END));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::ShowHpBar(HDC hDC, bool IsPlayer, float ScrollX, float ScrollY)
{
	Rectangle(hDC, m_tRect.left + ScrollX, m_tRect.top + (m_tInfo.fCY * 0.6f) + ScrollY, m_tRect.right + ScrollX, m_tRect.bottom - (m_tInfo.fCY * 0.2f) + ScrollY);

	HBRUSH myBrush = nullptr;

	if(m_bPlayer)
		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	else 
		myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
		
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRect.left + ScrollX,
		m_tRect.top + (m_tInfo.fCY * 0.6f) + ScrollY,
		m_tRect.left + (m_tInfo.fCX * float(float(m_iHealth) / float(m_iMaxHealth))) + ScrollX,
		m_tRect.bottom - (m_tInfo.fCY * 0.2f) + ScrollY);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}
