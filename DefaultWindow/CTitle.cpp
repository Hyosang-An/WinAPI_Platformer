#include "stdafx.h"
#include "CTitle.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"

CTitle::CTitle()
{

}

CTitle::~CTitle()
{

}

void CTitle::Initialize()
{

}

void CTitle::Update()
{
    if (CKeyMgr::Get_Instance()->Key_Down('N'))
        m_sResult = SCENERESULT::RESULT_NEXTSTAGE;

    if (0 >= CObjMgr::Get_Instance()->Last_Obj(PLAYER)->Get_Health())
        CObjMgr::Get_Instance()->Last_Obj(PLAYER)->Initialize();
}

SCENERESULT CTitle::Late_Update()
{
    SCENERESULT Result = m_sResult;
    m_sResult = SCENERESULT::RESULT_NONE;
    return Result;
}

void CTitle::Render(HDC hDC)
{
    Rectangle(hDC, 0, 0, WINCX, WINCY);
    Rectangle(hDC, 50, 50, WINCX - 50, WINCY - 50);

    TCHAR	szCnt[32] = L"";

    swprintf_s(szCnt, L"TITLE");

    TextOut(hDC, WINCX / 2, WINCY / 2, szCnt, lstrlen(szCnt));
}

void CTitle::Release()
{

}
