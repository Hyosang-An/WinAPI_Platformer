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
		//// �� �浹
		//if (r >= box_rc.left && l <= box_rc.left && box_rc.bottom >= t && b >= box_rc.top)
		//{
		//	pPlayer->Move_PosX(-r + box_rc.left);
		//	return true;
		//}
		//// �� �浹
		//else if (l <= box_rc.right && r >= box_rc.right && box_rc.bottom >= t && b >= box_rc.top)
		//{
		//	pPlayer->Move_PosX(box_rc.right - l);
		//	return true;
		//}
		//// �� �浹
		//else if (box_rc.top >= t && b >= box_rc.top && r >= box_rc.left && l <= box_rc.right)
		//{
		//	pPlayer->Move_PosY(box_rc.top - b);
		//	return true;
		//}
		//// �� �浹
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
			// ���� �浹
			if (fX > fY)
			{
				// �� �浹 �϶��� �ڽ� ���� ���ְ�. �׸��� �� ���� true ��ȯ
				if (pPlayer->Get_Info().fY < box_cy)
				{
					if (pPlayer->Get_Velocity().y >= 0)
					{
						pPlayer->Move_PosY(-fY + 2);
						pPlayer->Set_YVelocity(0);
						return true;
					}
					
				}

				// �� �浹
				else
				{
					pPlayer->Move_PosY(fY);
					pPlayer->Set_YVelocity(1);
				}
			}

			// �¿� �浹
			else
			{
				// �� �浹
				if (pPlayer->Get_Info().fX < box_cx)
				{
					pPlayer->Move_PosX(-fX);
				}

				// �� �浹
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
		// px, py�� ������ 0�̻� ��
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}




void CLineMgr::Load_Data(wchar_t* Data)
{
	HANDLE		hFile = CreateFile(Data, // ���� ��ο� �̸��� ���
		GENERIC_READ, // ���� ���� ���(GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL, // ���� ���, ������ ����� ���¿��� �ٸ� ���μ����� ���� ������ �ϴ� ���� �㰡�� ���ΰ�(NULL �������� ����)
		NULL, // ���� �Ӽ�, NULL �� ��� �⺻ ���� ����
		OPEN_EXISTING,	// ���� ���, (CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����)
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ���� ���),FILE_ATTRIBUTE_NORMAL : Ư�� �Ӽ��� ���� �Ϲ� ���� ���� 
		NULL); // ������ ������ �Ӽ��� ������ ���ø� ���� ( ������� �ʱ� ������ NULL)
	
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
			// ��Ÿ Ÿ�Ե鿡 ���� ó��...
		}
	}

	CloseHandle(hFile);
	
	MessageBox(g_hWnd, _T("Load2 �Ϸ�"), L"����", MB_OK);
	
}

void CLineMgr::Clear_List()
{
	m_LineList.clear();
	m_BoxList.clear();
}
