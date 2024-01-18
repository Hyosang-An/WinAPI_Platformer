#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "MainGame.h"
#include "ScrollMgr.h"
#include "PushBullet.h"
#include "BmpMgr.h"

CPlayer::CPlayer() : m_bJump(false), m_fJumpPower(0.f), m_fTime(0.f), m_bReflect(false), m_iGravityGun(0)
{
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 80.f, 80.f };
	prev_Pos = Get_Pos();
	m_fSpeed = 100.f;
	m_fAngle = 0.f;
	m_fDistance = 100.f;
	m_fJumpPower = 30.f;
	m_OBJID = PLAYER; // <- OBJ 타입 설정
	m_vecSpecial[int(OBJSPECIAL::NORMAL)] = true; // <- normal 특성으로 설정

	m_iHealth = 500; // <- 체력 구현
	m_iMaxHealth = 500; // <- 최대 체력 구현
	m_iAttack = 10; // <- 공격 구현 
	m_iMaxAttack = 100; // <- 최대 공격력
	m_bPlayer = true;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mario2.bmp", L"Player");

}

int CPlayer::Update()
{

	Key_Input();

	Set_Pos(m_tInfo + m_vVelocity * 0.1f);
	m_vVelocity = m_vVelocity + m_vGravity * 0.1f;

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	CLineMgr::Get_Instance()->Collision_Line(this);
	CLineMgr::Get_Instance()->Collision_Box(this);

	Offset(); // 스크롤 오프셋

	prev_Pos = Get_Pos();
	__super::Update_Rect();
}

void CPlayer::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Player");

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		0,
		0,
		60,
		60,
		RGB(255, 255, 255));

	//BitBlt(hDC,					// 복사 받을 최종적으로 그림을 그릴 dc
	//m_tRect.left + iScrollX, // 복사 받을 위치의 left, top 좌표
	//m_tRect.top + iScrollY,
	//(int)m_tInfo.fCX,	// 복사 받을 그림의 가로, 세로 길이
	//(int)m_tInfo.fCY,
	//hMemDC,	// 비트맵 이미지를 갖고 있는 dc
	//0,		// 출력할 비트맵 이미지의 시작 좌표
	//0, 
	//SRCCOPY);	// 출력 효과 설정

	if (m_bReflect == true)
	{
		TCHAR	szCnt[32] = L"";
		swprintf_s(szCnt, L"Reflect");
		TextOut(hDC, m_tInfo.fX + iScrollX - 10, m_tInfo.fY + iScrollY - 20, szCnt, lstrlen(szCnt));
	}

	if (m_iGravityGun > 0)
	{
		TCHAR	szCnt[32] = L"";
		swprintf_s(szCnt, L"Gravity %d", m_iGravityGun);
		TextOut(hDC, m_tInfo.fX + iScrollX - 10, m_tInfo.fY + iScrollY - 10, szCnt, lstrlen(szCnt));
	}

	ShowHpBar(hDC, true, iScrollX, iScrollY);
}

void CPlayer::Release()
{
	CScrollMgr::Get_Instance()->Destroy_Instance();
}

void CPlayer::OnColision(CObj* Oppnent)
{
}

void CPlayer::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{
	if ((true == Oppnent->Get_Special(OBJSPECIAL::PUSH))&&(!m_bReflect))
	{
		float fPush = dynamic_cast<PushBullet*>(Oppnent)->Get_PushPower();

		if (INVADEDIRC::BOTTOM == Direc)
			m_tInfo.fY -= fPush;
		else if (INVADEDIRC::TOP == Direc)
			m_tInfo.fY += fPush;
		else if (INVADEDIRC::RIGHT == Direc)
			m_tInfo.fX -= fPush;
		else if (INVADEDIRC::LEFT == Direc)
			m_tInfo.fX += fPush;
			
		m_iHealth -= Oppnent->Get_Attack();
	}

	if (true == Oppnent->Get_Special(OBJSPECIAL::BOOM))
	{
		m_iHealth -= Oppnent->Get_Attack();
	}

	if ((OBJID::PLATFORM == Oppnent->Get_OBJID())&&(false == Oppnent->Get_Special(OBJSPECIAL::SPRING)))
	{
		if (INVADEDIRC::BOTTOM == Direc)
		{
			m_tInfo.fY = m_tInfo.fY - invadesize;
			m_vVelocity.y -= invadesize;

			if (GetAsyncKeyState(VK_SPACE))
				m_vVelocity.y = -100;
		}
		else if (INVADEDIRC::TOP == Direc)
			m_tInfo.fY += invadesize;
		else if (INVADEDIRC::RIGHT == Direc)
			m_tInfo.fX -= invadesize;
		else if (INVADEDIRC::LEFT == Direc)
			m_tInfo.fX += invadesize;
	}
	else if ((OBJID::PLATFORM == Oppnent->Get_OBJID()) && (true == Oppnent->Get_Special(OBJSPECIAL::SPRING)))
	{
		/*m_tInfo.fY = m_tInfo.fY - invadesize;
		m_vVelocity.y -= invadesize;*/
		Set_YVelocity(-120);
	}

	if ((OBJID::BULLET == Oppnent->Get_OBJID()) && (!Oppnent->Get_IsPlayer()))
		m_iHealth -= Oppnent->Get_Attack();

	if ((true == Oppnent->Get_Special(OBJSPECIAL::PUSH)) && (m_bReflect))
		m_iHealth += Oppnent->Get_Attack();
}

void CPlayer::Key_Input()
{
	float	fY(0.f);

	if ((GetAsyncKeyState(VK_LEFT))&&(!m_bReflect))
	{
		m_vVelocity.x = -m_fSpeed;
	}
		
	if ((GetAsyncKeyState(VK_RIGHT)) && (!m_bReflect))
	{
		m_vVelocity.x = m_fSpeed;
	}

	if (!GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT)) // 왼쪽, 오른쪽 키 둘다 안누름
	{
		m_vVelocity.x = 0;
	}

	if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_LEFT)) // 왼쪽, 오른쪽 키 둘다 누름
	{
		m_vVelocity.x = 0;
	}

	if ((GetAsyncKeyState('R')) &&(0 == GetTickCount()%10))
	{
		if (m_bReflect)
			m_bReflect = false;
		else
			m_bReflect = true;
	}

	if ((GetAsyncKeyState(VK_SPACE)) && (!m_bReflect))
	{
		if (CLineMgr::Get_Instance()->Collision_Line(this) || CLineMgr::Get_Instance()->Collision_Box(this))
			m_vVelocity.y = -100;
	}	

	if (GetAsyncKeyState('Z'))
	{
		auto NowTickCount = GetTickCount();
		if (1.f / 1 < (NowTickCount - m_lBeforeTickCnt) / 1000.f)
		{
			m_lBeforeTickCnt = NowTickCount;
			CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>().Create(m_tInfo.fX, m_tInfo.fY, 90));
			CObjMgr::Get_Instance()->Last_Obj(BULLET)->Set_Special_True(OBJSPECIAL::GRAVITY);
			CObjMgr::Get_Instance()->Last_Obj(BULLET)->Set_IsPlayer(true);
		}
	}
}

void CPlayer::Offset()
{
	/*int	iOffsetX = WINCX >> 1;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (iOffsetX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffsetX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);*/


	int	iOffsetminX = 100;
	int	iOffsetmaxX = 700;
	int iOffsetminY = 100;
	int iOffsetmaxY = 300;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
   
	if (iOffsetminX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-(Get_Pos() - prev_Pos).x);

	if (iOffsetmaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-(Get_Pos() - prev_Pos).x);

	if (iOffsetminY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-(Get_Pos() - prev_Pos).y);

	if (iOffsetmaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-(Get_Pos() - prev_Pos).y);
}



