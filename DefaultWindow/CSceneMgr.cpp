#include "stdafx.h"
#include "CSceneMgr.h"
#include "CTitle.h"
#include "CTutor.h"
#include "CStage1.h"
#include "CStage2.h"
#include "CStage3.h"
#include "CClear.h"
#include "CFail.h"
#include "CEnding.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_eCurScene(SC_TITLE), m_iStageNo(-1)
{

}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize()
{
	m_vecScene.resize(SC_END);
	m_vecScene[SC_TITLE] = new CTitle;
	m_vecScene[SC_TUTOR] = new CTutor;
	m_vecScene[SC_STAGE1] = new CStage1;
	m_vecScene[SC_STAGE2] = new CStage2;
	m_vecScene[SC_STAGE3] = new CStage3;
	m_vecScene[SC_CLEAR] = new CClear;
	m_vecScene[SC_FAIL] = new CFail;
	m_vecScene[SC_ENDING] = new CEnding;
}

void CSceneMgr::Update()
{
	m_vecScene[m_eCurScene]->Update();
}

void CSceneMgr::Late_Update()
{
	switch (m_vecScene[m_eCurScene]->Late_Update())
	{
	case SCENERESULT::RESULT_TITLE:
		m_iStageNo = -1;
		m_eCurScene = SC_TITLE;
		break;
	case SCENERESULT::RESULT_NEXTSTAGE:
		++m_iStageNo;
		m_eCurScene = SCENEID(SC_TUTOR + SCENEID(m_iStageNo));
		m_vecScene[m_eCurScene]->Initialize();
		break;
	case SCENERESULT::RESULT_CLEAR:
		m_eCurScene = SC_CLEAR;
		break;
	case SCENERESULT::RESULT_FAIL:
		m_eCurScene = SC_FAIL;
		break;
	case SCENERESULT::RESULT_ENDING:
		m_eCurScene = SC_ENDING;
		break;
	default:
		break;
	}
}

void CSceneMgr::Render(HDC hDC)
{
	m_vecScene[m_eCurScene]->Render(hDC);
}

void CSceneMgr::Release()
{
	for (vector<CScene*>::iterator iter = m_vecScene.begin(); iter != m_vecScene.end();)
	{
		if (*iter)
		{
			Safe_Delete(*iter);
			iter = m_vecScene.erase(iter);
		}
		else
			++iter;
	}
}
