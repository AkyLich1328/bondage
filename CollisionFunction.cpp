#include "CollisionFunction.h"

bool RegWriteBool(HKEY key, const char *name, bool value)
{
	DWORD val = value;
	return RegSetValueExA(key, name, 0, REG_DWORD, (byte *)&val, 1) == ERROR_SUCCESS;
}

bool RegReadBool(HKEY key, const char *name, bool &value)
{
	DWORD val = 0, type = REG_DWORD, size = 4;
	bool result = RegQueryValueExA(key, name, NULL, &type, (byte *)&val, &size) == ERROR_SUCCESS;
	value = val != 0;
	return result;
}

void UpdateSettings(void)
{
	HKEY key;
	if (RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\SAMPFUNCS\\NoCollisions", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL) == ERROR_SUCCESS)
	{
		RegWriteBool(key, "Vehicles", Collision->_nocolVehicles);
		RegWriteBool(key, "Peds", Collision->_nocolPeds);
		RegWriteBool(key, "Objects", Collision->_nocolObjects);
		RegWriteBool(key, "Buildings", Collision->_nocolBuildings);
		RegCloseKey(key);
	}
}

void ReadSettings(void)
{
	HKEY key;
	if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\SAMPFUNCS\\NoCollisions", 0, KEY_ALL_ACCESS, &key) == ERROR_SUCCESS)
	{
		RegReadBool(key, "Vehicles", Collision->_nocolVehicles);
		RegReadBool(key, "Peds", Collision->_nocolPeds);
		RegReadBool(key, "Objects", Collision->_nocolObjects);
		RegReadBool(key, "Buildings", Collision->_nocolBuildings);
		RegCloseKey(key);
	}
}

void *memcpy_safe(void *_dest, const void *_src, size_t stLen)
{
	if (_dest == nullptr || _src == nullptr || stLen == 0)
		return nullptr;

	MEMORY_BASIC_INFORMATION	mbi;
	VirtualQuery(_dest, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);

	void	*pvRetn = memcpy(_dest, _src, stLen);
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);
	FlushInstructionCache(GetCurrentProcess(), _dest, stLen);
	return pvRetn;
}
