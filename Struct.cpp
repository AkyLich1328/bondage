#include "Struct.h"

void pFunc_::Write(void *addr, void *bytes, size_t byteSize) {
	DWORD prot;
	VirtualProtect(addr, byteSize, PAGE_EXECUTE_READWRITE, &prot);
	memcpy(addr, bytes, byteSize);
	VirtualProtect(addr, byteSize, prot, &prot);
}

void pFunc_::NOP(void *addr, size_t bytes) {
	DWORD prot;
	VirtualProtect(addr, bytes, PAGE_EXECUTE_READWRITE, &prot);
	memset(addr, 0x90, bytes);
	VirtualProtect(addr, bytes, prot, &prot);
}

bool CState_::GMPatch(bool gm) {//бай адский дрочила
	if (gm) {
		pFunc->NOP((void*)0x004B331F, 6);//my
		pFunc->NOP((void*)0x00637590, 10);//my
		pFunc->NOP((void*)0x0063070C, 10);//my
		pFunc->NOP((void*)0x004B3395, 6);//my
		pFunc->Write((void*)(SF->getSAMP()->getSAMPAddr() + 0xA6630), (BYTE*)"\xC2\x04\x00\x90\x90\x90", 6);//RPC
		pFunc->Write((void*)0x0064159F, (BYTE*)"\xE9\x36\x04\x00\x00\x90", 6);//sob??
		pFunc->Write((void*)0x00635DA0, (BYTE*)"\xB8\x00\x00\x00\x00\xC3\x90", 7);//sob parachute
		*(float*)(*(DWORD*)0xB6F5F0 + 0x540) = 100.0f;//set 100 hp
		pFunc->Write((void*)0x006A82CF, (BYTE*)"\xD9\x44\x24\x78", 4);//my car. 0x78 incorrect byte. load nothing?
		pFunc->Write((void*)0x006A832B, (BYTE*)"\xD8\x9E\xC0\x04\x00\x00", 6);//my car
		pFunc->Write((void*)0x006D8083, (BYTE*)"\xD8\x9E\xC0\x04\x00\x00", 6);//my car 
		pFunc->Write((void*)0x00570E7F, (BYTE*)"\xD8\x99\xC0\x04\x00\x00", 6);//my car
		pFunc->Write((void*)(SF->getSAMP()->getSAMPAddr() + 0xB0D70), (BYTE*)"\xC2\x04\x00", 3);//RPC
		return true;
	}
	else {
		pFunc->Write((void*)0x004B331F, (BYTE*)"\x89\x96\x40\x05\x00\x00", 6);//my
		pFunc->Write((void*)0x00637590, (BYTE*)"\xC7\x87\x40\x05\x00\x00\x00\x00\x00\x00", 10);//my
		pFunc->Write((void*)0x0063070C, (BYTE*)"\xC7\x86\x40\x05\x00\x00\x00\x00\x00\x00", 10);//my
		pFunc->Write((void*)0x004B3395, (BYTE*)"\x89\x9E\x40\x05\x00\x00", 6);//my
		pFunc->Write((void*)(SF->getSAMP()->getSAMPAddr() + 0xA6630), (BYTE*)"\x8B\x81\xA4\x02\x00\x00", 6);//setplayerhealth
		pFunc->Write((void*)0x0064159F, (BYTE*)"\x0F\x84\x35\x04\x00\x00", 6);//sob ??
		pFunc->Write((void*)0x00635DA0, (BYTE*)"\x6A\xFF\x68\x06\x0B\x84\x00", 7);//sob parachute
		pFunc->Write((void*)0x006A82CF, (BYTE*)"\xD9\x44\x24\x74", 4);//my car
		pFunc->Write((void*)0x006D8083, (BYTE*)"\xD9\x9E\xC0\x04\x00\x00", 6);//my car в удаление
		pFunc->Write((void*)0x006A832B, (BYTE*)"\xD9\x9E\xC0\x04\x00\x00", 6);//my car
		pFunc->Write((void*)0x00570E7F, (BYTE*)"\xD9\x99\xC0\x04\x00\x00", 6);//my car
		pFunc->Write((void*)(SF->getSAMP()->getSAMPAddr() + 0xB0D70), (BYTE*)"\x8B\x41\x4C", 3);//setvehiclehealth
		return false;
	}
}

bool CState_::AFKPatch(bool afk) {//бай адский дрочила
	if (afk) {
		*(uint8_t*)0x747FB6 = 1;
		*(uint8_t*)0x74805A = 1;
		pFunc->NOP((void*)0x74542B, 8);
		pFunc->NOP((void*)0x53EA88, 6);
		return true;
	}
	else {
		*(uint8_t*)0x747FB6 = 0;
		*(uint8_t*)0x74805A = 0;
		pFunc->Write((void*)0x53EA88, (BYTE*)"\x0F\x84\x7B\x01\x00\x00", 6);
		pFunc->Write((void*)0x74542B, (BYTE*)"\x50\x51\xFF\x15\x00\x83\x85\x00", 8);
		return false;
	}
}

bool CState_::ExtraWSPatch(bool extra) {
	if (extra) {
		*reinterpret_cast<byte*>(0x5109AC) = 235;
		*reinterpret_cast<byte*>(0x5109C5) = 235;
		*reinterpret_cast<byte*>(0x5231A6) = 235;
		*reinterpret_cast<byte*>(0x52322D) = 235;
		*reinterpret_cast<byte*>(0x5233BA) = 235;
		return true;
	}
	else {
		*reinterpret_cast<byte*>(0x5109AC) = 122;
		*reinterpret_cast<byte*>(0x5109C5) = 122;
		*reinterpret_cast<byte*>(0x5231A6) = 117;
		*reinterpret_cast<byte*>(0x52322D) = 117;
		*reinterpret_cast<byte*>(0x5233BA) = 117;
		return false;
	}
}
void CState_::carDamager(){

	if (*(DWORD*)0xBA18FC == 0)
		return;
	BitStream bs;

	bs.Write(SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData.sVehicleID);//кар ид
	bs.Write(53674035);//панели
	bs.Write(67371524);//двери
	bs.Write(5);//свет
	bs.Write(15);//шины

	SF->getRakNet()->SendRPC(RPC_DamageVehicle, &bs);

	BitStream bs1;

	bs1.Write(SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData.sVehicleID);
	bs1.Write(0);
	bs1.Write(0);
	bs1.Write(0);
	bs1.Write(0);

	SF->getRakNet()->SendRPC(RPC_DamageVehicle, &bs1);
}

void CState_::GlassesLagger() {//бай адский дрочила
	if (*(DWORD*)0xBA18FC > 0)
		return;

	static DWORD timer_ = 0;
	static bool status = false;
	static uint8_t this_glass = 0;
	if (GetTickCount() - timer_ > 100) {
		stOnFootData data;
		memcpy(&data, &SF->getSAMP()->getPlayers()->pLocalPlayer->onFootData, sizeof(stOnFootData));
		data.sKeys = status ? 4 : 0;
		status ^= true;
		if (this_glass == 0) {
			data.byteCurrentWeapon = 44;
			this_glass++;
		}
		else if (this_glass == 2) {
			data.byteCurrentWeapon = 45;
			this_glass = 0;
		}
		else if (this_glass == 1)
			this_glass++;
		BitStream bs;
		bs.Write((BYTE)ID_PLAYER_SYNC);
		bs.Write((PCHAR)&data, sizeof(stOnFootData));
		SF->getRakNet()->SendPacket(&bs);
		timer_ = GetTickCount();
	}
}

void CState_::Invize() {//бай севен
	static DWORD timer_ = 0;
	if (GetTickCount() - timer_ > 90) {
		static int iCumMode = 0;
		static bool bAct = false;

		int iCamModes[7] = { 7, 8, 34, 45, 46, 51, 65 };
		if (!bAct)
		{
			stOnFootData OF;
			memcpy(&OF, &SF->getSAMP()->getPlayers()->pLocalPlayer->onFootData, sizeof(stOnFootData));
			OF.sKeys = 128;
			OF.byteCurrentWeapon = 40;
			memcpy(OF.fPosition,&SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12],sizeof(OF.fPosition));

			BitStream fBit;
			fBit.Write((BYTE)ID_PLAYER_SYNC);
			fBit.Write((PCHAR)&OF, sizeof(stOnFootData));
			SF->getRakNet()->SendPacket(&fBit);

			bAct = true;
		}
		else
		{
			stOnFootData OF;
			memcpy(&OF, &SF->getSAMP()->getPlayers()->pLocalPlayer->onFootData, sizeof(stOnFootData));
			OF.sKeys = (uint16_t)128;
			OF.byteCurrentWeapon = (uint8_t)40;
			OF.fQuaternion[0] = 1.f;
			OF.fQuaternion[1] = 0.f;
			OF.fQuaternion[2] = 0.f;
			OF.fQuaternion[3] = 0.f;
			OF.sSurfingVehicleID = (uint16_t)1999;

			BitStream fBit;
			fBit.Write((BYTE)ID_PLAYER_SYNC);
			fBit.Write((PCHAR)&OF, sizeof(stOnFootData));
			SF->getRakNet()->SendPacket(&fBit);

			bAct = false;
		}

		stAimData AIM;
		memcpy(&AIM, &SF->getSAMP()->getPlayers()->pLocalPlayer->aimData, sizeof(stAimData));
		AIM.byteCamMode = iCamModes[iCumMode];

		BitStream fBit;
		fBit.Write((BYTE)ID_AIM_SYNC);
		fBit.Write((PCHAR)&AIM, sizeof(stAimData));
		SF->getRakNet()->SendPacket(&fBit);

		iCumMode++;

		if (iCumMode >= 7)
			iCumMode = 0;

		timer_ = GetTickCount();
	}
}

void CState_::GpciSpoofer(void) {//бай адский дрочила
	static DWORD timer = 0;
	if (GetTickCount() - timer > 30000) {
		for (int i = 13181804; i <= 13181842; i++) {
			BYTE p = rand() % 256;
			*(BYTE*)i = p;
		}
		timer = GetTickCount();
	}
}

void CState_::OnfootRvanka(void) {
	struct actor_info *self = SF->getGame()->actorInfoGet(-1, ACTOR_ALIVE);

	stOnFootData data;
	memset(&data, 0, sizeof(stOnFootData));
	memcpy(&data, &SF->getSAMP()->getPlayers()->pLocalPlayer->onFootData, sizeof(stOnFootData));

	data.fMoveSpeed[0] = sinf(-self->fCurrentRotation) * 3;
	data.fMoveSpeed[1] = cosf(-self->fCurrentRotation) * 3;

	BitStream bsActorSync;
	bsActorSync.Write((BYTE)ID_PLAYER_SYNC);
	bsActorSync.Write((PCHAR)&data, sizeof(stOnFootData));
	SF->getRakNet()->SendPacket(&bsActorSync);
}

void CState_::TeleportMetkaMap(void) {
	if ((*(int *)0xBA6774 != 0))
	{
		float    mapPos[3];
		for (int i = 0; i < (0xAF * 0x28); i += 0x28)
		{
			if (*(short *)(0xBA873D + i) == 4611)
			{
				float    *pos = (float *)(0xBA86F8 + 0x28 + i);
				mapPos[0] = *pos;
				mapPos[1] = *(pos + 1);
				mapPos[2] = GAME->GetWorld()->FindGroundZForPosition(pos[0], pos[1]) + 2.0f;
				PEDSELF->Teleport(mapPos[0], mapPos[1], mapPos[2]);
			}
		}
	}
}

void CState_::AirBreak(void) {

	if (!*(DWORD*)0xBA18FC) {
	
		struct actor_info *self = SF->getGame()->actorInfoGet(-1, ACTOR_ALIVE);
		self->fCurrentRotation = -GAME->GetCamera()->GetCameraRotation();
		PEDSELF->SetOrientation(0, 0, self->fCurrentRotation);
		float angle = *(float*)0xB6F258;
		SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.m_heading = angle + 1.57f;
		float heading = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.m_heading; // не работает
		float pos[3] = {
			SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3],
			SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 1],
			SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 2]
		};
		if (SF->getGame()->isKeyDown(0x57)) { // W
			pos[0] += 1.f * sin(-heading);
			pos[1] += 1.f * cos(-heading);
		}
		else if (SF->getGame()->isKeyDown(0x53)) { // S
			pos[0] -= 1.f * sin(-heading);
			pos[1] -= 1.f * cos(-heading);
		}
		if (SF->getGame()->isKeyDown(0x41)) { // A
			pos[0] -= 1.f * sin(-(heading - 1.57f));
			pos[1] -= 1.f * cos(-(heading - 1.57f));
		}
		else if (SF->getGame()->isKeyDown(0x44)) { // D
			pos[0] -= 1.f * sin(-(heading + 1.57f));
			pos[1] -= 1.f * cos(-(heading + 1.57f));
		}
		if (SF->getGame()->isKeyDown(0x20)) { // A
			pos[2] += 1.0f;
		}
		else if (SF->getGame()->isKeyDown(0xA0)) {
			pos[2] -= 1.0f;
		}
		PEDSELF->Teleport(pos[0], pos[1], pos[2]);
	}
}

bool CState_::RapidFirePatch(bool rapid) {
	if (rapid) {
		*reinterpret_cast<uint32_t*>(13157800) = 11;
		*reinterpret_cast<uint32_t*>(13157804) = 11;
		*reinterpret_cast<uint32_t*>(13157808) = 11;
		*reinterpret_cast<uint32_t*>(13157812) = 11;
		*reinterpret_cast<uint32_t*>(13157816) = 11;
		*reinterpret_cast<uint32_t*>(13157820) = 11;
		*reinterpret_cast<uint32_t*>(13157680) = 11;

		*reinterpret_cast<uint32_t*>(13157688) = 11;
		*reinterpret_cast<uint32_t*>(13157692) = 11;
		*reinterpret_cast<uint32_t*>(13157696) = 11;
		*reinterpret_cast<uint32_t*>(13157700) = 11;
		*reinterpret_cast<uint32_t*>(13157704) = 11;
		*reinterpret_cast<uint32_t*>(13157708) = 11;
		*reinterpret_cast<uint32_t*>(13158472) = 11;
		*reinterpret_cast<uint32_t*>(13158464) = 11;

		*reinterpret_cast<uint32_t*>(13158476) = 11;
		*reinterpret_cast<uint32_t*>(13158480) = 11;
		*reinterpret_cast<uint32_t*>(13158484) = 11;
		*reinterpret_cast<uint32_t*>(13158488) = 11;
		*reinterpret_cast<uint32_t*>(13158492) = 11;
		*reinterpret_cast<uint32_t*>(13157912) = 11;
		*reinterpret_cast<uint32_t*>(13157916) = 11;
		*reinterpret_cast<uint32_t*>(13157920) = 11;
		*reinterpret_cast<uint32_t*>(13157924) = 11;
		*reinterpret_cast<uint32_t*>(13157928) = 11;
		return true;
	}
	else {
		*reinterpret_cast<uint32_t*>(13157800) = 1045220558;
		*reinterpret_cast<uint32_t*>(13157804) = 1067483922;
		*reinterpret_cast<uint32_t*>(13157808) = 1047457520;
		*reinterpret_cast<uint32_t*>(13157812) = 1045220558;
		*reinterpret_cast<uint32_t*>(13157816) = 1067987239;
		*reinterpret_cast<uint32_t*>(13157820) = 1047457520;
		*reinterpret_cast<uint32_t*>(13157680) = 1067450368;

		*reinterpret_cast<uint32_t*>(13157688) = 1045220558;
		*reinterpret_cast<uint32_t*>(13157692) = 1063910376;
		*reinterpret_cast<uint32_t*>(13157696) = 1047457520;
		*reinterpret_cast<uint32_t*>(13157700) = 1045220558;
		*reinterpret_cast<uint32_t*>(13157704) = 1063910376;
		*reinterpret_cast<uint32_t*>(13157708) = 1047457520;
		*reinterpret_cast<uint32_t*>(13158472) = 1045220558;
		*reinterpret_cast<uint32_t*>(13158464) = 1061997773;

		*reinterpret_cast<uint32_t*>(13158476) = 1050723484;
		*reinterpret_cast<uint32_t*>(13158480) = 1047457520;
		*reinterpret_cast<uint32_t*>(13158484) = 1045220558;
		*reinterpret_cast<uint32_t*>(13158488) = 1050723484;
		*reinterpret_cast<uint32_t*>(13158492) = 1047457520;
		*reinterpret_cast<uint32_t*>(13157912) = 1045220558;
		*reinterpret_cast<uint32_t*>(13157916) = 1056763281;
		*reinterpret_cast<uint32_t*>(13157920) = 1045220558;
		*reinterpret_cast<uint32_t*>(13157924) = 1045220558;
		*reinterpret_cast<uint32_t*>(13157928) = 1056763281;
		return false;
	}
}

bool CState_::NoSpreadPatch(bool spread) {
	if (spread) {
		*(float *)13157456 = 100.0; // WEAPON_COLT45 
		*(float *)13157568 = 100.0; // WEAPON_SILENCED 
		*(float *)13157680 = 100.0; // WEAPON_DEAGLE 
		*(float *)13157792 = 100.0; // WEAPON_SHOTGUN 
		*(float *)13157904 = 100.0; // WEAPON_SAWEDOFF 
		*(float *)13158016 = 100.0; // WEAPON_SHOTGSPA 
		*(float *)13158128 = 100.0; // WEAPON_UZI 
		*(float *)13158240 = 100.0; // WEAPON_MP5 
		*(float *)13158352 = 100.0; // WEAPON_AK47 
		*(float *)13158464 = 100.0; // WEAPON_M4 
		*(float *)13158576 = 100.0; // WEAPON_TEC9
		return true;
	}
	else {
		*(float *)13157456 = 0.8;
		*(float *)13157568 = 0.8;
		*(float *)13157680 = 0.8;
		*(float *)13157792 = 0.8;
		*(float *)13157904 = 0.8;
		*(float *)13158016 = 0.8;
		*(float *)13158128 = 0.8;
		*(float *)13158240 = 0.8;
		*(float *)13158352 = 0.8;
		*(float *)13158464 = 0.8;
		*(float *)13158576 = 0.8;
		return false;
	}
}

void CState_::Pylsator(void) {
	static int num = 1;
	static bool pls = false;
	static DWORD timer_ = 0;
	if (GetTickCount() - timer_ > 1) {
		if (num != 100 && !pls) {
			num++;
			if (num == 100)
				pls = true;
		}
		if (num != 1 && pls) {
			num--;
			if (num == 1)
				pls = false;
		}
		timer_ = GetTickCount();
	}
	*(float*)(*(DWORD*)0xB6F5F0 + 0x540) = num;
	*(float*)(*(DWORD*)0xB6F5F0 + 0x548) = num;
}

void CState_::NoReload(void)//бай адский дрочила
{
	struct actor_info *pInfo = SF->getGame()->actorInfoGet(ACTOR_SELF, 0);
	if (ACTOR_IS_DEAD(pInfo)) return;
	// Check weapons
	int wID = pInfo->weapon[pInfo->weapon_slot].id;
	if (wID == 22 || wID == 23 || wID == 24 || wID == 26 || wID == 27 || wID == 28 || wID == 29 ||
		wID == 30 || wID == 31 || wID == 32 || wID == 37 || wID == 38 || wID == 41 || wID == 42) {
		int wSlot = PEDSELF->GetCurrentWeaponSlot();
		if (pInfo->weapon[pInfo->weapon_slot].ammo_clip == 1)
		{
			PEDSELF->SetCurrentWeaponSlot(eWeaponSlot(0));
			PEDSELF->SetCurrentWeaponSlot(eWeaponSlot(wSlot));
		}
	}
	else return;
}

void LogFunc_::ShowExampleAppLog_(bool* opened)
{

	ExampleAppLog->Draw("Log", opened);
}

void pFunc_::vect3_copy(const float in[3], float out[3]) {
	memcpy(out, in, sizeof(float) * 3);
}

float pFunc_::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

int pFunc_::getSAMPVehicleIDFromGTAVehicle(struct vehicle_info *pVehicle)
{
	if (SF->getSAMP()->getVehicles() == NULL)
		return NULL;
	if (SF->getGame()->vehicleInfoGet(VEHICLE_SELF, 0) == pVehicle && SF->getSAMP()->getPlayers() != NULL)
		return SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID;

	int i, iReturn = 0;
	for (i = 0; i < SAMP_MAX_VEHICLES; i++)
	{
		if (SF->getSAMP()->getVehicles()->iIsListed[i] != 1)
			continue;
		if (SF->getSAMP()->getVehicles()->pGTA_Vehicle[i] == pVehicle)
			return i;
	}

	return VEHICLE_SELF;
}

void pFunc_::vect3_vect3_sub(const float in1[3], const float in2[3], float out[3])
{
	int i;

	for (i = 0; i < 3; i++)
		out[i] = in1[i] - in2[i];
}
void pFunc_::vect3_vect3_add(const float in1[3], const float in2[3], float out[3])
{
	int i;

	for (i = 0; i < 3; i++)
		out[i] = in1[i] + in2[i];
}

void pFunc_::vect3_zero(float out[3])
{
	int i;

	for (i = 0; i < 3; i++)
		out[i] = 0.0f;
}

void pFunc_::vehicle_detachables_teleport(struct vehicle_info *info, const float from[3], const float to[3])
{
	int i, n;

	switch (info->vehicle_type)
	{
	case VEHICLE_TYPE_CAR: /* + helicopters and planes */
		for (n = 0; n < 4; n++)
		{
			for (i = 0; i < 3; i++)
				info->detachable_car[n].position[i] += to[i] - from[i];
		}
		break;

	case VEHICLE_TYPE_BIKE:
		for (i = 0; i < 3; i++)
			info->detachable_bike1[0].position[i] += to[i] - from[i];
		for (n = 0; n < 4; n++)
		{
			for (i = 0; i < 3; i++)
				info->detachable_bike2[n].position[i] += to[i] - from[i];
		}
		break;

	case VEHICLE_TYPE_TRAIN:
		/* XXX: fixme */
		break;

	case VEHICLE_TYPE_BOAT:
		for (n = 0; n < 2; n++)
		{
			for (i = 0; i < 3; i++)
				info->detachable_bike2[n].position[i] += to[i] - from[i];
		}
		break;
	}
}

void pFunc_::cheat_vehicle_teleport(struct vehicle_info *info, const float pos[3], int interior_id = 0, bool keepSpeed = true)
{
	if (info == NULL)
		return;

	float diff[3];
	float new_pos[3];
	struct vehicle_info *temp;

	pFunc->vect3_vect3_sub(pos, &info->base.matrix[4 * 3], diff);

	for (temp = info; temp != NULL; temp = temp->trailer)
	{
		if (temp == NULL) return;

		vect3_vect3_add(&temp->base.matrix[4 * 3], diff, new_pos);

		vehicle_detachables_teleport(temp, &temp->base.matrix[4 * 3], new_pos);
		pFunc->vect3_copy(new_pos, &temp->base.matrix[4 * 3]);

		if (!keepSpeed)
		{
			vect3_zero(temp->speed);
			vect3_zero(temp->spin);
		}
	}
}

void CState_::carShooter(void) {//бай адский дрочила
	static int once = 1;
	static int carUsed[SAMP_MAX_VEHICLES];

	struct actor_info *self = SF->getGame()->actorInfoGet(ACTOR_SELF, 0);

	static int v = 0;
	static int x = 0;

	if (SF->getSAMP()->getVehicles()->iIsListed[v] != 1)
		goto find_another_car;


	int car_id = (int)(((DWORD)SF->getSAMP()->getVehicles()->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
	struct vehicle_info *vinfo = SF->getGame()->vehicleInfoGet(car_id, 0);

	int iSAMPVehicleID = pFunc->getSAMPVehicleIDFromGTAVehicle(vinfo);
	if (iSAMPVehicleID == SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID)
	{
		v++;
		goto find_another_car;
	}



	static DWORD timer_ = 0;
	if (GetTickCount() - timer_ > 10) {
		if (SF->getGame()->isKeyDown(0x01))
		{
			float fPos[3];
			pFunc->vect3_copy(&self->base.matrix[4 * 3], fPos);

			fPos[0] += pFunc->cam_matrix[4] * (6.0f + x);
			fPos[1] += pFunc->cam_matrix[5] * (6.0f + x);
			fPos[2] += pFunc->cam_matrix[6] * (2.0f + x);

			stUnoccupiedData data;
			memset(&data, 0, sizeof(stUnoccupiedData));
			data.byteSeatID = 1;
			data.fDirection[0] = pFunc->RandomFloat(-0.9, 0.9);
			data.fDirection[1] = pFunc->RandomFloat(-0.9, 0.9);
			data.fDirection[2] = pFunc->RandomFloat(-0.9, 0.9);
			data.fHealth = 1000;
			data.fMoveSpeed[0] = pFunc->cam_matrix[4] * 7;
			data.fMoveSpeed[1] = pFunc->cam_matrix[5] * 7;
			data.fMoveSpeed[2] = pFunc->cam_matrix[6] * 7;
			data.fPosition[0] = fPos[0];
			data.fPosition[1] = fPos[1];
			data.fPosition[2] = fPos[2];
			data.fRoll[0] = pFunc->RandomFloat(-0.9, 0.9);
			data.fRoll[1] = pFunc->RandomFloat(-0.9, 0.9);
			data.fRoll[2] = pFunc->RandomFloat(-0.9, 0.9);
			data.fTurnSpeed[0] = 0;//random_float(-10000, 10000);
			data.fTurnSpeed[1] = 0;//random_float(-10000, 10000);
			data.fTurnSpeed[2] = 0;//random_float(-10000, 10000);
			data.sVehicleID = v;

			BitStream bs;
			bs.Write((BYTE)ID_UNOCCUPIED_SYNC);
			bs.Write((PCHAR)&data, sizeof(stUnoccupiedData));
			SF->getRakNet()->SendPacket(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

			pFunc->cheat_vehicle_teleport(vinfo, data.fPosition, -1, true);
			pFunc->vect3_copy(data.fMoveSpeed, vinfo->speed);

			x--;
			if (x < -1) x = 0;

			v++;

		}
		timer_ = GetTickCount();
	}

find_another_car:
	for (v; v < SAMP_MAX_VEHICLES; v++)
	{
		if (SF->getSAMP()->getVehicles()->iIsListed[v] == 1)
			break;
	}

	if (v >= SAMP_MAX_VEHICLES)
		v = 0;
}


void CState_::carWall(void) { //бай адский дрочила
	static int once = 1;
	static int carUsed[SAMP_MAX_VEHICLES];

	struct actor_info	*self = SF->getGame()->actorInfoGet(ACTOR_SELF, 0);

	static int v = 0;
	static int x = 0;

	if (SF->getSAMP()->getVehicles()->iIsListed[v] != 1)
		goto find_another_car;

	int car_id = (int)(((DWORD)SF->getSAMP()->getVehicles()->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
	struct vehicle_info	*vinfo = SF->getGame()->vehicleInfoGet(car_id, 0);

	int iSAMPVehicleID = pFunc->getSAMPVehicleIDFromGTAVehicle(vinfo);
	if (iSAMPVehicleID == SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID)
	{
		v++;
		goto find_another_car;
	}



	static DWORD timer_ = 0;
	if (GetTickCount() - timer_ > 10) {

		float fPos[3];
		pFunc->vect3_copy(&self->base.matrix[4 * 3], fPos);

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		float fQuaternion[3] = { 0.0f, 90.0f, 0.0f };

		static int state = 0;

		if (state == 0)
		{
			fPos[2] += 4.0f;
			fPos[1] += 7.5f;
			fSpeed[1] = 3.0f;
			fQuaternion[0] = 100.0f;
		}
		else if (state == 1)
		{
			fPos[2] += 6.0f;
			fSpeed[2] = 3.0f;
			fQuaternion[2] = 180.0f;
		}
		else if (state == 2)
		{
			fPos[2] += 4.0f;
			fPos[1] += -7.5f;
			fSpeed[1] = -3.0f;
			fQuaternion[0] = -100.0f;
		}

		stUnoccupiedData vehSync;
		memset(&vehSync, 0, sizeof(stUnoccupiedData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		vehSync.fHealth = vinfo->hitpoints;
		vehSync.fMoveSpeed[0] = fSpeed[0];
		vehSync.fMoveSpeed[1] = fSpeed[1];
		vehSync.fMoveSpeed[2] = fSpeed[2];
		vehSync.fRoll[0] = cosf(fQuaternion[0]);

		pFunc->cheat_vehicle_teleport(vinfo, fPos);
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		if (state == 0)
		{
			vinfo->base.matrix[0] = sinf(fQuaternion[0]);
			vinfo->base.matrix[1] = sinf(fQuaternion[0]);

			state = 1;
		}
		else if (state == 1)
		{
			state = 2;
		}
		else if (state == 2)
		{
			vinfo->base.matrix[2] = cosf(fQuaternion[0]);
			vinfo->base.matrix[3] = cosf(fQuaternion[0]);

			state = 0;
		}

		vinfo->base.matrix[4] = fQuaternion[0];
		vinfo->base.matrix[5] = fQuaternion[1];
		vinfo->base.matrix[6] = fQuaternion[2];


		x--;
		if (x < -1) x = 0;

		v++;
		timer_ = GetTickCount();
	}

find_another_car:
	for (v; v < SAMP_MAX_VEHICLES; v++)
	{
		if (SF->getSAMP()->getVehicles()->iIsListed[v] == 1)
			break;
	}

	if (v >= SAMP_MAX_VEHICLES)
		v = 0;
}

void CState_::SendBulletPlayer(uint32_t i) {
	static DWORD timer = 0;
	if (GetTickCount() - timer > 100) {
		stRemotePlayer *pPlayer = SF->getSAMP()->getPlayers()->pRemotePlayer[i];
		if (!pPlayer) return;
		if (!i<= -1 || !i >= 1000) return;
		stBulletData sync;
		ZeroMemory(&sync, sizeof(stBulletData));

		sync.sTargetID = i;

		sync.fOrigin[0] = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3];
		sync.fOrigin[1] = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 1];
		sync.fOrigin[2] = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 2];

		sync.fTarget[0] = SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3];
		sync.fTarget[1] = SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 1];
		sync.fTarget[2] = SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 2];

		sync.fCenter[0] = 0.0;
		sync.fCenter[1] = 0.0;
		sync.fCenter[2] = 0.5;

		sync.byteWeaponID = SF->getSAMP()->getPlayers()->pLocalPlayer->byteCurrentWeapon;

		sync.byteType = 1;

		BitStream BulletSync;
		BulletSync.Write((BYTE)PacketEnumeration::ID_BULLET_SYNC);
		BulletSync.Write((PCHAR)&sync, sizeof(stBulletData));
		SF->getRakNet()->SendPacket(&BulletSync);
		timer = GetTickCount();
	}
}

void CState_::SpeedHack(void){
	//SF->getSAMP()->getMisc()->iCursorMode
	if (SF->getGame()->isKeyDown(0xA4)) {
		if (*(DWORD*)0xBA18FC) {
			struct actor_info *self = SF->getGame()->actorInfoGet(-1, ACTOR_ALIVE);
			CVector speed;
			PEDSELF->GetVehicle()->GetMoveSpeed(&speed);
			speed.fX += sinf(-self->fCurrentRotation) * 0.01;
			speed.fY += cosf(-self->fCurrentRotation) * 0.01;
			PEDSELF->GetVehicle()->SetMoveSpeed(&speed);
		}
	}
}

void CState_::CarFly(void) { //бай адский дрочила
	if (*(DWORD*)0xBA18FC == 0)
		return;
	if (SF->getGame()->vehicleInfoGet(VEHICLE_SELF, VEHICLE_ALIVE) == NULL) return;
	struct actor_info *self = SF->getGame()->actorInfoGet(-1, ACTOR_ALIVE);
	struct vehicle_info *info = SF->getGame()->vehicleInfoGet(-1, 0);
	if (info != NULL)
	{
		self->fCurrentRotation = -GAME->GetCamera()->GetCameraRotation();
		PEDSELF->GetVehicle()->SetOrientation(0, 0, self->fCurrentRotation);
		self->fTargetRotation = self->fCurrentRotation;
		info->base.matrix[4] = sinf(-self->fCurrentRotation);
		info->base.matrix[5] = cosf(-self->fCurrentRotation);

		if (SF->getGame()->isKeyDown('S') && SF->getGame()->isKeyDown('D')) {
			info->speed[0] = sinf(-self->fCurrentRotation - PI / 4) * -1.3;
			info->speed[1] = cosf(-self->fCurrentRotation - PI / 4) * -1.3;
		}
		else
			if (SF->getGame()->isKeyDown('S') && SF->getGame()->isKeyDown('A')) {
				info->speed[0] = sinf(-self->fCurrentRotation + PI / 4) * -1.3;
				info->speed[1] = cosf(-self->fCurrentRotation + PI / 4) * -1.3;
			}
			else
				if (SF->getGame()->isKeyDown('W') && SF->getGame()->isKeyDown('D')) {//invert 
					info->speed[0] = -sinf(-self->fCurrentRotation + PI / 4) * -1.3;
					info->speed[1] = -cosf(-self->fCurrentRotation + PI / 4) * -1.3;
				}
				else
					if (SF->getGame()->isKeyDown('W') && SF->getGame()->isKeyDown('A')) {//invert 
						info->speed[0] = -sinf(-self->fCurrentRotation - PI / 4) * -1.3;
						info->speed[1] = -cosf(-self->fCurrentRotation - PI / 4) * -1.3;
					}
					else {
						if (SF->getGame()->isKeyDown('W')) //вперед 
						{
							info->speed[0] = sinf(-self->fCurrentRotation) * 1.5; // 0.8 - velocity 
							info->speed[1] = cosf(-self->fCurrentRotation) * 1.5;
						}
						if (SF->getGame()->isKeyDown('S')) //назад 
						{
							info->speed[0] = sinf(-self->fCurrentRotation) * -1.3;//-0.5 
							info->speed[1] = cosf(-self->fCurrentRotation) * -1.3;
						}
						if (SF->getGame()->isKeyDown('A')) {//влево 
							info->speed[0] = sinf(-self->fCurrentRotation + 1.570796f) * -1.3;
							info->speed[1] = cosf(-self->fCurrentRotation + 1.570796f) * -1.3;
						}
						if (SF->getGame()->isKeyDown('D')) {//вправо 
							info->speed[0] = sinf(-self->fCurrentRotation - 1.570796f) * -1.3;//-0.5 
							info->speed[1] = cosf(-self->fCurrentRotation - 1.570796f) * -1.3;
						}
					}
		if (SF->getGame()->isKeyDown(0x20)) //пробел - вверх 
		{
			info->speed[2] += 0.05;
		}
		if (SF->getGame()->isKeyDown('C')) // C - зависнуть 
		{
			info->speed[0] = 0;
			info->speed[1] = 0;
			info->speed[2] = 0;
		}
		if (SF->getGame()->isKeyDown(0xA0)) // LShift - вниз 
		{
			info->speed[2] -= 0.05;
		}
	}
}

bool CState_::SuperCollisionPatch(bool cols) { //бай адский дрочила
	if (cols) {
		pFunc->Write((void*)(SF->getSAMP()->getSAMPAddr() + 0x3470), (BYTE*)"\xE9\x56\x01\x00\x00\x90", 6);
		return true;
	}
	else {
		pFunc->Write((void*)(SF->getSAMP()->getSAMPAddr() + 0x3470), (BYTE*)"\x0F\x84\x55\x01\x00\x00", 6);
		return false;
	}
}


void pFunc_::changeServer(const char *pszIp, unsigned ulPort)
{
	((void(__cdecl *)(unsigned))(SF->getSAMP()->getSAMPAddr() + 0x1BC20))(ulPort);

	SF->getSAMP()->disconnect(500);
	strcpy(SF->getSAMP()->getInfo()->szIP, pszIp);
	SF->getSAMP()->getInfo()->ulPort = ulPort;
}

void pFunc_::DisembarkInstantly()
{
	CTaskManager *taskManager = PEDSELF->GetPedIntelligence()->GetTaskManager();
	for (int i = 0; i < TASK_PRIORITY_MAX; i++)
	{
		CTask * pTask = taskManager->GetTask(i);
		if (pTask)
		{
			pTask->MakeAbortable(PEDSELF, ABORT_PRIORITY_IMMEDIATE, NULL);
			taskManager->RemoveTask(i);
		}
	}
	for (int i = 0; i < TASK_SECONDARY_MAX; i++)
	{
		CTask * pTask = taskManager->GetTaskSecondary(i);
		if (pTask)
		{
			pTask->MakeAbortable(PEDSELF, ABORT_PRIORITY_IMMEDIATE, NULL);
			if (i != TASK_SECONDARY_FACIAL_COMPLEX)
				taskManager->RemoveTaskSecondary(i);
		}
	}
}

void pFunc_::RemovePed(CPed* ped) {
	((void(__cdecl *)(CPed*))0x610F20)(ped);
}

void pFunc_::cfgFile(void) {
	char buf[64];
	/*Onfoot*/
	GetPrivateProfileString("ONFOOT", "AntiAfk", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->AntiAFK = atoi(buf);
	GetPrivateProfileString("ONFOOT", "GodMode", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->GodMode = atoi(buf);
	GetPrivateProfileString("ONFOOT", "ExtraWS", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->ExtraWS = atoi(buf);
	GetPrivateProfileString("ONFOOT", "NoSpread", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->NoSpread = atoi(buf);
	GetPrivateProfileString("ONFOOT", "NoReload", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->NoReload = atoi(buf);
	GetPrivateProfileString("ONFOOT", "GhostMode", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->GhostMode = atoi(buf);
	GetPrivateProfileString("ONFOOT", "QuickTurn", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->QuickTurn = atoi(buf);
	GetPrivateProfileString("ONFOOT", "nocolPeds", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	Collision->_nocolPeds = atoi(buf);
	/*MISC*/
	GetPrivateProfileString("MISC", "LogRPC", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->LogRPC = atoi(buf);
	GetPrivateProfileString("MISC", "Crosspiece", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->Crosspiece = atoi(buf);
	GetPrivateProfileString("MISC", "GpciSpoofer", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->GpciSpoofer = atoi(buf);
	GetPrivateProfileString("MISC", "nocolObjects", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	Collision->_nocolObjects = atoi(buf);
	GetPrivateProfileString("MISC", "nocolBuildings", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	Collision->_nocolBuildings = atoi(buf);
	GetPrivateProfileString("MISC", "FakePos", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->FakePos = atoi(buf);
	GetPrivateProfileString("MISC", "nocolCamBuildings", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	Collision->_nocolCamBuildings = atoi(buf);
	GetPrivateProfileString("MISC", "nocolCamVehicle", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	Collision->_nocolCamVehicle = atoi(buf);
	GetPrivateProfileString("MISC", "nocolCamObject", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	Collision->_nocolCamObject = atoi(buf);
	/*incar*/
	GetPrivateProfileString("INCAR", "CarFly", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->CarFly = atoi(buf);
	GetPrivateProfileString("INCAR", "AutoMending", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->AutoMending = atoi(buf);
	GetPrivateProfileString("INCAR", "nocolVehicles", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	Collision->_nocolVehicles = atoi(buf);
	/*jabroniProtect*/
	GetPrivateProfileString("jabroniProtect", "onfoot", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->onfoot = atoi(buf);
	GetPrivateProfileString("jabroniProtect", "incar", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->incar = atoi(buf);
	GetPrivateProfileString("jabroniProtect", "unoccupied", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->unoccupied = atoi(buf);
	GetPrivateProfileString("jabroniProtect", "bullet", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->bullet = atoi(buf);
	GetPrivateProfileString("jabroniProtect", "aim", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->aim = atoi(buf);
	GetPrivateProfileString("jabroniProtect", "passenger", "0", buf, 64, "./SAMPFUNCS/Bondage/settings.ini");
	ImGuiWindow->passenger = atoi(buf);
};


void pFunc_::GetPlayerPosition(uint32_t playerId,VECTOR &pos) {
	if (playerId == SF->getSAMP()->getPlayers()->sLocalPlayerID) {
		pos.X = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3];
		pos.Y = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 1];
		pos.Z = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 2];
	}
	else {
		if (SF->getSAMP()->getPlayers()->IsPlayerDefined(playerId, true)) {
			pos.X = SF->getSAMP()->getPlayers()->pRemotePlayer[playerId]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3];
			pos.Y = SF->getSAMP()->getPlayers()->pRemotePlayer[playerId]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 1];
			pos.Z = SF->getSAMP()->getPlayers()->pRemotePlayer[playerId]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 2];
		}
	}
}

void CState_::SilentCarshot(void) {
	static DWORD timer = 0;
	if(GetTickCount() - timer > 100 ){
		if (SF->getGame()->isKeyDown(0x01) && *(DWORD*)0xBA18FC) {
			stInCarData data;
			memset(&data, 0, sizeof(stInCarData));

			data = SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData;

			data.fMoveSpeed[0] = pFunc->cam_matrix[4] * 3;
			data.fMoveSpeed[1] = pFunc->cam_matrix[5] * 3;
			data.fMoveSpeed[2] = pFunc->cam_matrix[6] * 3;

			BitStream bsActorSync;
			bsActorSync.Write((BYTE)ID_VEHICLE_SYNC);
			bsActorSync.Write((PCHAR)&data, sizeof(stInCarData));
			SF->getRakNet()->SendPacket(&bsActorSync);
			timer = GetTickCount();
		}
	}
}

void CState_::spinner(void) {
	static DWORD timer = 0;
	if (GetTickCount() - timer > 100 && *(DWORD*)0xBA18FC) {
		stInCarData data;
		memset(&data, 0, sizeof(stInCarData));
		memcpy(&data, &SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData, sizeof(stInCarData));

		VECTOR playerPos;
		pFunc->GetPlayerPosition(ImGuiWindow->InputSpinnerPlayerId, playerPos);

		data.fPosition[0] = playerPos.X;
		data.fPosition[1] = playerPos.Y;
		data.fPosition[2] = playerPos.Z - 1;

		data.fQuaternion[1] = pFunc->RandomFloat(-1,1);
		data.fQuaternion[3] = pFunc->RandomFloat(-1, 1);
		data.fQuaternion[0] = pFunc->RandomFloat(-1, 1);

		BitStream bsIncarSync;
		bsIncarSync.Write((BYTE)ID_VEHICLE_SYNC);
		bsIncarSync.Write((PCHAR)&data, sizeof(stInCarData));
		SF->getRakNet()->SendPacket(&bsIncarSync);
		timer = GetTickCount();
	}
}

void CState_::SuperMan(void) {
	static DWORD timer = 0;
	if (GetTickCount() - timer > 100 && *(DWORD*)0xBA18FC) {
		stInCarData data;
		memset(&data, 0, sizeof(stInCarData));
		memcpy(&data, &SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData, sizeof(stInCarData));

		VECTOR playerPos;
		pFunc->GetPlayerPosition(4, playerPos);

		data.fPosition[0] = playerPos.X;
		data.fPosition[1] = playerPos.Y;
		data.fPosition[2] = playerPos.Z - 1;

		data.fMoveSpeed[2] = pFunc->RandomFloat(-0.2, 0.2);

		data.fQuaternion[1] = pFunc->RandomFloat(-1, 1);
		data.fQuaternion[3] = pFunc->RandomFloat(-1, 1);
		data.fQuaternion[0] = pFunc->RandomFloat(-1, 1);

		BitStream bsIncarSync;
		bsIncarSync.Write((BYTE)ID_VEHICLE_SYNC);
		bsIncarSync.Write((PCHAR)&data, sizeof(stInCarData));
		SF->getRakNet()->SendPacket(&bsIncarSync);
		timer = GetTickCount();
	}
}

void CState_::sentChatMessage(char *text, uint16_t sleep) {
	static DWORD time = 0;
	if (GetTickCount() - time > sleep) {
		SF->getSAMP()->getPlayers()->pLocalPlayer->Say(text);
		time = GetTickCount();
	}
}
