#include "stdafx.h"
#include "CClear.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"

CClear::CClear()
{
}

CClear::~CClear()
{
}

void CClear::Initialize()
{
}

void CClear::Update()
{
    if (CKeyMgr::Get_Instance()->Key_Down('N'))
        m_sResult = SCENERESULT::RESULT_NEXTSTAGE;
}

SCENERESULT CClear::Late_Update()
{
    SCENERESULT Result = m_sResult;
    m_sResult = SCENERESULT::RESULT_NONE;
    return Result;
}

void CClear::Render(HDC hDC)
{
    Rectangle(hDC, 0, 0, WINCX, WINCY);
    Rectangle(hDC, 50, 50, WINCX - 50, WINCY - 50);

    TCHAR	szCnt[32] = L"";

    swprintf_s(szCnt, L"CLEAR");

    TextOut(hDC, WINCX / 2, WINCY / 2, szCnt, lstrlen(szCnt));
}

void CClear::Release()
{
}
