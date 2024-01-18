#include "stdafx.h"
#include "Monster.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 2.f;
	m_iHealth = 100.0f;
	m_iMaxHealth = 100.0f;
	m_OBJID = MONSTER;
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Set_Pos(m_tInfo + m_vVelocity * 0.1f);
	m_vVelocity = m_vVelocity + m_vGravity * 0.1f;

	

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	if (0 >= m_iHealth)
		m_bDead = true;

	CLineMgr::Get_Instance()->Collision_Line(this);
	CLineMgr::Get_Instance()->Collision_Box(this);

	__super::Update_Rect();
}

void CMonster::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		m_tRect.right + iScrollX,
		m_tRect.bottom + iScrollY);

	
}

void CMonster::Release()
{
}

void CMonster::OnColision(CObj* Oppnent)
{
	
}

void CMonster::OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize)
{
	if (OBJID::BULLET == Oppnent->Get_OBJID())
	{
		m_iHealth -= Oppnent->Get_Attack();
	}
}
