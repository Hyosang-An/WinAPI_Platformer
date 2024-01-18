#pragma once
#include "CScene.h"

class CEnding : public CScene
{
public:
	CEnding();
	virtual ~CEnding();

public:
	virtual void Initialize()		override;
	virtual void	 Update()			override;
	virtual SCENERESULT Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;
};

