#pragma once
#include <GJHString.h>

class Weapon
{
public:
	enum class ENUM_WEAPONTYPE
	{
		BASIC,
		HEAVYMACHINEGUN,
	};

private:
	ENUM_WEAPONTYPE m_Type;
	GJHString m_TypeStr;
	int m_Ammo;

public:
	void SetWeaponType(ENUM_WEAPONTYPE _Type)
	{
		switch (_Type)
		{
		case Weapon::ENUM_WEAPONTYPE::BASIC:
			m_Ammo = 0;
			m_TypeStr = "Basic";
			break;
		case Weapon::ENUM_WEAPONTYPE::HEAVYMACHINEGUN:
			m_TypeStr = "HeavyMachineGun";
			break;
		}

		m_Type = _Type;
	}

	ENUM_WEAPONTYPE GetWeaponType()
	{
		return m_Type;
	}

	GJHString GetWeaponTypeStr()
	{
		return m_TypeStr;
	}

	int GetAmmo()
	{
		return m_Ammo;
	}

	void SetAmmo(int _Value)
	{
		m_Ammo = _Value;
	}

	void SubAmmo()
	{
		if (0 < m_Ammo)
		{
			--m_Ammo;
		}
	}
};

