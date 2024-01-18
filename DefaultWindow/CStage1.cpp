#include "stdafx.h"
#include "CStage1.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "CGhost.h"
#include "CPushMon.h"
#include "CBoomMon.h"
#include "CPlatform.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
}

void CStage1::Initialize()
{
	CLineMgr::Get_Instance()->Clear_List();
	CLineMgr::Get_Instance()->Initialize(L"../Data/Stage_1.dat");
	CObjMgr::Get_Instance()->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(200, 100, 0));
	CObjMgr::Get_Instance()->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(450, 100, 0));
	CObjMgr::Get_Instance()->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(350, 200, 0));
	CObjMgr::Get_Instance()->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(200, 350, 0));
	CObjMgr::Get_Instance()->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(450, 350, 0));

	CObjMgr::Get_Instance()->Set_Player(200, 400);

	CScrollMgr::Get_Instance()->Set_ScrollX(-CScrollMgr::Get_Instance()->Get_ScrollX());
	CScrollMgr::Get_Instance()->Set_ScrollY(-CScrollMgr::Get_Instance()->Get_ScrollY());
	m_iCount = 200;
}

void CStage1::Update()
{
	if (0 == GetTickCount() % 70)
		CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CBoomMon>::Create(650, 200, 0));

	if (CKeyMgr::Get_Instance()->Key_Down('N'))
		m_sResult = SCENERESULT::RESULT_CLEAR;

	if (0 == GetTickCount() % 10)
		--m_iCount;

	if (0 == m_iCount)
		m_sResult = SCENERESULT::RESULT_CLEAR;

	if (0 >= CObjMgr::Get_Instance()->Last_Obj(PLAYER)->Get_Health())
		m_sResult = SCENERESULT::RESULT_FAIL;

	CObjMgr::Get_Instance()->Update();
}

SCENERESULT CStage1::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	SCENERESULT Result = m_sResult;

	if ((SCENERESULT::RESULT_CLEAR == Result) || (SCENERESULT::RESULT_FAIL == Result))
	{
		CObjMgr::Get_Instance()->Delete_Stage_Obj();
		CLineMgr::Get_Instance()->Release();
	}

	m_sResult = SCENERESULT::RESULT_NONE;
	return Result;
}

void CStage1::Render(HDC hDC)
{
	/*Rectangle(hDC, 0, 0, WINCX, WINCY);

	TCHAR	szCnt[32] = L"";

	swprintf_s(szCnt, L"STAGE1");

	TextOut(hDC, 0, 0, szCnt, lstrlen(szCnt));

	TCHAR	szCount[32] = L"";

	swprintf_s(szCount, L"%d", m_iCount);

	TextOut(hDC, 0, 50, szCount, lstrlen(szCount));

	CLineMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);*/

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");

	BitBlt(hMemDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

	CLineMgr::Get_Instance()->Render(hMemDC);
	CObjMgr::Get_Instance()->Render(hMemDC);

	TCHAR	szCnt[32] = L"";

	swprintf_s(szCnt, L"STAGE1");

	TextOut(hMemDC, 0, 0, szCnt, lstrlen(szCnt));

	TCHAR	szCount[32] = L"";

	swprintf_s(szCount, L"%d", m_iCount);

	TextOut(hMemDC, 0, 50, szCount, lstrlen(szCount));

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	
}

void CStage1::Release()
{
}
