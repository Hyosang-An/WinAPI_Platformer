#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
}

int CMouse::Update()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);

	// 전체 스크린 영역에서 클라이언트 좌표로 변환
	ScreenToClient(g_hWnd, &ptMouse);
	
	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	__super::Update_Rect();

	ShowCursor(false);	// 마우스 커서의 출력 유무를 결정

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
}

void CMouse::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release()
{
}

void CMouse::OnColision(CObj* Oppnent)
{
}

void CMouse::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{
}
