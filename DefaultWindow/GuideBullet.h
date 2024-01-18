#pragma once
#include "Obj.h"
class CGuideBullet : public CObj
{
public:
	CGuideBullet();
	CGuideBullet(int Count);
	virtual ~CGuideBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnColision(CObj* Oppnent) override;
	virtual void OnColisionEX(CObj* Oppnent, INVADEDIRC Direc, float invadesize) override;

private: // 연속 추적을 위한 변수 구현 (뮤탈리스크)
	list<CObj*> m_pExceptionlist; // <- 특정 CObj를 추적에서 제외 
	int m_iCount; // <- 남은 추적 횟수 (0이 되면 Dead처리)
};

