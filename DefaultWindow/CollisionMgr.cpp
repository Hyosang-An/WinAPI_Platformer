#include "stdafx.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> Dst, list<CObj*> Src)
{
	RECT	rc{};

	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->OnColision(Sour); // <- Dead�� ȣ������ �ʰ� �浹ó�� �Լ� ȣ�� / ��ü���� ó���� Obj ������ �Լ��� ����
				Sour->OnColision(Dest);
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> Dst, list<CObj*> Src)
{
	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->OnColision(Sour);
				Sour->OnColision(Dest);
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	float	fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float	fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	
	return	fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_RectEx(list<CObj*> Dst, list<CObj*> Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				// ���� �浹
				if (fX > fY)
				{
					// �� �浹
					if (Dest->Get_Info().fY < Sour->Get_Info().fY) 
					{
						if ((Dest->Get_Velocity() - Sour->Get_Velocity()).y <= 0)
							if ((OBJID::BULLET != Dest->Get_OBJID()) && (OBJID::BULLET != Sour->Get_OBJID())) 
								continue;
						Dest->OnColisionEX(Sour, INVADEDIRC::BOTTOM, fY); // <- [Sour]�� Dest�� [�Ʒ���]���� [fY��ŭ ħ��]�ߴ�
						Sour->OnColisionEX(Dest, INVADEDIRC::TOP, fY); // <- [Dest]�� Sour�� [����]���� [fY��ŭ ħ��]�ߴ�
					}

					// �� �浹
					else
					{
						if ((Dest->Get_Velocity() - Sour->Get_Velocity()).y >= 0)
							if ((OBJID::BULLET != Dest->Get_OBJID()) && (OBJID::BULLET != Sour->Get_OBJID()))
								continue;
						Dest->OnColisionEX(Sour, INVADEDIRC::TOP, fY); // <- [Sour]�� Dest�� [����]���� [fY��ŭ ħ��]�ߴ�
						Sour->OnColisionEX(Dest, INVADEDIRC::BOTTOM, fY); // <- [Dest]�� Sour�� [�Ʒ���]���� [fY��ŭ ħ��]�ߴ�
					}
				}

				// �¿� �浹
				else
				{
					// �� �浹
					if (Dest->Get_Info().fX < Sour->Get_Info().fX)
					{
						if ((Dest->Get_Velocity() - Sour->Get_Velocity()).x <= 0)
							if ((OBJID::BULLET != Dest->Get_OBJID()) && (OBJID::BULLET != Sour->Get_OBJID()))
								continue;
						Dest->OnColisionEX(Sour, INVADEDIRC::RIGHT, fX); // <- [Sour]�� Dest�� [������]���� [fX��ŭ ħ��]�ߴ�
						Sour->OnColisionEX(Dest, INVADEDIRC::LEFT, fX); // <- [Dest]�� Sour�� [����]���� [fX��ŭ ħ��]�ߴ�
					}

					// �� �浹
					else
					{
						if ((Dest->Get_Velocity() - Sour->Get_Velocity()).x >= 0)
							if ((OBJID::BULLET != Dest->Get_OBJID()) && (OBJID::BULLET != Sour->Get_OBJID()))
								continue;
						Dest->OnColisionEX(Sour, INVADEDIRC::LEFT, fX); // <- [Sour]�� Dest�� [����]���� [fX��ŭ ħ��]�ߴ�
						Sour->OnColisionEX(Dest, INVADEDIRC::RIGHT, fX); // <- [Dest]�� Sour�� [������]���� [fX��ŭ ħ��]�ߴ�
					}
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj * pDst, CObj * pSrc, float* pX, float *pY)
{
	float	fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float	fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);
	
	float fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float fRadiusY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		// px, py�� ������ 0�̻� ��
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}
	
	return false;
}
