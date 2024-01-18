#pragma once

#include "Define.h"

class CScene
{
public:
	CScene() : m_sResult(SCENERESULT::RESULT_NONE) {}
	virtual ~CScene() {};

public:
	virtual void Initialize()		PURE;
	virtual void	 Update()			PURE;
	virtual SCENERESULT Late_Update()		PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release()			PURE;

protected:
	SCENERESULT		m_sResult;
	int				m_iCount;
};

