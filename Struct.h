#pragma once
#include "main.h"

class ImGuiWindow_ {
public:
	bool ImGuiDrawMenu{ false };
	bool activew{ true };
	//window
	bool OnfootWindow{ false };
	bool IncarWindow{ false };
	bool MiscWindow{ false };
	bool NopSampWindow{ false };
	bool ProtectWindow{ false };
	bool GtaPatchWindow{ false };
	bool OnfootMiscWindow{ false };
	bool SettingsWindow{ false };
	char *text;
	//onfoot 
	bool AntiAFK{ false };
	bool GodMode{ false };
	bool ExtraWS{ false };
	bool GlassesLagger{ false };
	bool Invize{ false };
	bool SetGameSpeed{ false };
	bool SetGravity{ false };
	bool AimZ{ false };
	bool DerpCam{ false };
	bool OnfootRvanka{ false };
	bool AirBreak{ false };
	bool RapidFire{ false };
	bool NoSpread{ false };
	bool Pylsator{ false };
	bool NoReload{ false };
	bool GhostMode{ false };
	bool Damager{ false };
	bool QuickTurn{ false };
	bool SubstitutionWeapon{ false };
	//misc
	bool LogRPC{ false };
	bool Crosspiece{ false };
	bool Sensfix{ false };
	bool GpciSpoofer{ true };
	bool GotoMark{ false };
	bool RollCrasher{ false };
	bool FakePos{ false };
	bool SyncLogger{ false };
	bool SyncLoggerOnfoot{ false };
	bool SyncLoggerIncar{ false };
	bool SyncLoggerBullet{ false };
	bool SyncLoggerAim{ false };
	bool SyncLoggerPassenger{ false };
	bool SyncLoggerUnoccupied{ false };
	bool ChatFlooder{ false };
	//incar
	bool CarDamager{ false };
	bool CarWall{ false };
	bool CarShoter{ false };
	bool SpeedHack{ false };
	bool CarFly{ false };
	bool AutoMending{ false };
	bool DriftController{ false };
	bool FuckCar{ false };
	bool TransferOfControlVehicle{ false };
	bool SilentCarshot{ false };
	bool SpinnerSlapper{ false };
	//jabroniProtect
	bool onfoot{ true };
	bool incar{ true };
	bool unoccupied{ true };
	bool bullet{ true };
	bool aim{ true };
	bool passenger{ true };
	//settins
	float gamespeed = 5.0f;
	float heightmegaJump = 25.0f;
	int ChatFlooderSpeed = 300;
	char ChatFlooderText[255];
	bool AntiHook{ true };
	//Input
	int InputDamagerPlayerId = 0;
	int InputDgunWeaponId = 0;
	int InputDgunAmmo = 0;
	int InputSkinId = 0;
	int InputRemovePlayerId = 0;
	int SubstitutionWeaponId = 0;
	int inputSyncAllLoggerPlayerId = 0;
	int InputTransferOfControlVehicleId = 0;
	int InputSpinnerPlayerId = 0;
	char SyncAllLoggerPlayer[355] = "Никакой синхры не было получено";
};

class CState_{
public:
	char *LoggerOutcomingRPC;
	char *LoggerIncomingRPC;
	///////
	bool GMPatch(bool gm);
	bool AFKPatch(bool afk);
	bool ExtraWSPatch(bool extra);
	bool RapidFirePatch(bool rapid);
	bool NoSpreadPatch(bool spread);
	bool SuperCollisionPatch(bool cols);
	void carDamager();
	void GlassesLagger();
	void Invize();
	void GpciSpoofer(void);
	void OnfootRvanka(void);
	void TeleportMetkaMap(void);
	void AirBreak(void);
	void Pylsator(void);
	void NoReload(void);
	void carShooter(void);
	void carWall(void);
	void SendBulletPlayer(uint32_t i);
	void SpeedHack(void);
	void CarFly(void);
	void SilentCarshot(void);
	void spinner(void);
	void SuperMan(void);
	void sentChatMessage(char *text, uint16_t sleep);
};

class BlockRPC_ {
public:
	bool RPC_ScrSetPlayerName = false; //1
	bool RPC_ScrSetPlayerPos = false; //2
	bool RPC_ScrSetPlayerPosFindZ = false; //3
	bool RPC_ScrSetPlayerHealth = false;//4
	bool RPC_ScrTogglePlayerControllable = false; //5
	bool RPC_ScrPlaySound = false;//6
	bool RPC_ScrGivePlayerMoney = false;//7
	bool RPC_ScrSetPlayerFacingAngle = false;//8
	bool RPC_ScrResetPlayerWeapons = false;//9
	bool RPC_ScrGivePlayerWeapon = false;//10
	bool RPC_ScrSetVehicleParamsEx = false;//11
	bool RPC_ScrSetPlayerTime = false;//12
	bool RPC_ScrToggleClock = false;//13
	bool RPC_ScrSetPlayerDrunkLevel = false;//14
	bool RPC_ScrCreate3DTextLabel = false;//15
	bool RPC_ScrDisableCheckpoint = false;//16
	bool RPC_ScrSetRaceCheckpoint = false;//17
	bool RPC_ScrPlayAudioStream = false;//18
	bool RPC_ScrStopAudioStream = false;//19
	bool RPC_ScrRemoveBuildingForPlayer = false;//20
	bool RPC_ScrCreateObject = false;//21
	bool RPC_ScrSetObjectPos = false;//22
	bool RPC_ScrSetObjectRot = false;//23
	bool RPC_ScrDestroyObject = false;//24
	bool RPC_ScrDeathMessage = false;//25
	bool RPC_ScrSetPlayerMapIcon = false;//26
	bool RPC_ScrRemoveVehicleComponent = false;//27
	bool RPC_ScrUpdate3DTextLabel = false;//28
	bool RPC_ScrChatBubble = false;//29
	bool RPC_ScrShowDialog = false;//30
	bool RPC_ScrDestroyPickup = false;//31
	bool RPC_ScrSetPlayerArmour = false;//32
	bool RPC_ScrSetSpawnInfo = false;//33
	bool RPC_ScrRemovePlayerFromVehicle = false;//34
	bool RPC_ScrSetPlayerColor = false;//35
	bool RPC_ScrDisplayGameText = false;//36
	bool RPC_ScrForceClassSelection = false;//37
	bool RPC_ScrAttachObjectToPlayer = false;//38
	bool RPC_ScrCreateExplosion = false;//39
	bool RPC_ScrShowPlayerNameTagForPlayer = false;//40
	bool RPC_ScrAttachCameraToObject = false;//41
	bool RPC_ScrInterpolateCamera = false;//42
	bool RPC_ScrSetObjectMaterial = false;//43
	bool RPC_ScrGangZoneStopFlash = false;//44
	bool RPC_ScrApplyAnimation = false;//45
	bool RPC_ScrClearAnimations = false;//46
	bool RPC_ScrSetPlayerSpecialAction = false;//47
	bool RPC_ScrSetPlayerFightingStyle = false;//48
	bool RPC_ScrSetPlayerVelocity = false;//49
	bool RPC_ScrSetVehicleVelocity = false;//50
	bool RPC_ScrClientMessage = false;//51
	bool RPC_ScrSetWorldTime = false;//52
	bool RPC_ScrCreatePickup = false;//53
	bool RPC_ScrSetCheckpoint = false;//54
	bool RPC_ScrSetPlayerAttachedObject = false;//55
	bool RPC_ScrStopObject = false;//56
	bool RPC_ScrShowTextDraw = false;//57
	bool RPC_ScrTextDrawHideForPlayer = false;//58
	bool RPC_ScrServerJoin = false;//59
	bool RPC_ScrServerQuit = false;//60
	bool RPC_ScrSetPlayerAmmo = false;//61
	bool RPC_ScrSetGravity = false;//62
	bool RPC_ScrSetVehicleHealth = false;//63
	bool RPC_ScrSetWeather = false;//64
	bool RPC_ScrSetPlayerSkin = false;//65
	bool RPC_ScrSetPlayerInterior = false;//66
	bool RPC_ScrSetPlayerCameraPos = false;//67
	bool RPC_ScrSetPlayerCameraLookAt = false;//68
	bool RPC_ScrSetVehiclePos = false;//69
	bool RPC_ScrSetVehicleZAngle = false;//70
};

struct ExampleAppLog_
{
	ImGuiTextBuffer Buf;
	ImGuiTextFilter Filter;
	ImVector<int> LineOffsets; // Index to lines offset
	bool ScrollToBottom;

	void Clear() { Buf.clear(); LineOffsets.clear(); }

	void AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendfv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size);
		ScrollToBottom = true;
	}

	void Draw(const char* title, bool* p_open = NULL)
	{
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin(title, NULL, ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::End();
			return;
		}
		if (ImGui::Button(u8"Очистить")) Clear();
		ImGui::SameLine();
		bool copy = ImGui::Button(u8"Скопировать");
		ImGui::SameLine();
		Filter.Draw(u8"Фильтр", -100.0f);
		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
		if (copy) ImGui::LogToClipboard();

		if (Filter.IsActive())
		{
			const char* buf_begin = Buf.begin();
			const char* line = buf_begin;
			for (int line_no = 0; line != NULL; line_no++)
			{
				const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
				if (Filter.PassFilter(line, line_end))
					ImGui::TextUnformatted(line, line_end);
				line = line_end && line_end[1] ? line_end + 1 : NULL;
			}
		}
		else
		{
			ImGui::TextUnformatted(Buf.begin());
		}

		if (ScrollToBottom)
			ImGui::SetScrollHere(1.0f);
		ScrollToBottom = false;
		ImGui::EndChild();
		ImGui::End();
	}
};

class LogFunc_ {
public:
	void ShowExampleAppLog_(bool* opened);
	bool show_app_log_ = true;
	ExampleAppLog_ log_;
	bool log_enabled = false;
};

class Collision_
{
public:
	bool _enabled = true, _inited = false;
	bool _nocolVehicles = true, _nocolPeds = true, _nocolObjects = false, _nocolBuildings = false;
	bool _nocolCamBuildings = false, _nocolCamVehicle = false, _nocolCamObject = false;;
};

struct pool
{
#pragma pack( 1 )
	void *start; /* pointer to start of pool */
	void *__end; /* end of this structure? (not the pool) */
	int32_t size; /* max number of items in the pool */
	/* there's some more junk after this */
};

class pFunc_{
public:
	float *cam_matrix = (float *)0xB6F99C;
	void vect3_copy(const float in[3], float out[3]);
	float RandomFloat(float a, float b);
	void Write(void *addr, void *bytes, size_t byteSize);
	void NOP(void *addr, size_t bytes);
	void cheat_vehicle_teleport(struct vehicle_info *info, const float pos[3], int interior_id, bool keepSpeed);
	void vehicle_detachables_teleport(struct vehicle_info *info, const float from[3], const float to[3]);
	void vect3_zero(float out[3]);
	void vect3_vect3_add(const float in1[3], const float in2[3], float out[3]);
	void vect3_vect3_sub(const float in1[3], const float in2[3], float out[3]);
	int getSAMPVehicleIDFromGTAVehicle(struct vehicle_info *pVehicle);
	void changeServer(const char *pszIp, unsigned ulPort);
	void cfgFile(void);
	void DisembarkInstantly(void);
	void RemovePed(CPed* ped);
	void GetPlayerPosition(uint32_t playerId,VECTOR &pos);

};
extern pool *pool_vehicle;
extern pFunc_ *pFunc;
extern Collision_ *Collision;
extern ExampleAppLog_ *ExampleAppLog;
extern LogFunc_ *LogFunc;
extern stFontInfo *pFont;
extern ImGuiWindow_ *ImGuiWindow;
extern CState_ *CState;
extern BlockRPC_ *BlockRPC;