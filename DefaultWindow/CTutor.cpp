#include "stdafx.h"
#include "CTutor.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "CGhost.h"
#include "CPushMon.h"
#include "CBoomMon.h"
#include "CPlatform.h"
#include "ScrollMgr.h"
#include "CSpring.h"
#include "BmpMgr.h"

CTutor::CTutor()
{
}

CTutor::~CTutor()
{
}

void CTutor::Initialize()
{
    CLineMgr::Get_Instance()->Clear_List();
    //CLineMgr::Get_Instance()->Initialize(L"../Data/Stage_Tutor.dat");
    CLineMgr::Get_Instance()->Initialize(L"../Data/Stage_Tutor.dat");

    //CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(400, 300, 0));
    CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CGhost>::Create(500, 100, 0));
    CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CPushMon>::Create(1350, 400, 0));
    CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CBoomMon>::Create(1000, 400, 0));
    CObjMgr::Get_Instance()->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(1000, 250, 0));
    CObjMgr::Get_Instance()->Add_Object(PLATFORM, CAbstractFactory<CSpring>::Create(1300, 250, 0));

    CObjMgr::Get_Instance()->Set_Player(200, 400);
    CScrollMgr::Get_Instance()->Set_ScrollX(-CScrollMgr::Get_Instance()->Get_ScrollX());
    CScrollMgr::Get_Instance()->Set_ScrollY(-CScrollMgr::Get_Instance()->Get_ScrollY());

}

void CTutor::Update()
{
    if (CKeyMgr::Get_Instance()->Key_Down('N'))
        m_sResult = SCENERESULT::RESULT_CLEAR;

    if(0 >= CObjMgr::Get_Instance()->Last_Obj(PLAYER)->Get_Health())
        m_sResult = SCENERESULT::RESULT_FAIL;

    CObjMgr::Get_Instance()->Update();
}

SCENERESULT CTutor::Late_Update()
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

void CTutor::Render(HDC hDC)
{
   /* Rectangle(hDC, 0, 0, WINCX, WINCY);

    TCHAR	szCnt[32] = L"";

    swprintf_s(szCnt, L"TUTORIAL");

    TextOut(hDC, 0, 0, szCnt, lstrlen(szCnt));

    CLineMgr::Get_Instance()->Render(hDC);
    CObjMgr::Get_Instance()->Render(hDC);*/


    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
    HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");

    BitBlt(hMemDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

    CLineMgr::Get_Instance()->Render(hMemDC);
    CObjMgr::Get_Instance()->Render(hMemDC);

    TCHAR	szCnt[32] = L"";

    swprintf_s(szCnt, L"TUTORIAL");

    TextOut(hMemDC, 0, 0, szCnt, lstrlen(szCnt));

    BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

}

void CTutor::Release()
{
}
