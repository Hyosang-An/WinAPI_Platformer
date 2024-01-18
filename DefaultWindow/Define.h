#pragma once

#include "Vector2D.h"

#define WINCX		800
#define WINCY		600

#define PURE		= 0

#define	PI			3.141592f

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		VK_MAX		0xff

#define		GRAVITY_ACC		9.8f	

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

	Vector2D operator+(const Vector2D& other) const
	{
		return Vector2D(fX + other.x, fY + other.y);
	}
}INFO;

enum DIRECTION
{
	DIR_LEFT, 
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	DIR_END
};

enum OBJID
{
	PLAYER,
	MONSTER,
	BULLET,
	MOUSE,
	SHIELD,
	BOX,
	PLATFORM,
	END
};

typedef struct tagLinePoint
{
	float	fX;
	float	fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) { }

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT	tLeft;
	LINEPOINT	tRight;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLeft, LINEPOINT& _tRight)
		: tLeft(_tLeft), tRight(_tRight) {}

}LINE;

struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(m_pString, Pair.first);
	}

private:
	const TCHAR* m_pString;
};


enum StructType
{
	TYPE_LINE,
	TYPE_BOX
};

enum class SCENERESULT
{
	RESULT_NONE,
	RESULT_NEXTSTAGE,
	RESULT_CLEAR,
	RESULT_FAIL,
	RESULT_ENDING,
	RESULT_TITLE,
	END
};

enum class INVADEDIRC
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	END
};

enum class OBJSPECIAL
{
	NORMAL,
	PUSH,
	BOOM,
	GRAVITY,
	SPRING,
	END
};

extern HWND g_hWnd;