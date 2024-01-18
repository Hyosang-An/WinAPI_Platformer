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

#pragma region 복습
	/*CObj*		m_pPlayer;
	list<CObj*>	m_BulletList;*/
#pragma endregion 복습	
	DWORD			m_dwTime;
	int				m_iFPS;
	TCHAR			m_szFPS[32];

public:
	static ULONGLONG		prev_update_time_ms;
	static ULONGLONG		delta_time_ms;
};

// 디자인 패턴 : 코드의 구조들을 일정한 형태로 만들어 재사용하기 편리하게 만든 일정한 패턴
// https://refactoring.guru/ko/design-patterns

// 추상 팩토리 패턴 : 생성 패턴의 한 방법으로 인스턴스를 만드는 절차를 추상화시킨 패턴, 객체 생성 시 동반되는 공통적인 작업을 추상화한다.
// 반복자 패턴 : 내부 표현 방식은 공개하지 않고 순차적인 접근 방법을 제공하는 패턴
// 메디에이터 패턴(중재자) 패턴 : 상호 작용하는 객체들이 서로 복잡한 관계를 맺고 있을 경우 별도의 형식으로 정의하여 중재하는 객체를 두는 패턴

// 싱글톤 패턴 : 단 하나의 인스턴스(객체)를 생성하여 사용하는 패턴
