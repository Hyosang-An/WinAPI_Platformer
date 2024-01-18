#include "stdafx.h"
#include "CStage2.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "CPushMon.h"
#include "BmpMgr.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
}

void CStage2::Initialize()
{
    CLineMgr::Get_Instance()->Clear_List();
    CLineMgr::Get_Instance()->Initialize(L"../Data/Stage_2.dat");

    CObjMgr::Get_Instance()->Set_Player(200, 400);

    CScrollMgr::Get_Instance()->Set_ScrollX(-CScrollMgr::Get_Instance()->Get_ScrollX());
    CScrollMgr::Get_Instance()->Set_ScrollY(-CScrollMgr::Get_Instance()->Get_ScrollY());

    CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CPushMon>::Create(360, 240, 0));
    CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CPushMon>::Create(930, 320, 0));
    CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CPushMon>::Create(1280, 240, 0));
}

void CStage2::Update()
{
    if (CKeyMgr::Get_Instance()->Key_Down('N'))
        m_sResult = SCENERESULT::RESULT_CLEAR;

    if (0 >= CObjMgr::Get_Instance()->Last_Obj(PLAYER)->Get_Health())
        m_sResult = SCENERESULT::RESULT_FAIL;

    if (0>=CObjMgr::Get_Instance()->Get_Size(MONSTER))
        m_sResult = SCENERESULT::RESULT_CLEAR;

    CObjMgr::Get_Instance()->Update();
}

SCENERESULT CStage2::Late_Update()
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

void CStage2::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
    HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");

    BitBlt(hMemDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

    CLineMgr::Get_Instance()->Render(hMemDC);
    CObjMgr::Get_Instance()->Render(hMemDC);

    TCHAR	szCnt[32] = L"";

    swprintf_s(szCnt, L"STAGE2");

    TextOut(hMemDC, 0, 0, szCnt, lstrlen(szCnt));

    BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CStage2::Release()
{
}
