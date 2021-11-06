#include "CollisionHook.h"
#define HOOKPOS_PlayerCollision 0x0054BCEE
bool CollisionCheck(object_base *obj1, object_base *obj2);

void __declspec (naked) HOOK_PlayerCollision(void)
{
	static object_base *_obj1, *_obj2;
	static DWORD RETURN_ovrwr = 0x54CEFC, RETURN_process = 0x0054BCF4, RETURN_noProcessing = 0x54CF8D;
	__asm
	{
		jz hk_PlCol_process
		jmp RETURN_ovrwr
	}

hk_PlCol_process:
	__asm
	{
		pushad
		mov _obj2, esi // processing collision of *_info (esi)
		mov _obj1, edi // with *_info (edi)
	}

	// process collision if cheat not enabled
	if (!Collision->_enabled)
		goto hk_PlCol_processCol;

	// already crashed, if true
	if (_obj1 == nullptr || _obj2 == nullptr)
		goto hk_PlCol_noCol;

	// check for disable collision
	if (CollisionCheck(_obj1, _obj2))
		goto hk_PlCol_noCol;

	if (Collision->_nocolBuildings)
	{
		__asm popad;
		__asm jmp RETURN_ovrwr
	}

hk_PlCol_processCol:
	__asm popad
	__asm jmp RETURN_process

	hk_PlCol_noCol :
				   __asm popad
				   __asm jmp RETURN_noProcessing
}

void ToggleCollisionHook(bool enabled)
{
	static byte _collisionHookBackup[6];
	if (enabled)
	{
		memcpy_safe(_collisionHookBackup, (void *)HOOKPOS_PlayerCollision, 6);
		SF->getGame()->createHook((void *)HOOKPOS_PlayerCollision, HOOK_PlayerCollision, DETOUR_TYPE_JMP, 6);
	}
	else
	{
		memcpy_safe((void *)HOOKPOS_PlayerCollision, _collisionHookBackup, 6);
	}
}

bool CollisionCheck(object_base *obj1, object_base *obj2)
{
	return (obj2->nType == 3 || obj2->nType == 2) &&
		((obj1->nType == 2 && Collision->_nocolVehicles) ||
		(obj1->nType == 3 && Collision->_nocolPeds) ||
			(obj1->nType == 4 && Collision->_nocolObjects));
}
