#include "HookRakNet.h"

bool __stdcall outcomingData(stRakNetHookParams *params) {

	switch (params->packetId) {

	case ID_VEHICLE_SYNC:

		stInCarData dataIncar;
		memset(&dataIncar, 0, sizeof(stInCarData));
		byte packetIncar;

		params->bitStream->ResetReadPointer();
		params->bitStream->Read(packetIncar);
		params->bitStream->Read((PCHAR)&dataIncar, sizeof(stInCarData));
		params->bitStream->ResetReadPointer();

		if (ImGuiWindow->FakePos)
			dataIncar.fPosition[1] += 10;

		if (ImGuiWindow->TransferOfControlVehicle)
			dataIncar.sVehicleID = ImGuiWindow->InputTransferOfControlVehicleId;

		params->bitStream->ResetWritePointer();
		params->bitStream->Write(packetIncar);
		params->bitStream->Write((PCHAR)&dataIncar, sizeof(stInCarData));

		break;

	case ID_PLAYER_SYNC:

		stOnFootData dataOnfoot;
		memset(&dataOnfoot, 0, sizeof(stOnFootData));
		byte packetOnfoot;

		params->bitStream->ResetReadPointer();
		params->bitStream->Read(packetOnfoot);
		params->bitStream->Read((PCHAR)&dataOnfoot, sizeof(stOnFootData));
		params->bitStream->ResetReadPointer();

		if (ImGuiWindow->FakePos)
			dataOnfoot.fPosition[1] += 10;
		
		if(ImGuiWindow->GhostMode)
			dataOnfoot.byteSpecialAction = (BYTE)3;

		params->bitStream->ResetWritePointer();
		params->bitStream->Write(packetOnfoot);
		params->bitStream->Write((PCHAR)&dataOnfoot, sizeof(stOnFootData));

		break;
	case ID_UNOCCUPIED_SYNC:

		stUnoccupiedData dataUnoc;
		memset(&dataUnoc, 0, sizeof(stUnoccupiedData));
		byte packetUnoc;

		params->bitStream->ResetReadPointer();
		params->bitStream->Read(packetUnoc);
		params->bitStream->Read((PCHAR)&dataUnoc, sizeof(stUnoccupiedData));
		params->bitStream->ResetReadPointer();

		if (ImGuiWindow->RollCrasher) {
			dataUnoc.fRoll[0] = 99999999999;
			dataUnoc.fRoll[1] = 99999999999;
			dataUnoc.fRoll[2] = 99999999999;
			SF->getSAMP()->sendEnterVehicle(dataUnoc.sVehicleID, 0);
		}
		if (ImGuiWindow->FuckCar) {
			dataUnoc.fDirection[0] = 10;
			dataUnoc.fDirection[1] = 10;
			dataUnoc.fDirection[2] = 10; 
		}
		params->bitStream->ResetWritePointer();
		params->bitStream->Write(packetUnoc);
		params->bitStream->Write((PCHAR)&dataUnoc, sizeof(stUnoccupiedData));

		break;
	case ID_AIM_SYNC:
		stAimData data;
		memset(&data, 0, sizeof(stAimData));
		byte packet;

		params->bitStream->ResetReadPointer();
		params->bitStream->Read(packet);
		params->bitStream->Read((PCHAR)&data, sizeof(stAimData));
		params->bitStream->ResetReadPointer();
		//
		if (ImGuiWindow->AimZ) 
			data.fAimZ = sqrt((float)-1);
		
		if (ImGuiWindow->DerpCam) 
			data.byteCamMode = 45;
		
		//
		params->bitStream->ResetWritePointer();
		params->bitStream->Write(packet);
		params->bitStream->Write((PCHAR)&data, sizeof(stAimData));
		break;

	case ID_BULLET_SYNC:

		stBulletData dataBullet;
		memset(&dataBullet, 0, sizeof(stBulletData));
		byte packetBullet;

		params->bitStream->ResetReadPointer();
		params->bitStream->Read(packetBullet);
		params->bitStream->Read((PCHAR)&dataBullet, sizeof(stBulletData));
		params->bitStream->ResetReadPointer();
		//
		if (ImGuiWindow->SubstitutionWeapon)
			dataBullet.byteWeaponID = ImGuiWindow->SubstitutionWeaponId;
		//
		params->bitStream->ResetWritePointer();
		params->bitStream->Write(packetBullet);
		params->bitStream->Write((PCHAR)&dataBullet, sizeof(stBulletData));

		break;
	}

	return true;
}

bool __stdcall incomingData(stRakNetHookParams *params) {
	switch (params->packetId) {
	case ID_PLAYER_SYNC: {
		stOnFootData data;
		unsigned short PlayerID;
		params->bitStream->IgnoreBits(8);
		params->bitStream->Read((unsigned short)PlayerID);
		char *name = SF->getSAMP()->getPlayers()->pRemotePlayer[PlayerID]->szPlayerName;

		bool bLR, bUD;
		params->bitStream->Read(bLR);
		if (bLR)
			params->bitStream->Read(data.sLeftRightKeys);
		params->bitStream->Read(bUD);
		if (bUD)
			params->bitStream->Read(data.sUpDownKeys);
		params->bitStream->Read(data.sKeys);
		//позиция
		params->bitStream->Read(data.fPosition[0]);
		params->bitStream->Read(data.fPosition[1]);
		params->bitStream->Read(data.fPosition[2]);
		//кватернион
		params->bitStream->ReadNormQuat(data.fQuaternion[0], data.fQuaternion[1], data.fQuaternion[2], data.fQuaternion[3]);
		BYTE byteHealthArmour;
		BYTE byteHealth, byteArmour;
		BYTE byteArmTemp = 0, byteHlTemp = 0;

		params->bitStream->Read(byteHealthArmour);
		byteArmTemp = (byteHealthArmour & 0x0F);
		byteHlTemp = (byteHealthArmour >> 4);

		if (byteArmTemp == 0xF) byteArmour = 100;
		else if (byteArmTemp == 0) byteArmour = 0;
		else byteArmour = byteArmTemp * 7;

		if (byteHlTemp == 0xF) byteHealth = 100;
		else if (byteHlTemp == 0) byteHealth = 0;
		else byteHealth = byteHlTemp * 7;

		data.byteHealth = byteHealth;
		data.byteArmor = byteArmour;
		//оружие
		params->bitStream->Read(data.byteCurrentWeapon);
		//действие
		params->bitStream->Read(data.byteSpecialAction);
		//скорость
		params->bitStream->ReadVector(data.fMoveSpeed[0], data.fMoveSpeed[1], data.fMoveSpeed[2]);

		if (ImGuiWindow->SyncLogger && PlayerID == ImGuiWindow->inputSyncAllLoggerPlayerId && ImGuiWindow->SyncLoggerOnfoot) {
			sprintf(ImGuiWindow->SyncAllLoggerPlayer,
				"last incoming onfoot packet:\n%s[%i]\nfPosition:%.2f,%.2f,%.2f\nfQuaternion:%.2f,%.2f,%.2f,%.2f\nbyteHealth:%i\nbyteArmor:%i\nbyteCurrentWeapon:%i\nbyteSpecialAction:%i\nfMoveSpeed:%.2f,%.2f,%.2f",
				SF->getSAMP()->getPlayers()->GetPlayerName(PlayerID), PlayerID, data.fPosition[0], data.fPosition[1], data.fPosition[2], data.fQuaternion[0], data.fQuaternion[1], data.fQuaternion[2],
				data.fQuaternion[3], data.byteHealth, data.byteArmor, data.byteCurrentWeapon, data.byteSpecialAction,
				data.fMoveSpeed[0], data.fMoveSpeed[1], data.fMoveSpeed[2]);
			return true;
		}

		if (ImGuiWindow->onfoot) {

			if (data.fMoveSpeed[0] > 1 || data.fMoveSpeed[1] > 1 || data.fMoveSpeed[2] > 1 || data.fMoveSpeed[0] < -1 || data.fMoveSpeed[1] < -1 || data.fMoveSpeed[2] < -1) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fMoveSpeed | Onfoot\n", name, PlayerID);
				return false;
			}

			if (data.fQuaternion[0] > 1 || data.fQuaternion[0] < -1 || data.fQuaternion[1] > 1 || data.fQuaternion[1] < -1 || data.fQuaternion[2] > 1 || data.fQuaternion[2] < -1 || data.fQuaternion[3] > 1 || data.fQuaternion[3] < -1) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fQuaternion | Onfoot\n", name, PlayerID);
				return false;
			}

			if (data.fPosition[0] > 20000 || data.fPosition[1] > 20000 || data.fPosition[2] > 20000 || data.fPosition[0] < -20000 || data.fPosition[1] < -20000 || data.fPosition[2] < -20000) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fPosition | Onfoot\n", name, PlayerID);
				return false;
			}
		}

		break;
	}

	case ID_VEHICLE_SYNC: {
		stInCarData data;
		unsigned short PlayerID;
		params->bitStream->IgnoreBits(8);
		params->bitStream->Read((unsigned short)PlayerID);
		char *name = SF->getSAMP()->getPlayers()->pRemotePlayer[PlayerID]->szPlayerName;

		//vehID
		params->bitStream->Read(data.sVehicleID);

		// KEYS
		params->bitStream->Read(data.sLeftRightKeys);
		params->bitStream->Read(data.sUpDownKeys);
		params->bitStream->Read(data.sKeys);

		// QUATERNIONS
		params->bitStream->ReadNormQuat(data.fQuaternion[0], data.fQuaternion[1], data.fQuaternion[2], data.fQuaternion[3]);

		// POSITION
		params->bitStream->Read(data.fPosition[0]);
		params->bitStream->Read(data.fPosition[1]);
		params->bitStream->Read(data.fPosition[2]);

		// MOVE SPEED
		params->bitStream->ReadVector(data.fMoveSpeed[0], data.fMoveSpeed[1], data.fMoveSpeed[2]);

		//health car
		WORD wTempVehicleHealth;
		params->bitStream->Read(wTempVehicleHealth);
		data.fVehicleHealth = (float)wTempVehicleHealth;

		//health && armor player
		BYTE byteHealthArmour;
		BYTE bytePlayerHealth, bytePlayerArmour;
		BYTE byteArmTemp = 0, byteHlTemp = 0;

		params->bitStream->Read(byteHealthArmour);
		byteArmTemp = (byteHealthArmour & 0x0F);
		byteHlTemp = (byteHealthArmour >> 4);

		if (byteArmTemp == 0xF) bytePlayerArmour = 100;
		else if (byteArmTemp == 0) bytePlayerArmour = 0;
		else bytePlayerArmour = byteArmTemp * 7;

		if (byteHlTemp == 0xF) bytePlayerHealth = 100;
		else if (byteHlTemp == 0) bytePlayerHealth = 0;
		else bytePlayerHealth = byteHlTemp * 7;

		data.bytePlayerHealth = bytePlayerHealth;
		data.byteArmor = bytePlayerArmour;

		//weapon
		params->bitStream->Read(data.byteCurrentWeapon);

		if (ImGuiWindow->SyncLogger && PlayerID == ImGuiWindow->inputSyncAllLoggerPlayerId && ImGuiWindow->SyncLoggerIncar) {
			sprintf(ImGuiWindow->SyncAllLoggerPlayer,
				"last incoming incar packet:\n%s[%i]\nsVehicleID:%i\nsLeftRightKeys:%i\nsUpDownKeys:%i\nsKeys:%i\nfQuaternion:%.2f,%.2f,%.2f,%.2f\nfPosition:%.2f,%.2f,%.2f\nfMoveSpeed:%.2f,%.2f,%.2f\nfVehicleHealth:%.2f",
				SF->getSAMP()->getPlayers()->GetPlayerName(PlayerID), PlayerID, data.sVehicleID, data.sLeftRightKeys,
				data.sUpDownKeys, data.sKeys, data.fQuaternion[0], data.fQuaternion[1], data.fQuaternion[2], data.fQuaternion[3],
				data.fPosition[0], data.fPosition[1], data.fPosition[2], data.fMoveSpeed[0], data.fMoveSpeed[1], data.fMoveSpeed[2],
				data.fVehicleHealth);
			return true;
		}

		if (ImGuiWindow->incar) {
			if ((*(DWORD*)0xBA18FC && data.sVehicleID == SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData.sVehicleID && SF->getSAMP()->getPlayers()->pRemotePlayer[PlayerID]->pPlayerData->byteSeatID == 0)) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] пытается взять под контроль вашу машину | Incar\n", name, PlayerID);
				return false;
			}

			if (data.fMoveSpeed[0] > 1 || data.fMoveSpeed[1] > 1 || data.fMoveSpeed[2] > 1 || data.fMoveSpeed[0] < -1 || data.fMoveSpeed[1] < -1 || data.fMoveSpeed[2] < -1) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fMoveSpeed | Incar\n", name, PlayerID);
				return false;
			}

			if (data.fQuaternion[0] > 1 || data.fQuaternion[0] < -1 || data.fQuaternion[1] > 1 || data.fQuaternion[1] < -1 || data.fQuaternion[2] > 1 || data.fQuaternion[2] < -1 || data.fQuaternion[3] > 1 || data.fQuaternion[3] < -1) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fQuaternion | Incar\n", name, PlayerID);
				return false;
			}

			if (data.fPosition[0] > 20000 || data.fPosition[1] > 20000 || data.fPosition[2] > 20000 || data.fPosition[0] < -20000 || data.fPosition[1] < -20000 || data.fPosition[2] < -20000) {
				ExampleAppLog->AddLog(u8"Игрок:[%i] Отправил невалидный fPosition | Incar\n", PlayerID);
				return false;
			}
		}

		break;
	}

	case ID_BULLET_SYNC: {
		stBulletData data;
		unsigned short PlayerID;
		params->bitStream->IgnoreBits(8);
		params->bitStream->Read((unsigned short)PlayerID);
		char *name = SF->getSAMP()->getPlayers()->pRemotePlayer[PlayerID]->szPlayerName;
		params->bitStream->Read((PCHAR)&data, sizeof(stBulletData));

		if (ImGuiWindow->SyncLogger && PlayerID == ImGuiWindow->inputSyncAllLoggerPlayerId && ImGuiWindow->SyncLoggerBullet) {
			sprintf(ImGuiWindow->SyncAllLoggerPlayer,
				"last incoming bullet packet:\n%s[%i]\nbyteType:%i\nbyteWeaponID:%i\nfCenter:%.2f,%.2f,%.2f\nfOrigin:%.2f,%.2f,%.2f\nfTarget:%.2f,%.2f,%.2f\nsTargetID:%i",
				SF->getSAMP()->getPlayers()->GetPlayerName(PlayerID), PlayerID, data.byteType, data.byteWeaponID,
				data.fCenter[0], data.fCenter[1], data.fCenter[2], data.fOrigin[0], data.fOrigin[1], data.fOrigin[2],
				data.fTarget[0], data.fTarget[1], data.fTarget[2], data.sTargetID);
			return true;
		}

		if (ImGuiWindow->bullet) {

			if (data.fOrigin[0] > 20000 || data.fOrigin[1] > 20000 || data.fOrigin[2] > 20000) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fOrigin | Bullet\n", name, PlayerID);
				return false;
			}

			if (data.fCenter[0] > 20000 || data.fCenter[1] > 20000 || data.fCenter[2] > 20000) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fCenter | Bullet\n", name, PlayerID);
				return false;
			}
		}

		break;
	}

	case ID_AIM_SYNC: {

		stAimData data;
		unsigned short PlayerID;
		params->bitStream->IgnoreBits(8);
		params->bitStream->Read((unsigned short)PlayerID);
		char *name = SF->getSAMP()->getPlayers()->pRemotePlayer[PlayerID]->szPlayerName;
		params->bitStream->Read((PCHAR)&data, sizeof(stAimData));

		if (ImGuiWindow->SyncLogger && PlayerID == ImGuiWindow->inputSyncAllLoggerPlayerId && ImGuiWindow->SyncLoggerAim) {
			sprintf(ImGuiWindow->SyncAllLoggerPlayer,
				"last incoming aim packet:\n%s[%i]\nbyteCamMode:%i\nbyteWeaponState:%i\nfAimZ:%.2f",
				SF->getSAMP()->getPlayers()->GetPlayerName(PlayerID), PlayerID, data.byteCamMode, data.byteWeaponState, data.fAimZ);
			return true;
		}

		if (ImGuiWindow->aim) {

			if (data.byteCamMode != 4 || data.byteCamMode != 53 || data.byteCamMode != 18 || data.byteCamMode != 55)
				return false;

			if (data.fAimZ > 1.2 || data.fAimZ < -1.2) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fAimZ | Aim\n", name, PlayerID);
				return false;
			}

		}

		break;
	}

	case ID_PASSENGER_SYNC: {
		stPassengerData data;
		unsigned short PlayerID;
		params->bitStream->IgnoreBits(8);
		params->bitStream->Read((unsigned short)PlayerID);
		char *name = SF->getSAMP()->getPlayers()->pRemotePlayer[PlayerID]->szPlayerName;
		params->bitStream->Read((PCHAR)&data, sizeof(stPassengerData));

		if (ImGuiWindow->SyncLogger && PlayerID == ImGuiWindow->inputSyncAllLoggerPlayerId && ImGuiWindow->SyncLoggerPassenger) {
			sprintf(ImGuiWindow->SyncAllLoggerPlayer,
				"last incoming passenger packet:\n%s[%i]\nbyteHealth:%i\nbyteSeatID:%i\nfPosition:%.2f,%.2f,%.2f\nsVehicleID:%i",
				SF->getSAMP()->getPlayers()->GetPlayerName(PlayerID), PlayerID, data.byteHealth, data.byteSeatID,
				data.fPosition[0], data.fPosition[1], data.fPosition[2], data.sVehicleID);
			return true;
		}

		if (ImGuiWindow->passenger) {

			if (data.fPosition[0] > 20000 || data.fPosition[1] > 20000 || data.fPosition[2] > 20000 || data.fPosition[0] < -20000 || data.fPosition[1] < -20000 || data.fPosition[2] < -20000) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fPosition | Passenger\n", name, PlayerID);
				return false;
			}

			if (data.byteSeatID > 6) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный byteSeatID | Passenger\n", name, PlayerID);
				return false;
			}
		}

		break;
	}

	case ID_UNOCCUPIED_SYNC: {
		stUnoccupiedData data;
		unsigned short PlayerID;
		params->bitStream->IgnoreBits(8);
		params->bitStream->Read((unsigned short)PlayerID);
		char *name = SF->getSAMP()->getPlayers()->pRemotePlayer[PlayerID]->szPlayerName;
		params->bitStream->Read((PCHAR)&data, sizeof(stUnoccupiedData));

		if (ImGuiWindow->SyncLogger && PlayerID == ImGuiWindow->inputSyncAllLoggerPlayerId && ImGuiWindow->SyncLoggerUnoccupied) {
			sprintf(ImGuiWindow->SyncAllLoggerPlayer,
				"last incoming unoccupied packet:\n%s[%i]\nbyteSeatID:%i\nfDirection:%.2f,%.2f,%.2f\nfHealth:%.2f\nfMoveSpeed:%.2f,%.2f,%.2f\nfPosition:%.2f,%.2f,%.2f\nfRoll:%.2f,%.2f,%.2f\nfTurnSpeed:%.2f,%.2f,%.2f\nsVehicleID:%i",
				SF->getSAMP()->getPlayers()->GetPlayerName(PlayerID), PlayerID,data.byteSeatID,
				data.fDirection[0], data.fDirection[1], data.fDirection[2],data.fHealth,
				data.fMoveSpeed[0], data.fMoveSpeed[1], data.fMoveSpeed[2],data.fPosition[0], data.fPosition[1], data.fPosition[2],
				data.fRoll[0], data.fRoll[1], data.fRoll[2],data.fTurnSpeed[0], data.fTurnSpeed[1], data.fTurnSpeed[2],data.sVehicleID);
			return true;
		}

		if (ImGuiWindow->unoccupied) {

			if (data.fMoveSpeed[0] > 0.9 || data.fMoveSpeed[1] > 0.9 || data.fMoveSpeed[2] > 0.9 || data.fMoveSpeed[0] < -0.9 || data.fMoveSpeed[1] < -0.9 || data.fMoveSpeed[2] < -0.9) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fMoveSpeed | Unoccupied\n", name, PlayerID);
				return false;
			}

			if (data.fTurnSpeed[0] > 1 || data.fTurnSpeed[1] > 1 || data.fTurnSpeed[2] > 1 || data.fTurnSpeed[0] < -1 || data.fTurnSpeed[1] < -1 || data.fTurnSpeed[2] < -1) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fTurnSpeed | Unoccupied\n", name, PlayerID);
				return false;
			}

			if (data.fDirection[0] > 1 || 
				data.fDirection[1] > 1 || 
				data.fDirection[2] > 1 || 
				data.fDirection[0] < -1 || 
				data.fDirection[1] < -1 || 
				data.fDirection[2] < -1) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fDirection | Unoccupied\n", name, PlayerID);
				return false;
			}

			if (data.fRoll[0] > 1 || 
				data.fRoll[1] > 1 || 
				data.fRoll[2] > 1 ||
				data.fRoll[0] < -1 || 
				data.fRoll[1] < -1 ||
				data.fRoll[2] < -1) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fRoll | Unoccupied\n", name, PlayerID);
				return false;
			}

			if (data.fPosition[0] > 20000 || data.fPosition[1] > 20000 || data.fPosition[2] > 20000 || data.fPosition[0] < -20000 || data.fPosition[1] < -20000 || data.fPosition[2] < -20000) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный fPosition | Unoccupied\n", name, PlayerID);
				return false;
			}

			if (data.byteSeatID > 6) {
				ExampleAppLog->AddLog(u8"Игрок:%s[%i] Отправил невалидный byteSeatID | Unoccupied\n", name, PlayerID);
				return false;
			}
		}

		break;
	}
	}
	return true;
}

//-----------------------------------\\

bool __stdcall outcomingRPC(stRakNetHookParams *params) {

	switch (params->packetId) {

	case RPC_ClickPlayer:
		CState->LoggerOutcomingRPC = "RPC_ClickPlayer";
		break;

	case RPC_ClientJoin:
		CState->LoggerOutcomingRPC = "RPC_ClientJoin";
		break;

	case RPC_EnterVehicle:
		CState->LoggerOutcomingRPC = "RPC_EnterVehicle";
		break;

	case RPC_EnterEditObject:
		CState->LoggerOutcomingRPC = "RPC_EnterEditObject";
		break;

	case RPC_ScriptCash:
		CState->LoggerOutcomingRPC = "RPC_ScriptCash";
		break;

	case RPC_ServerCommand:
		CState->LoggerOutcomingRPC = "RPC_ServerCommand";
		break;

	case RPC_Spawn:
		CState->LoggerOutcomingRPC = "RPC_Spawn";
		break;

	case RPC_Death:
		CState->LoggerOutcomingRPC = "RPC_Death";
		break;

	case RPC_NPCJoin:
		CState->LoggerOutcomingRPC = "RPC_NPCJoin";
		break;

	case RPC_DialogResponse:
		CState->LoggerOutcomingRPC = "RPC_DialogResponse";
		break;

	case RPC_ClickTextDraw:
		CState->LoggerOutcomingRPC = "RPC_ClickTextDraw";
		break;

	case RPC_ScmEvent:
		CState->LoggerOutcomingRPC = "RPC_ScmEvent";
		break;

	case RPC_WeaponPickupDestroy:
		CState->LoggerOutcomingRPC = "RPC_WeaponPickupDestroy";
		break;

	case RPC_Chat:
		CState->LoggerOutcomingRPC = "RPC_Chat";
		break;

	case RPC_SrvNetStats:
		CState->LoggerOutcomingRPC = "RPC_SrvNetStats";
		break;

	case RPC_ClientCheck:
		CState->LoggerOutcomingRPC = "RPC_ClientCheck";
		break;

	case RPC_DamageVehicle:
		CState->LoggerOutcomingRPC = "RPC_DamageVehicle";
		break;

	case RPC_GiveTakeDamage:
		CState->LoggerOutcomingRPC = "RPC_GiveTakeDamage";
		break;

	case RPC_EditAttachedObject:
		CState->LoggerOutcomingRPC = "RPC_EditAttachedObject";
		break;

	case RPC_EditObject:
		CState->LoggerOutcomingRPC = "RPC_EditObject";
		break;

	case RPC_SetInteriorId:
		CState->LoggerOutcomingRPC = "RPC_SetInteriorId";
		break;

	case RPC_MapMarker:
		CState->LoggerOutcomingRPC = "RPC_MapMarker";
		break;

	case RPC_RequestClass:
		CState->LoggerOutcomingRPC = "RPC_RequestClass";
		break;

	case RPC_RequestSpawn:
		CState->LoggerOutcomingRPC = "RPC_RequestSpawn";
		break;

	case RPC_PickedUpPickup:
		CState->LoggerOutcomingRPC = "RPC_PickedUpPickup";
		break;

	case RPC_MenuSelect:
		CState->LoggerOutcomingRPC = "RPC_MenuSelect";
		break;

	case RPC_VehicleDestroyed:
		CState->LoggerOutcomingRPC = "RPC_VehicleDestroyed";
		break;

	case RPC_MenuQuit:
		CState->LoggerOutcomingRPC = "RPC_MenuQuit";
		break;

	case RPC_ExitVehicle:
		CState->LoggerOutcomingRPC = "RPC_ExitVehicle";
		break;

	case RPC_UpdateScoresPingsIPs:
		CState->LoggerOutcomingRPC = "RPC_UpdateScoresPingsIPs";
		break;
	}
	return true;
}

bool __stdcall incomingRPC(stRakNetHookParams *params) {

	switch (params->packetId) {

	case RPC_ScrSetPlayerName:
		if (BlockRPC->RPC_ScrSetPlayerName)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerName";
		break;

	case RPC_ScrSetPlayerPos:
		if (BlockRPC->RPC_ScrSetPlayerPos)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerPos";
		break;

	case RPC_ScrSetPlayerPosFindZ:
		if (BlockRPC->RPC_ScrSetPlayerPosFindZ)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerPosFindZ";
		break;

	case RPC_ScrSetPlayerHealth:
		if (BlockRPC->RPC_ScrSetPlayerHealth)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerHealth";
		break;

	case RPC_ScrTogglePlayerControllable:
		if (BlockRPC->RPC_ScrTogglePlayerControllable)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrTogglePlayerControllable";
		break;

	case RPC_ScrPlaySound:
		if (BlockRPC->RPC_ScrPlaySound)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrPlaySound";
		break;

	case RPC_ScrGivePlayerMoney:
		if (BlockRPC->RPC_ScrGivePlayerMoney)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrGivePlayerMoney";
		break;

	case RPC_ScrSetPlayerFacingAngle:
		if (BlockRPC->RPC_ScrSetPlayerFacingAngle)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerFacingAngle";
		break;

	case RPC_ScrResetPlayerWeapons:
		if (BlockRPC->RPC_ScrResetPlayerWeapons)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrResetPlayerWeapons";
		break;

	case RPC_ScrGivePlayerWeapon:
		if (BlockRPC->RPC_ScrGivePlayerWeapon)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrGivePlayerWeapon";
		break;

	case RPC_ScrSetVehicleParamsEx:
		if (BlockRPC->RPC_ScrSetVehicleParamsEx)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetVehicleParamsEx";
		break;

	case RPC_ScrSetPlayerTime:
		if (BlockRPC->RPC_ScrSetPlayerTime)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerTime";
		break;

	case RPC_ScrToggleClock:
		if (BlockRPC->RPC_ScrToggleClock)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrToggleClock";
		break;

	case RPC_ScrSetPlayerDrunkLevel:
		if (BlockRPC->RPC_ScrSetPlayerDrunkLevel)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerDrunkLevel";
		break;

	case RPC_ScrCreate3DTextLabel:
		if (BlockRPC->RPC_ScrCreate3DTextLabel)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrCreate3DTextLabel";
		break;

	case RPC_ScrDisableCheckpoint:
		if (BlockRPC->RPC_ScrDisableCheckpoint)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrDisableCheckpoint";
		break;

	case RPC_ScrSetRaceCheckpoint:
		if (BlockRPC->RPC_ScrSetRaceCheckpoint)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetRaceCheckpoint";
		break;

	case RPC_ScrPlayAudioStream:
		if (BlockRPC->RPC_ScrPlayAudioStream)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrPlayAudioStream";
		break;

	case RPC_ScrStopAudioStream:
		if (BlockRPC->RPC_ScrStopAudioStream)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrStopAudioStream";
		break;

	case RPC_ScrRemoveBuildingForPlayer:
		if (BlockRPC->RPC_ScrRemoveBuildingForPlayer)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrRemoveBuildingForPlayer";
		break;

	case RPC_ScrCreateObject:
		if (BlockRPC->RPC_ScrCreateObject)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrCreateObject";
		break;

	case RPC_ScrSetObjectPos:
		if (BlockRPC->RPC_ScrSetObjectPos)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetObjectPos";
		break;

	case RPC_ScrSetObjectRot:
		if (BlockRPC->RPC_ScrSetObjectRot)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetObjectRot";
		break;

	case RPC_ScrDestroyObject:
		if (BlockRPC->RPC_ScrDestroyObject)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrDestroyObject";
		break;

	case RPC_ScrDeathMessage:
		if (BlockRPC->RPC_ScrDeathMessage)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrDeathMessage";
		break;

	case RPC_ScrSetPlayerMapIcon:
		if (BlockRPC->RPC_ScrSetPlayerMapIcon)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerMapIcon";
		break;

	case RPC_ScrRemoveVehicleComponent:
		if (BlockRPC->RPC_ScrRemoveVehicleComponent)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrRemoveVehicleComponent";
		break;

	case RPC_ScrUpdate3DTextLabel:
		if (BlockRPC->RPC_ScrUpdate3DTextLabel)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrUpdate3DTextLabel";
		break;

	case RPC_ScrChatBubble:
		if (BlockRPC->RPC_ScrChatBubble)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrChatBubble";
		break;

	case RPC_ScrShowDialog:
		if (BlockRPC->RPC_ScrShowDialog)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrShowDialog";
		break;

	case RPC_ScrDestroyPickup:
		if (BlockRPC->RPC_ScrDestroyPickup)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrDestroyPickup";
		break;

	case RPC_ScrSetPlayerArmour:
		if (BlockRPC->RPC_ScrSetPlayerArmour)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerArmour";
		break;

	case RPC_ScrSetSpawnInfo:
		if (BlockRPC->RPC_ScrSetSpawnInfo)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetSpawnInfo";
		break;

	case RPC_ScrRemovePlayerFromVehicle:
		if (BlockRPC->RPC_ScrRemovePlayerFromVehicle)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrRemovePlayerFromVehicle";
		break;

	case RPC_ScrSetPlayerColor:
		if (BlockRPC->RPC_ScrSetPlayerColor)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerColor";
		break;

	case RPC_ScrDisplayGameText:
		if (BlockRPC->RPC_ScrDisplayGameText)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrDisplayGameText";
		break;

	case RPC_ScrForceClassSelection:
		if (BlockRPC->RPC_ScrForceClassSelection)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrForceClassSelection";
		break;

	case RPC_ScrAttachObjectToPlayer:
		if (BlockRPC->RPC_ScrAttachObjectToPlayer)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrAttachObjectToPlayer";
		break;

	case RPC_ScrCreateExplosion:
		if (BlockRPC->RPC_ScrCreateExplosion)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrCreateExplosion";
		break;

	case RPC_ScrShowPlayerNameTagForPlayer:
		if (BlockRPC->RPC_ScrShowPlayerNameTagForPlayer)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrShowPlayerNameTagForPlayer";
		break;

	case RPC_ScrAttachCameraToObject:
		if (BlockRPC->RPC_ScrAttachCameraToObject)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrAttachCameraToObject";
		break;

	case RPC_ScrInterpolateCamera:
		if (BlockRPC->RPC_ScrInterpolateCamera)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrInterpolateCamera";
		break;

	case RPC_ScrSetObjectMaterial:
		if (BlockRPC->RPC_ScrSetObjectMaterial)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetObjectMaterial";
		break;

	case RPC_ScrGangZoneStopFlash:
		if (BlockRPC->RPC_ScrGangZoneStopFlash)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrGangZoneStopFlash";
		break;

	case RPC_ScrApplyAnimation:
		if (BlockRPC->RPC_ScrApplyAnimation)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrApplyAnimation";
		break;

	case RPC_ScrClearAnimations:
		if (BlockRPC->RPC_ScrClearAnimations)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrClearAnimations";
		break;

	case RPC_ScrSetPlayerSpecialAction:
		if (BlockRPC->RPC_ScrSetPlayerSpecialAction)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerSpecialAction";
		break;

	case RPC_ScrSetPlayerFightingStyle:
		if (BlockRPC->RPC_ScrSetPlayerFightingStyle)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerFightingStyle";
		break;

	case RPC_ScrSetPlayerVelocity:
		if (BlockRPC->RPC_ScrSetPlayerVelocity)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerVelocity";
		break;

	case RPC_ScrSetVehicleVelocity:
		if (BlockRPC->RPC_ScrSetVehicleVelocity)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetVehicleVelocity";
		break;

	case RPC_ScrClientMessage:
		if (BlockRPC->RPC_ScrClientMessage)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrClientMessage";
		break;

	case RPC_ScrSetWorldTime:
		if (BlockRPC->RPC_ScrSetWorldTime)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetWorldTime";
		break;

	case RPC_ScrCreatePickup:
		if (BlockRPC->RPC_ScrCreatePickup)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrCreatePickup";
		break;

	case RPC_ScrSetCheckpoint:
		if (BlockRPC->RPC_ScrSetCheckpoint)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetCheckpoint";
		break;

	case RPC_ScrSetPlayerAttachedObject:
		if (BlockRPC->RPC_ScrSetPlayerAttachedObject)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerAttachedObject";
		break;

	case RPC_ScrStopObject:
		if (BlockRPC->RPC_ScrStopObject)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrStopObject";
		break;

	case RPC_ScrShowTextDraw:
		if (BlockRPC->RPC_ScrShowTextDraw)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrShowTextDraw";
		break;

	case RPC_ScrTextDrawHideForPlayer:
		if (BlockRPC->RPC_ScrTextDrawHideForPlayer)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrTextDrawHideForPlayer";
		break;

	case RPC_ScrServerJoin:
		if (BlockRPC->RPC_ScrServerJoin)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrServerJoin";
		break;

	case RPC_ScrServerQuit:
		if (BlockRPC->RPC_ScrServerQuit)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrServerQuit";
		break;

	case RPC_ScrSetPlayerAmmo:
		if (BlockRPC->RPC_ScrSetPlayerAmmo)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerAmmo";
		break;

	case RPC_ScrSetGravity:
		if (BlockRPC->RPC_ScrSetGravity)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetGravity";
		break;

	case RPC_ScrSetVehicleHealth:
		if (BlockRPC->RPC_ScrSetVehicleHealth)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetVehicleHealth";
		break;

	case RPC_ScrSetWeather:
		if (BlockRPC->RPC_ScrSetWeather)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetWeather";
		break;

	case RPC_ScrSetPlayerSkin:
		if (BlockRPC->RPC_ScrSetPlayerSkin)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerSkin";
		break;

	case RPC_ScrSetPlayerInterior:
		if (BlockRPC->RPC_ScrSetPlayerInterior)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerInterior";
		break;

	case RPC_ScrSetPlayerCameraPos:
		if (BlockRPC->RPC_ScrSetPlayerCameraPos)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerCameraPos";
		break;

	case RPC_ScrSetPlayerCameraLookAt:
		if (BlockRPC->RPC_ScrSetPlayerCameraLookAt)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetPlayerCameraLookAt";
		break;

	case RPC_ScrSetVehiclePos:
		if (BlockRPC->RPC_ScrSetVehiclePos)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetVehiclePos";
		break;

	case RPC_ScrSetVehicleZAngle:
		if (BlockRPC->RPC_ScrSetVehicleZAngle)
			return false;
		CState->LoggerIncomingRPC = "RPC_ScrSetVehicleZAngle";
		break;
	}

	return true;
}