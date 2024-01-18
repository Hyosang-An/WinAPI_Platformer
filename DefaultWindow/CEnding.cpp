#include "stdafx.h"
#include "CEnding.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"

CEnding::CEnding()
{
}

CEnding::~CEnding()
{
}

void CEnding::Initialize()
{
}

void CEnding::Update()
{
    if (CKeyMgr::Get_Instance()->Key_Down('N'))
        m_sResult = SCENERESULT::RESULT_TITLE;
}

SCENERESULT CEnding::Late_Update()
{
    SCENERESULT Result = m_sResult;
    m_sResult = SCENERESULT::RESULT_NONE;
    return Result;
}

void CEnding::Render(HDC hDC)
{
    Rectangle(hDC, 0, 0, WINCX, WINCY);
    Rectangle(hDC, 50, 50, WINCX - 50, WINCY - 50);

    TCHAR	szCnt[32] = L"";

    swprintf_s(szCnt, L"ENDING");

    TextOut(hDC, WINCX / 2, WINCY / 2, szCnt, lstrlen(szCnt));
}

void CEnding::Release()
{
}
