#pragma once
#include "Obj.h"

class PushBullet : public CObj
{
public:
	PushBullet();
	virtual ~PushBullet();

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;
	virtual void OnColision(CObj* Oppnent) override;
	virtual void OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize) override;
	float	Get_PushPower() { return m_fPushPower; }

private:
	float	m_fPushPower;
	int		m_iTime;
};

