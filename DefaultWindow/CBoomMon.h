#pragma once
#include "Obj.h"

class CBoomMon : public CObj
{
public:
	CBoomMon();
	virtual ~CBoomMon();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnColision(CObj* Oppnent) override;
	virtual void OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize) override;

private:
	bool m_bTrace;
};

