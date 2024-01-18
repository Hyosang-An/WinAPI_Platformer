#include "stdafx.h"
#include "ObjMgr.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if ((END <= eID) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update()
{
	for (size_t i = 0; i < END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}

	CCollisionMgr::Collision_RectEx(m_ObjList[PLAYER], m_ObjList[BULLET]);
	CCollisionMgr::Collision_RectEx(m_ObjList[PLAYER], m_ObjList[PLATFORM]);
	CCollisionMgr::Collision_RectEx(m_ObjList[MONSTER], m_ObjList[BULLET]);
	//CCollisionMgr::Collision_Rect(m_ObjList[MONSTER], m_ObjList[MOUSE]);
	CCollisionMgr::Collision_RectEx(m_ObjList[PLAYER], m_ObjList[BOX]);
	CCollisionMgr::Collision_RectEx(m_ObjList[PLAYER], m_ObjList[MONSTER]);
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CObjMgr::Set_Player(float fX, float fY)
{
	(*m_ObjList[PLAYER].begin())->Initialize();
	(*m_ObjList[PLAYER].begin())->Set_Pos(fX, fY);
}

void CObjMgr::Delete_Stage_Obj()
{
	for (size_t i = PLAYER+1; i < END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

CObj * CObjMgr::Get_Target(OBJID eID, CObj * pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;

	float	fDistance(0.f);

	for (auto& iter : m_ObjList[eID])
	{
		if(iter->Get_Dead())
			continue;

		float	fWidth = abs(iter->Get_Info().fX - pObj->Get_Info().fX);
		float	fHeight = abs(iter->Get_Info().fY - pObj->Get_Info().fY);

		float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || fDistance > fDiagonal)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}

	}
	
	return pTarget;
}
