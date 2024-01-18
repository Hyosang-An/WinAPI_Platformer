#pragma once

#include "Player.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Mouse.h"
#include "Box.h"
#include "CollisionMgr.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();
	void		Set_Player(float fX, float fY); // <- �������� ���� ���� ���� ��ġ ������ ���� ���
	void		Delete_Stage_Obj(); // <- �������� �Ϸ� �� �÷��̾� ������ ������Ʈ ����
	int			Get_Size(OBJID eID) { return m_ObjList[int(eID)].size(); }

public:
	CObj*		Get_Target(OBJID eID, CObj* pObj);
	CObj*		Last_Obj(OBJID eID) { return m_ObjList[int(eID)].back(); }

public:
	static CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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
	list<CObj*>		m_ObjList[END];
	static CObjMgr*	m_pInstance;

};

