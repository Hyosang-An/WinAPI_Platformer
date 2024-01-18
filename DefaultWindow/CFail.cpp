#include "stdafx.h"
#include "CFail.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"

CFail::CFail()
{
}

CFail::~CFail()
{
}

void CFail::Initialize()
{
}

void CFail::Update()
{
    if (CKeyMgr::Get_Instance()->Key_Down('N'))
        m_sResult = SCENERESULT::RESULT_TITLE;
}

SCENERESULT CFail::Late_Update()
{
    SCENERESULT Result = m_sResult;
    m_sResult = SCENERESULT::RESULT_NONE;
    return Result;
}

void CFail::Render(HDC hDC)
{
    Rectangle(hDC, 0, 0, WINCX, WINCY);
    Rectangle(hDC, 50, 50, WINCX - 50, WINCY - 50);

    TCHAR	szCnt[32] = L"";

    swprintf_s(szCnt, L"FAIL");

    TextOut(hDC, WINCX / 2, WINCY / 2, szCnt, lstrlen(szCnt));
}

void CFail::Release()
{
}
