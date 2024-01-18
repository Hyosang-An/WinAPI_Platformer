#pragma once
#include "CScene.h"

class CFail : public CScene
{
public:
	CFail();
	virtual ~CFail();

public:
	virtual void Initialize()		override;
	virtual void	 Update()			override;
	virtual SCENERESULT Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;
};

