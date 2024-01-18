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
				Dest->OnColision(Sour); // <- Dead를 호출하지 않고 충돌처리 함수 호출 / 구체적인 처리는 Obj 내부의 함수에 구현
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
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_Info().fY < Sour->Get_Info().fY) 
					{
						if ((Dest->Get_Velocity() - Sour->Get_Velocity()).y <= 0)
							if ((OBJID::BULLET != Dest->Get_OBJID()) && (OBJID::BULLET != Sour->Get_OBJID())) 
								continue;
						Dest->OnColisionEX(Sour, INVADEDIRC::BOTTOM, fY); // <- [Sour]가 Dest의 [아래쪽]에서 [fY만큼 침범]했다
						Sour->OnColisionEX(Dest, INVADEDIRC::TOP, fY); // <- [Dest]가 Sour의 [위쪽]에서 [fY만큼 침범]했다
					}

					// 하 충돌
					else
					{
						if ((Dest->Get_Velocity() - Sour->Get_Velocity()).y >= 0)
							if ((OBJID::BULLET != Dest->Get_OBJID()) && (OBJID::BULLET != Sour->Get_OBJID()))
								continue;
						Dest->OnColisionEX(Sour, INVADEDIRC::TOP, fY); // <- [Sour]가 Dest의 [위쪽]에서 [fY만큼 침범]했다
						Sour->OnColisionEX(Dest, INVADEDIRC::BOTTOM, fY); // <- [Dest]가 Sour의 [아래쪽]에서 [fY만큼 침범]했다
					}
				}

				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_Info().fX < Sour->Get_Info().fX)
					{
						if ((Dest->Get_Velocity() - Sour->Get_Velocity()).x <= 0)
							if ((OBJID::BULLET != Dest->Get_OBJID()) && (OBJID::BULLET != Sour->Get_OBJID()))
								continue;
						Dest->OnColisionEX(Sour, INVADEDIRC::RIGHT, fX); // <- [Sour]가 Dest의 [오른쪽]에서 [fX만큼 침범]했다
						Sour->OnColisionEX(Dest, INVADEDIRC::LEFT, fX); // <- [Dest]가 Sour의 [왼쪽]에서 [fX만큼 침범]했다
					}

					// 우 충돌
					else
					{
						if ((Dest->Get_Velocity() - Sour->Get_Velocity()).x >= 0)
							if ((OBJID::BULLET != Dest->Get_OBJID()) && (OBJID::BULLET != Sour->Get_OBJID()))
								continue;
						Dest->OnColisionEX(Sour, INVADEDIRC::LEFT, fX); // <- [Sour]가 Dest의 [왼쪽]에서 [fX만큼 침범]했다
						Sour->OnColisionEX(Dest, INVADEDIRC::RIGHT, fX); // <- [Dest]가 Sour의 [오른쪽]에서 [fX만큼 침범]했다
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
		// px, py는 무조건 0이상 값
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}
	
	return false;
}
