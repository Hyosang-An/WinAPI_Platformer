#include "stdafx.h"
#include "LineMgr.h"
#include "CollisionMgr.h"
CLineMgr*	CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(wchar_t* Data)
{
	Load_Data(Data);
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);

	for (auto& box : m_BoxList)
		box->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
	for_each(m_BoxList.begin(), m_BoxList.end(), Safe_Delete<CBox*>);
	m_BoxList.clear();
}

bool CLineMgr::Collision_Line(CObj* _obj)
{
	float _pY(0);
	float _fX = _obj->Get_Pos().x;
	float _fY = _obj->Get_Pos().y + _obj->Get_Info().fCY * 0.5;

	if (m_LineList.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLeft.fX &&
			_fX < iter->Get_Info().tRight.fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;


	float x1 = pTarget->Get_Info().tLeft.fX;
	float y1 = pTarget->Get_Info().tLeft.fY;
	float x2 = pTarget->Get_Info().tRight.fX;
	float y2 = pTarget->Get_Info().tRight.fY;

	_pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	if (_fY >= _pY)
	{
		_obj->Set_Pos(Vector2D(_fX, _pY - _obj->Get_Info().fCY * 0.5f));
		_obj->Set_YVelocity(0);
		return true;
	}
	else
		return false;
}

bool CLineMgr::Collision_Box(CObj* pPlayer)
{
	float	fX(0.f), fY(0.f);

	const auto& r = pPlayer->Get_Rect().right;
	const auto& l = pPlayer->Get_Rect().left;
	const auto& t = pPlayer->Get_Rect().top;
	const auto& b = pPlayer->Get_Rect().bottom;

	for (auto& box : m_BoxList)
	{
		//auto box_rc = box->Get_Info();
		//// 좌 충돌
		//if (r >= box_rc.left && l <= box_rc.left && box_rc.bottom >= t && b >= box_rc.top)
		//{
		//	pPlayer->Move_PosX(-r + box_rc.left);
		//	return true;
		//}
		//// 우 충돌
		//else if (l <= box_rc.right && r >= box_rc.right && box_rc.bottom >= t && b >= box_rc.top)
		//{
		//	pPlayer->Move_PosX(box_rc.right - l);
		//	return true;
		//}
		//// 상 충돌
		//else if (box_rc.top >= t && b >= box_rc.top && r >= box_rc.left && l <= box_rc.right)
		//{
		//	pPlayer->Move_PosY(box_rc.top - b);
		//	return true;
		//}
		//// 하 충돌
		//else if (box_rc.bottom >= t && b >= box_rc.bottom && r >= box_rc.left && l <= box_rc.right)
		//{
		//	pPlayer->Move_PosY(box_rc.bottom - t);
		//	return true;
		//}

		//else
		//	return false;

		auto box_cx = (box->Get_Info().left + box->Get_Info().right) / 2;
		auto box_cy = (box->Get_Info().top + box->Get_Info().bottom) / 2;
		/*auto box_w = (box->Get_Info().right - box->Get_Info().left);
		auto box_h = (box->Get_Info().bottom - box->Get_Info().top);*/

		if (CheckBoxCollision(pPlayer, box, &fX, &fY))
		{
			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌 일때만 박스 위에 서있게. 그리고 그 때만 true 반환
				if (pPlayer->Get_Info().fY < box_cy)
				{
					if (pPlayer->Get_Velocity().y >= 0)
					{
						pPlayer->Move_PosY(-fY + 2);
						pPlayer->Set_YVelocity(0);
						return true;
					}
					
				}

				// 하 충돌
				else
				{
					pPlayer->Move_PosY(fY);
					pPlayer->Set_YVelocity(1);
				}
			}

			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (pPlayer->Get_Info().fX < box_cx)
				{
					pPlayer->Move_PosX(-fX);
				}

				// 우 충돌
				else
				{
					pPlayer->Move_PosX(fX);
				}
			}
		}

	}

	return false;
}

bool CLineMgr::CheckBoxCollision(CObj* pPlayer, CBox* box, float* pX, float* pY)
{
	auto box_cx = (box->Get_Info().left + box->Get_Info().right) / 2;
	auto box_cy = (box->Get_Info().top + box->Get_Info().bottom) / 2;
	auto box_w = (box->Get_Info().right - box->Get_Info().left);
	auto box_h = (box->Get_Info().bottom - box->Get_Info().top);

	float	fWidth = abs(pPlayer->Get_Info().fX - box_cx);
	float	fHeight = abs(pPlayer->Get_Info().fY - box_cy);

	float fRadiusX = (pPlayer->Get_Info().fCX + box_w) * 0.5f;
	float fRadiusY = (pPlayer->Get_Info().fCY + box_h) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		// px, py는 무조건 0이상 값
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}




void CLineMgr::Load_Data(wchar_t* Data)
{
	HANDLE		hFile = CreateFile(Data, // 파일 경로와 이름을 명시
		GENERIC_READ, // 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL, // 공유 방식, 파일이 개방된 상태에서 다른 프로세스가 파일 개방을 하는 것을 허가할 것인가(NULL 공유하지 않음)
		NULL, // 보안 속성, NULL 인 경우 기본 보안 상태
		OPEN_EXISTING,	// 생성 방식, (CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 열기)
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 파일 등등),FILE_ATTRIBUTE_NORMAL : 특수 속성이 없는 일반 파일 형태 
		NULL); // 생성될 파일의 속성을 제공할 템플릿 파일 ( 사용하지 않기 때문에 NULL)
	
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OKCANCEL);
		return;
	}
	
	DWORD dwBytesRead;
	StructType type;
	size_t count;



	while (ReadFile(hFile, &type, sizeof(type), &dwBytesRead, NULL) && dwBytesRead > 0) {
		switch (type) {
		case TYPE_LINE:
			ReadFile(hFile, &count, sizeof(count), &dwBytesRead, NULL);
			for (size_t i = 0; i < count; ++i) {
				LINE line;
				ReadFile(hFile, &line, sizeof(LINE), &dwBytesRead, NULL);
				m_LineList.push_back(new CLine(line));
			}
			break;
		case TYPE_BOX:
			ReadFile(hFile, &count, sizeof(count), &dwBytesRead, NULL);
			for (size_t i = 0; i < count; ++i) {
				RECT box;
				ReadFile(hFile, &box, sizeof(RECT), &dwBytesRead, NULL);
				m_BoxList.push_back(new CBox(box));
			}
			break;
			// 기타 타입들에 대한 처리...
		}
	}

	CloseHandle(hFile);
	
	MessageBox(g_hWnd, _T("Load2 완료"), L"성공", MB_OK);
	
}

void CLineMgr::Clear_List()
{
	m_LineList.clear();
	m_BoxList.clear();
}
