#pragma once
#include "CScene.h"

class CStage1 : public CScene
{
public:
	CStage1();
	virtual ~CStage1();

public:
	virtual void Initialize()		override;
	virtual void	 Update()			override;
	virtual SCENERESULT Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;
};

