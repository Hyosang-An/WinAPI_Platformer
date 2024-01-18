#include "stdafx.h"
#include "MainGame.h"
#include "CSceneMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

ULONGLONG		CMainGame::prev_update_time_ms = GetTickCount64();
ULONGLONG		CMainGame::delta_time_ms = GetTickCount64();

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);
	
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create());

	/*for (int i = 0; i < 5; ++i)
	{
		CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(float(rand() % WINCX), float(rand() % WINCY), 0.f));
	}*/

	CSceneMgr::Get_Instance()->Initialize();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
}

void CMainGame::Update()
{
	delta_time_ms = GetTickCount64() - prev_update_time_ms;
	prev_update_time_ms = GetTickCount64();

	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	CSceneMgr::Get_Instance()->Render(m_DC);
}

void CMainGame::Release()
{
	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	
	ReleaseDC(g_hWnd, m_DC);
}
