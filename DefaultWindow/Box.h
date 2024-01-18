#pragma once

#include "Define.h"

class CBox
{
public:
	CBox();
	CBox(LINEPOINT& tLT, LINEPOINT& tRB);
	CBox(RECT box);
	~CBox();

public:
	void	Render(HDC hDC);
	RECT	Get_Info() { return m_tInfo; }

private:
	RECT	m_tInfo;
};

