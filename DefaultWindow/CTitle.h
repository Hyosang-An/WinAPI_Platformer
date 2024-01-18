#pragma once
#include "CScene.h"

class CTitle : public CScene
{
public:
	CTitle();
	virtual ~CTitle();

public:
	virtual void Initialize()		override;
	virtual void	 Update()			override;
	virtual SCENERESULT Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;
};

