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

private: // ���� ������ ���� ���� ���� (��Ż����ũ)
	list<CObj*> m_pExceptionlist; // <- Ư�� CObj�� �������� ���� 
	int m_iCount; // <- ���� ���� Ƚ�� (0�� �Ǹ� Deadó��)
};

