#pragma once
#include "CScene.h"

class CClear : public CScene
{
public:
	CClear();
	virtual ~CClear();

public:
	virtual void Initialize()		override;
	virtual void	 Update()			override;
	virtual SCENERESULT Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;
};

