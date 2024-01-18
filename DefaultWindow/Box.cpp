#include "stdafx.h"
#include "Box.h"
#include "ScrollMgr.h"

CBox::CBox()
{
}


CBox::CBox(LINEPOINT& tLT, LINEPOINT& tRB)
{
	m_tInfo = { (long)tLT.fX, (long)tLT.fY, (long)tRB.fX, (long)tRB.fY };
}

CBox::CBox(RECT box)
{
	m_tInfo = box;
}

CBox::~CBox()
{
}

void CBox::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tInfo.left + iScrollX, m_tInfo.top + iScrollY, m_tInfo.right + iScrollX, m_tInfo.bottom + iScrollY);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}


