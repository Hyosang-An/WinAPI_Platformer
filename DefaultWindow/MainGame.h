#pragma once

#include "Define.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

private:
	HDC			m_DC;

#pragma region ����
	/*CObj*		m_pPlayer;
	list<CObj*>	m_BulletList;*/
#pragma endregion ����	
	DWORD			m_dwTime;
	int				m_iFPS;
	TCHAR			m_szFPS[32];

public:
	static ULONGLONG		prev_update_time_ms;
	static ULONGLONG		delta_time_ms;
};

// ������ ���� : �ڵ��� �������� ������ ���·� ����� �����ϱ� ���ϰ� ���� ������ ����
// https://refactoring.guru/ko/design-patterns

// �߻� ���丮 ���� : ���� ������ �� ������� �ν��Ͻ��� ����� ������ �߻�ȭ��Ų ����, ��ü ���� �� ���ݵǴ� �������� �۾��� �߻�ȭ�Ѵ�.
// �ݺ��� ���� : ���� ǥ�� ����� �������� �ʰ� �������� ���� ����� �����ϴ� ����
// �޵����� ����(������) ���� : ��ȣ �ۿ��ϴ� ��ü���� ���� ������ ���踦 �ΰ� ���� ��� ������ �������� �����Ͽ� �����ϴ� ��ü�� �δ� ����

// �̱��� ���� : �� �ϳ��� �ν��Ͻ�(��ü)�� �����Ͽ� ����ϴ� ����
