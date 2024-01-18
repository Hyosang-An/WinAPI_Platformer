#pragma once

#include "Line.h"
#include "Box.h"
#include "Player.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(wchar_t* Data);
	void		Render(HDC hDC);
	void		Release();
	
public:
	bool		Collision_Line(CObj* pObj);
	bool		Collision_Box(CObj* pPlayer);
	bool		CheckBoxCollision(CObj* pPlayer, CBox* box, float* pX, float* pY);

	void		Load_Data(wchar_t* Data);
	void		Clear_List();

	list<CBox*>			Get_BoxLIst() { return m_BoxList; }

public:
	static CLineMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

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
	static CLineMgr*		m_pInstance;

	list<CLine*>			m_LineList;
	list<CBox*>				m_BoxList;

};


