#pragma once
#include "define.h"
#include "CScene.h"

class CSceneMgr
{
public:
	enum SCENEID 
	{ 
		SC_TITLE, 
		SC_TUTOR, 
		SC_STAGE1, 
		SC_STAGE2,
		SC_STAGE3,
		SC_CLEAR, 
		SC_FAIL, 
		SC_ENDING, 
		SC_END 
	};

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr* m_pInstance;
	vector<CScene*> m_vecScene;

	SCENEID				m_eCurScene;
	int					m_iStageNo;
};

