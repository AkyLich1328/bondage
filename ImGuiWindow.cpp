#include "ImGuiWindow.h"

void TextQuestion(const char* params) {
	ImGui::TextDisabled("(!)");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450);
		ImGui::TextUnformatted(params);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void setHealthColor(unsigned int hpHigh, unsigned int hpLow) {
	pFunc->Write((void*)(GetModuleHandle("samp.dll") + 0x68B0C), (uint32_t*)hpHigh, 4);
	pFunc->Write((void*)(GetModuleHandle("samp.dll") + 0x68B33), (uint32_t*)hpLow, 4);
}

void CherryTheme() {

/*ImGuiStyle* style = &ImGui::GetStyle();
ImVec4* colors = style->Colors;

colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

style->ChildRounding = 4.0f;
style->FrameBorderSize = 1.0f;
style->FrameRounding = 2.0f;
style->GrabMinSize = 7.0f;
style->PopupRounding = 2.0f;
style->ScrollbarRounding = 12.0f;
style->ScrollbarSize = 13.0f;
style->TabBorderSize = 1.0f;
style->TabRounding = 0.0f;
style->WindowRounding = 4.0f;*/
	ImGuiStyle & style = ImGui::GetStyle();
	ImVec4 * colors = style.Colors;

	/// 0 = FLAT APPEARENCE
	/// 1 = MORE "3D" LOOK
	int is3D = 0;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
	colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
	colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

	style.PopupRounding = 3;

	style.WindowPadding = ImVec2(4, 4);
	style.FramePadding = ImVec2(6, 4);
	style.ItemSpacing = ImVec2(6, 2);

	style.ScrollbarSize = 18;

	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.FrameBorderSize = is3D;

	style.WindowRounding = 3;
	style.ChildRounding = 3;
	style.FrameRounding = 3;
	style.ScrollbarRounding = 2;
	style.GrabRounding = 3;

#ifdef IMGUI_HAS_DOCK 
	style.TabBorderSize = is3D;
	style.TabRounding = 3;

	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
#endif
}

void BackFunc() {
	ImGuiWindow->OnfootWindow = false;
	ImGuiWindow->IncarWindow = false;
	ImGuiWindow->NopSampWindow = false;
	ImGuiWindow->MiscWindow = false;
	ImGuiWindow->ProtectWindow = false;
	ImGuiWindow->GtaPatchWindow = false;
	ImGuiWindow->SettingsWindow = false;
	ImGuiWindow->OnfootMiscWindow = false;
	ImGuiWindow->OnfootWindow = false;

}

void CheckboxNopRPC(void) {
	ImGui::Checkbox("1.SetPlayerName", &BlockRPC->RPC_ScrSetPlayerName);
	ImGui::Checkbox("2.SetPlayerPos", &BlockRPC->RPC_ScrSetPlayerPos);
	ImGui::Checkbox("3.SetPlayerPosFindZ", &BlockRPC->RPC_ScrSetPlayerPosFindZ);
	ImGui::Checkbox("4.SetPlayerHealth", &BlockRPC->RPC_ScrSetPlayerHealth);
	ImGui::Checkbox("5.TogglePlayerControllable", &BlockRPC->RPC_ScrTogglePlayerControllable);
	ImGui::Checkbox("6.PlaySound", &BlockRPC->RPC_ScrPlaySound);
	ImGui::Checkbox("7.GivePlayerMoney", &BlockRPC->RPC_ScrGivePlayerMoney);
	ImGui::Checkbox("8.SetPlayerFacingAngle", &BlockRPC->RPC_ScrSetPlayerFacingAngle);
	ImGui::Checkbox("9.ResetPlayerWeapons", &BlockRPC->RPC_ScrResetPlayerWeapons);
	ImGui::Checkbox("10.GivePlayerWeapon", &BlockRPC->RPC_ScrGivePlayerWeapon);
	ImGui::Checkbox("11.SetVehicleParamsEx", &BlockRPC->RPC_ScrSetVehicleParamsEx);
	ImGui::Checkbox("12.SetPlayerTime", &BlockRPC->RPC_ScrSetPlayerTime);
	ImGui::Checkbox("13.ToggleClock", &BlockRPC->RPC_ScrToggleClock);
	ImGui::Checkbox("14.SetPlayerDrunkLevel", &BlockRPC->RPC_ScrSetPlayerDrunkLevel);
	ImGui::Checkbox("15.Create3DTextLabel", &BlockRPC->RPC_ScrCreate3DTextLabel);
	ImGui::Checkbox("16.DisableCheckpoint", &BlockRPC->RPC_ScrDisableCheckpoint);
	ImGui::Checkbox("17.SetRaceCheckpoint", &BlockRPC->RPC_ScrSetRaceCheckpoint);
	ImGui::Checkbox("18.PlayAudioStream", &BlockRPC->RPC_ScrPlayAudioStream);
	ImGui::Checkbox("19.StopAudioStream", &BlockRPC->RPC_ScrStopAudioStream);
	ImGui::Checkbox("20.RemoveBuildingForPlayer", &BlockRPC->RPC_ScrRemoveBuildingForPlayer);
	ImGui::Checkbox("21.CreateObject", &BlockRPC->RPC_ScrCreateObject);
	ImGui::Checkbox("22.SetObjectPos", &BlockRPC->RPC_ScrSetObjectPos);
	ImGui::Checkbox("23.SetObjectRot", &BlockRPC->RPC_ScrSetObjectRot);
	ImGui::Checkbox("24.DestroyObject", &BlockRPC->RPC_ScrDestroyObject);
	ImGui::Checkbox("25.DeathMessage", &BlockRPC->RPC_ScrDeathMessage);
	ImGui::Checkbox("26.SetPlayerMapIcon", &BlockRPC->RPC_ScrSetPlayerMapIcon);
	ImGui::Checkbox("27.RemoveVehicleComponent", &BlockRPC->RPC_ScrRemoveVehicleComponent);
	ImGui::Checkbox("28.Update3DTextLabel", &BlockRPC->RPC_ScrUpdate3DTextLabel);
	ImGui::Checkbox("29.ChatBubble", &BlockRPC->RPC_ScrChatBubble);
	ImGui::Checkbox("30.ShowDialog", &BlockRPC->RPC_ScrShowDialog);
	ImGui::Checkbox("31.DestroyPickup", &BlockRPC->RPC_ScrDestroyPickup);
	ImGui::Checkbox("32.SetPlayerArmour", &BlockRPC->RPC_ScrSetPlayerArmour);
	ImGui::Checkbox("33.SetSpawnInfo", &BlockRPC->RPC_ScrSetSpawnInfo);
	ImGui::Checkbox("34.RemovePlayerFromVehicle", &BlockRPC->RPC_ScrRemovePlayerFromVehicle);
	ImGui::Checkbox("35.SetPlayerColor", &BlockRPC->RPC_ScrSetPlayerColor);
	ImGui::Checkbox("36.DisplayGameText", &BlockRPC->RPC_ScrDisplayGameText);
	ImGui::Checkbox("37.ForceClassSelection", &BlockRPC->RPC_ScrForceClassSelection);
	ImGui::Checkbox("38.AttachObjectToPlayer", &BlockRPC->RPC_ScrAttachObjectToPlayer);
	ImGui::Checkbox("39.CreateExplosion", &BlockRPC->RPC_ScrCreateExplosion);
	ImGui::Checkbox("40.ShowPlayerNameTagForPlayer", &BlockRPC->RPC_ScrShowPlayerNameTagForPlayer);
	ImGui::Checkbox("41.AttachCameraToObject", &BlockRPC->RPC_ScrAttachCameraToObject);
	ImGui::Checkbox("42.InterpolateCamera", &BlockRPC->RPC_ScrInterpolateCamera);
	ImGui::Checkbox("43.SetObjectMaterial", &BlockRPC->RPC_ScrSetObjectMaterial);
	ImGui::Checkbox("44.GangZoneStopFlash", &BlockRPC->RPC_ScrGangZoneStopFlash);
	ImGui::Checkbox("45.ApplyAnimation", &BlockRPC->RPC_ScrApplyAnimation);
	ImGui::Checkbox("46.ClearAnimations", &BlockRPC->RPC_ScrClearAnimations);
	ImGui::Checkbox("47.SetPlayerSpecialAction", &BlockRPC->RPC_ScrSetPlayerSpecialAction);
	ImGui::Checkbox("48.SetPlayerFightingStyle", &BlockRPC->RPC_ScrSetPlayerFightingStyle);
	ImGui::Checkbox("49.SetPlayerVelocity", &BlockRPC->RPC_ScrSetPlayerVelocity);
	ImGui::Checkbox("50.SetVehicleVelocity", &BlockRPC->RPC_ScrSetVehicleVelocity);
	ImGui::Checkbox("51.ClientMessage", &BlockRPC->RPC_ScrClientMessage);
	ImGui::Checkbox("52.SetWorldTime", &BlockRPC->RPC_ScrSetWorldTime);
	ImGui::Checkbox("53.CreatePickup", &BlockRPC->RPC_ScrCreatePickup);
	ImGui::Checkbox("54.SetCheckpoint", &BlockRPC->RPC_ScrSetCheckpoint);
	ImGui::Checkbox("55.SetPlayerAttachedObject", &BlockRPC->RPC_ScrSetPlayerAttachedObject);
	ImGui::Checkbox("56.StopObject", &BlockRPC->RPC_ScrStopObject);
	ImGui::Checkbox("57.ShowTextDraw", &BlockRPC->RPC_ScrShowTextDraw);
	ImGui::Checkbox("58.TextDrawHideForPlayer", &BlockRPC->RPC_ScrTextDrawHideForPlayer);
	ImGui::Checkbox("59.ServerJoin", &BlockRPC->RPC_ScrServerJoin);
	ImGui::Checkbox("60.ServerQuit", &BlockRPC->RPC_ScrServerQuit);
	ImGui::Checkbox("61.SetPlayerAmmo", &BlockRPC->RPC_ScrSetPlayerAmmo);
	ImGui::Checkbox("62.SetGravity", &BlockRPC->RPC_ScrSetGravity);
	ImGui::Checkbox("63.SetVehicleHealth", &BlockRPC->RPC_ScrSetVehicleHealth);
	ImGui::Checkbox("64.SetWeather", &BlockRPC->RPC_ScrSetWeather);
	ImGui::Checkbox("65.SetPlayerSkin", &BlockRPC->RPC_ScrSetPlayerSkin);
	ImGui::Checkbox("66.SetPlayerInterior", &BlockRPC->RPC_ScrSetPlayerInterior);
	ImGui::Checkbox("67.SetPlayerCameraPos", &BlockRPC->RPC_ScrSetPlayerCameraPos);
	ImGui::Checkbox("68.SetPlayerCameraLookAt", &BlockRPC->RPC_ScrSetPlayerCameraLookAt);
	ImGui::Checkbox("69.SetVehiclePos", &BlockRPC->RPC_ScrSetVehiclePos);
	ImGui::Checkbox("70.SetVehicleZAngle", &BlockRPC->RPC_ScrSetVehicleZAngle);
}

struct IMGUITEXT {
	const char *language = "Language";
	const char *Onfoot; const char *Incar; const char *Misc; const char*GTAPatches;
	const char *SAMPNOP; const char *JabroniProtect; const char* Settings;
	struct IMGUITEXTONFOOT {
		const char *GodMode;
	}pTextOnfoot;
}pText;

void ImGuiDraw() {
	if (ImGuiWindow->activew)
	{
		static bool resize;
		ImGui::Begin(" < AnaL.Bo[N]DaGe.v3.0 >", &ImGuiWindow->activew, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize); {
			if (!resize) {
				CherryTheme();
				ImGuiWindow->text = "Main->"; 
				ImGui::SetWindowSize(" < AnaL.Bo[N]DaGe.v3.0 >", ImVec2(360, 325));
				ImGui::SetWindowPos(" < AnaL.Bo[N]DaGe.v3.0 >", ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 200, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_::ImGuiCond_FirstUseEver);
				resize = true;
			}
			ImGui::Text("%s", ImGuiWindow->text);
			ImGui::SameLine();
			ImGui::SetCursorPosX(235);
			ImGui::PushItemWidth(60);
			const char* items[] = { "ENG", "RUS" };
			static int item_current = 0;
			ImGui::Combo("", &item_current, items, IM_ARRAYSIZE(items));
			if (item_current == 0) {
				pText.language = "Language";
				pText.Onfoot = "<Onfoot>";
				pText.Incar = "<Incar>";
				pText.Misc = "<Misc>";
				pText.GTAPatches = "<GTA:Patches>";
				pText.SAMPNOP = "<SAMP:NOP>";
				pText.JabroniProtect = "<Jabroni:Protect>";
				pText.Settings = "<Settings>";

				pText.pTextOnfoot.GodMode = "GodMode";
			}
			else if (item_current == 1) {
				pText.language = u8"Язык";
				pText.Onfoot = u8"<Онфут>";
				pText.Incar = u8"<Инкар>";
				pText.Misc = u8"<Разное>";
				pText.GTAPatches = u8"<ГТА:Патчи>";
				pText.SAMPNOP = u8"<САМП:Ноп>";
				pText.JabroniProtect = u8"<Жаброни:Защита>";
				pText.Settings = u8"<Настройки>";

				pText.pTextOnfoot.GodMode = u8"Бессмертие";
			}
			ImGui::PopItemWidth();
			ImGui::SameLine();
			ImGui::SetCursorPosX(300);
			if (ImGui::Button("Back")) {
				BackFunc();	
			}
			ImGui::Separator();
				
			if (!ImGuiWindow->OnfootWindow && !ImGuiWindow->IncarWindow && !ImGuiWindow->NopSampWindow && !ImGuiWindow->MiscWindow && !ImGuiWindow->ProtectWindow && !ImGuiWindow->GtaPatchWindow && !ImGuiWindow->SettingsWindow && !ImGuiWindow->OnfootMiscWindow) {
				if (ImGui::Button(pText.Onfoot, ImVec2(350, 25))) {
					ImGuiWindow->text = "Main->Onfoot->";
					ImGuiWindow->OnfootWindow = true;
				}

				if (ImGui::Button(pText.Incar, ImVec2(350, 25))) {
					ImGuiWindow->text = "Main->Incar->";
					ImGuiWindow->IncarWindow = true;
				}

				if (ImGui::Button(pText.Misc, ImVec2(350, 25))) {
					ImGuiWindow->text = "Main->Misc->";
					ImGuiWindow->MiscWindow = true;
				}

				ImGui::Separator();

				if (ImGui::Button(pText.GTAPatches, ImVec2(350, 25))) {
					ImGuiWindow->text = "Main->GTA:Patches->";
					ImGuiWindow->GtaPatchWindow = true;
				}
				if (ImGui::Button(pText.SAMPNOP, ImVec2(350, 25))) {
					ImGuiWindow->text = "Main->SAMP:NOP->";
					ImGuiWindow->NopSampWindow = true;
				}

				if (ImGui::Button(pText.JabroniProtect, ImVec2(350, 25))) {
					ImGuiWindow->text = "Main->Jabroni:Protect->";
					ImGuiWindow->ProtectWindow = true;
				}

				if (ImGui::Button(pText.Settings, ImVec2(350, 25))) {
					ImGuiWindow->text = "Main->Settings->";
					ImGuiWindow->SettingsWindow = true;
				}

			}
			if (ImGuiWindow->OnfootWindow) {
				if (ImGui::Button("<Onfoot:Misc>", ImVec2(350, 25))) {
					ImGuiWindow->text = "Main->Onfoot:Misc";
					ImGuiWindow->OnfootWindow = false;
					ImGuiWindow->OnfootMiscWindow = true;
				}

				if (ImGui::Checkbox(pText.pTextOnfoot.GodMode, &ImGuiWindow->GodMode)) {
					if (ImGuiWindow->GodMode) {
						CState->GMPatch(true);
					}
					else {
						CState->GMPatch(false);
					}
				}

				if (ImGui::Checkbox("ExtraWSP", &ImGuiWindow->ExtraWS)) {
					if (ImGuiWindow->ExtraWS) {
						CState->ExtraWSPatch(true);
					}
					else {
						CState->ExtraWSPatch(false);
					}
				}

				ImGui::SameLine();
				TextQuestion(u8"Блокировка востановления камеры на стандартную позицию");

				if (ImGui::Checkbox("AntiAFK", &ImGuiWindow->AntiAFK)) {
					if (ImGuiWindow->AntiAFK) {
						CState->AFKPatch(true);
					}
					else {
						CState->AFKPatch(false);
					}
				}

				ImGui::SameLine();
				TextQuestion(u8"Что бы анти афк работал нужно свернуть игру(через alt+tab)");

				ImGui::Checkbox("GlassesLagger", &ImGuiWindow->GlassesLagger);

				ImGui::Checkbox("OnfootRvanka", &ImGuiWindow->OnfootRvanka);

				ImGui::Checkbox("AirBreak", &ImGuiWindow->AirBreak);

				ImGui::Checkbox("Invize", &ImGuiWindow->Invize);

				ImGui::Checkbox("SetGameSpeed", &ImGuiWindow->SetGameSpeed);

				if (ImGui::Checkbox("FuckGta", &ImGuiWindow->SetGravity)) {
					if (ImGuiWindow->SetGravity) {
						*reinterpret_cast <float*>(0x863984) = 900.0f;
					}
					else {
						*reinterpret_cast <float*>(0x863984) = 0.008f;
					}
				}

				ImGui::Checkbox("AimZ", &ImGuiWindow->AimZ);

				ImGui::Checkbox("DerpCam", &ImGuiWindow->DerpCam);

				if (ImGui::Checkbox("RapidFire", &ImGuiWindow->RapidFire)) {
					if (ImGuiWindow->RapidFire) {
						CState->RapidFirePatch(true);
					}
					else {
						CState->RapidFirePatch(false);
					}
				}

				if (ImGui::Checkbox("NoSpread", &ImGuiWindow->NoSpread)) {
					if (ImGuiWindow->NoSpread) {
						CState->NoSpreadPatch(true);
					}
					else {
						CState->NoSpreadPatch(false);
					}
				}

				ImGui::Checkbox("Pylsator", &ImGuiWindow->Pylsator);

				ImGui::Checkbox("NoReload", &ImGuiWindow->NoReload);

				ImGui::Checkbox("GhostMode", &ImGuiWindow->GhostMode);

				if (ImGui::Checkbox("QuickTurn", &ImGuiWindow->QuickTurn)) {
					if (ImGuiWindow->QuickTurn) *(float*)(*(DWORD*)0xB6F5F0 + 0x560) = 100;
					else *(float*)(*(DWORD*)0xB6F5F0 + 0x560) = 7.5;
				}

				if (ImGui::CollapsingHeader("Damager")) {
					ImGui::InputInt("playerId", &ImGuiWindow->InputDamagerPlayerId);
					ImGui::Checkbox("SendBullet", &ImGuiWindow->Damager);
					ImGui::Separator();
				}

				if (ImGui::CollapsingHeader("Dgun")) {
					ImGui::InputInt("weaponId", &ImGuiWindow->InputDgunWeaponId);
					ImGui::InputInt("Ammo", &ImGuiWindow->InputDgunAmmo);
					if (ImGui::Button("Give weapon")) {
						if (ImGuiWindow->InputDgunWeaponId >= 0 || ImGuiWindow->InputDgunWeaponId <= 46) {
							BitStream bsClass;
							bsClass.Write(uint32_t(ImGuiWindow->InputDgunWeaponId)); // WeaponID
							bsClass.Write(uint32_t(ImGuiWindow->InputDgunAmmo)); // Ammo
							SF->getRakNet()->emulateRecvRPC(22, &bsClass);
						}
					}
					if (ImGui::CollapsingHeader("Weapon")) {
						ImGui::Text(
							"0 - Fist\n"
							"1 - Brass knuckles\n"
							"2 - Golf club\n"
							"3 - Nitestick\n"
							"4 - Knife\n"
							"5 - Bat\n"
							"6 - Shovel\n"
							"7 - Pool cue\n"
							"8 - Katana\n"
							"9 - Chainsaw\n"
							"10 - Dildo\n"
							"11 - Dildo2\n"
							"12 - Vibrator\n"
							"13 - Vibrator 2\n"
							"14 - Flowers\n"
							"15 - Cane\n"
							"16 - Grenade\n"
							"17 - Teargas\n"
							"18 - Molotov\n"
							"19 - Vehicle M4(custom)\n"
							"20 - Vehicle minigun(custom)\n"
							"22 - Colt 45\n"
							"23 - Silenced\n"
							"24 - Deagle\n"
							"25 - Shotgun\n"
							"26 - Sawed - off\n"
							"27 - Spas\n"
							"28 - UZI\n"
							"29 - MP5\n"
							"30 - AK47\n"
							"31 - M4\n"
							"32 - Tec9\n"
							"33 - Cuntgun\n"
							"34 - Sniper\n"
							"35 - Rocket launcher\n"
							"36 - Heatseeker\n"
							"37 - Flamethrower\n"
							"38 - Minigun\n"
						);
					}
					ImGui::Separator();
				}

				if (ImGui::CollapsingHeader("SetVisualSkin")) {
					ImGui::InputInt("skinId", &ImGuiWindow->InputSkinId);
					if (ImGui::Button("SetSkin")) {
						if (ImGuiWindow->InputSkinId >= 0 || ImGuiWindow->InputSkinId <= 311) {
							BitStream bsClass;
							bsClass.Write(uint32_t(SF->getSAMP()->getPlayers()->sLocalPlayerID));
							bsClass.Write(uint32_t(ImGuiWindow->InputSkinId));
							SF->getRakNet()->emulateRecvRPC(153, &bsClass);
						}
					}
					ImGui::Separator();
				}

				if (ImGui::CollapsingHeader("SubstitutionWeapon")) {
					ImGui::InputInt("weaponId", &ImGuiWindow->SubstitutionWeaponId);
					ImGui::Checkbox("Substitution", &ImGuiWindow->SubstitutionWeapon);
				}

			}

			if (ImGuiWindow->OnfootMiscWindow) {
				if (ImGui::Button("Full hp", ImVec2(120, 25)))
					*(float*)(*(DWORD*)0xB6F5F0 + 0x540) = 100;

				if (ImGui::Button("Full armour", ImVec2(120, 25)))
					*(float*)(*(DWORD*)0xB6F5F0 + 0x548) = 100;

				if (ImGui::Button("Suicide", ImVec2(120, 25)))
					*(float*)(*(DWORD*)0xB6F5F0 + 0x540) = 0;
			}

			if (ImGuiWindow->IncarWindow) {
				if (ImGui::Button("FixCar", ImVec2(120, 25))) {
					CVehicle *veh = PEDSELF->GetVehicle();
					if (!veh) return;
					veh->Fix();
					veh->SetHealth(1000.0f);
				}
				ImGui::Checkbox("CarDamager", &ImGuiWindow->CarDamager);

				ImGui::Checkbox("CarShoter", &ImGuiWindow->CarShoter);

				ImGui::Checkbox("CarWall", &ImGuiWindow->CarWall);

				ImGui::Checkbox("SpeedHack", &ImGuiWindow->SpeedHack);

				ImGui::Checkbox("CarFly", &ImGuiWindow->CarFly);

				ImGui::Checkbox("AutoMending", &ImGuiWindow->AutoMending);

				ImGui::Checkbox("DriftController", &ImGuiWindow->DriftController);

				ImGui::Checkbox("FuckCar", &ImGuiWindow->FuckCar);

				ImGui::Checkbox("SilentCarshot", &ImGuiWindow->SilentCarshot);

				if (ImGui::CollapsingHeader("Spinner.Slapper")) {
					ImGui::InputInt("playerId", &ImGuiWindow->InputSpinnerPlayerId);
					ImGui::Checkbox("Transfer", &ImGuiWindow->SpinnerSlapper);
				}

				if (ImGui::CollapsingHeader("TransferOfControlVehicle")) {
					ImGui::InputInt("vehicleId", &ImGuiWindow->InputTransferOfControlVehicleId);
					ImGui::Checkbox("Transfer", &ImGuiWindow->TransferOfControlVehicle);
				}

			}

			if (ImGuiWindow->MiscWindow) {

				if (ImGui::Button("Spawn", ImVec2(120, 25)))
					SF->getSAMP()->getPlayers()->pLocalPlayer->Spawn();

				if (ImGui::Button("Reconnect", ImVec2(120, 25))) {
					SF->getSAMP()->disconnect(100);
					SF->getSAMP()->getInfo()->RestartGame();
					SF->getSAMP()->getInfo()->iGameState = GAMESTATE_WAIT_CONNECT;
				}

				ImGui::Checkbox("LogRPC", &ImGuiWindow->LogRPC);

				ImGui::Checkbox("Crosspiece", &ImGuiWindow->Crosspiece);

				if (ImGui::Checkbox("Sensfix", &ImGuiWindow->Sensfix)) {
					if (ImGuiWindow->Sensfix) {
						if (*(float*)0xB6EC1C != *(float*)(0xB6EC18))
							*(float*)(0xB6EC18) = *(float*)0xB6EC1C;
					}
				}

				ImGui::Checkbox("GpciSpoofer", &ImGuiWindow->GpciSpoofer);

				ImGui::Checkbox("GotoMark", &ImGuiWindow->GotoMark);

				ImGui::Checkbox("RollCrasher", &ImGuiWindow->RollCrasher);

				ImGui::Checkbox("FakePos", &ImGuiWindow->FakePos);

				if (ImGui::CollapsingHeader("RakLogger")) {
					ImGui::InputInt("playerId", &ImGuiWindow->inputSyncAllLoggerPlayerId);
					ImGui::Checkbox("Log", &ImGuiWindow->SyncLogger);
					ImGui::Separator();
					ImGui::Checkbox("Log.Onfoot", &ImGuiWindow->SyncLoggerOnfoot);
					ImGui::Checkbox("Log.Incar", &ImGuiWindow->SyncLoggerIncar);
					ImGui::Checkbox("Log.Passenger", &ImGuiWindow->SyncLoggerPassenger);
					ImGui::Checkbox("Log.Unoccupied", &ImGuiWindow->SyncLoggerUnoccupied);
					ImGui::Checkbox("Log.Bullet", &ImGuiWindow->SyncLoggerBullet);
					ImGui::Checkbox("Log.Aim", &ImGuiWindow->SyncLoggerAim);
				}

				if (ImGui::CollapsingHeader("WarpPlayer")) {
					for (int i = 0; i < SAMP_MAX_PLAYERS; i++) 
					{
						if (SF->getSAMP()->getPlayers()->IsPlayerDefined(i, false))
						{
							if (i == SF->getSAMP()->getPlayers()->sLocalPlayerID) continue;

							float fPos[3] = {SF->getSAMP()->getStreamedOutInfo()->fPlayerPos[i][0],SF->getSAMP()->getStreamedOutInfo()->fPlayerPos[i][1],SF->getSAMP()->getStreamedOutInfo()->fPlayerPos[i][2]};
							char buf[255];
							sprintf_s(buf, u8"%s[%d]", SF->getSAMP()->getPlayers()->GetPlayerName(i), i);

							if (ImGui::Button(buf))
								PEDSELF->Teleport(fPos[0], fPos[1], fPos[2]);
							
							memset(buf, 0, sizeof(buf));
						}
					}
				}
				if (ImGui::CollapsingHeader("StreamFind")) {
					for (int i = 0; i < SAMP_MAX_PLAYERS; i++) {
						if (SF->getSAMP()->getPlayers()->IsPlayerDefined(i, true))
						{
							if (i == SF->getSAMP()->getPlayers()->sLocalPlayerID) continue;

							char buf[255];
							sprintf_s(buf, u8"%s[%d]", SF->getSAMP()->getPlayers()->GetPlayerName(i), i);

							ImGui::Text(buf);

							memset(buf, 0, sizeof(buf));
						}
					}
				}

				if (ImGui::CollapsingHeader("RemovePed")) {
					ImGui::InputInt("playerId", &ImGuiWindow->InputRemovePlayerId);
					if (ImGui::Button("Remove")) {
						if (SF->getSAMP()->getPlayers()->iIsListed[ImGuiWindow->InputRemovePlayerId] == 1 && SF->getSAMP()->getPlayers()->pRemotePlayer[ImGuiWindow->InputRemovePlayerId] != nullptr &&
							SF->getSAMP()->getPlayers()->pRemotePlayer[ImGuiWindow->InputRemovePlayerId]->pPlayerData != nullptr && SF->getSAMP()->getPlayers()->pRemotePlayer[ImGuiWindow->InputRemovePlayerId]->pPlayerData->pSAMP_Actor != nullptr &&
							SF->getSAMP()->getPlayers()->pRemotePlayer[ImGuiWindow->InputRemovePlayerId]->pPlayerData->pSAMP_Actor->pGTA_Ped != nullptr) {
							CPed* Ped = (CPed*)SF->getSAMP()->getPlayers()->pRemotePlayer[ImGuiWindow->InputRemovePlayerId]->pPlayerData->pSAMP_Actor->pGTA_Ped;
							pFunc->RemovePed(Ped);
						}
					}
				}

				if (ImGui::CollapsingHeader("Collision")) {
					static unsigned __int8 disableCamCols[] = { 0x90, 0x90, 0x90, 0x90 };
					static unsigned __int8 enableCamCols[] = { 0x8B, 0x44, 0x24, 0x04 };

					ImGui::Checkbox("CollisionPlayer", &Collision->_nocolPeds);

					ImGui::Checkbox("CollisionVehicle", &Collision->_nocolVehicles);

					ImGui::Checkbox("CollisionObjects", &Collision->_nocolObjects);

					ImGui::Checkbox("CollisionBuildings", &Collision->_nocolBuildings);

					ImGui::Separator();

					if (ImGui::Checkbox("CollisionCamBuildings", &Collision->_nocolCamBuildings)) {
						if (Collision->_nocolCamBuildings) pFunc->Write((void*)0x41a820, disableCamCols, 4U);
						else pFunc->Write((void*)0x41a820, enableCamCols, 4U);
					}

					if (ImGui::Checkbox("CollisionCamVehicle", &Collision->_nocolCamVehicle)) {
						if (Collision->_nocolCamVehicle) pFunc->Write((void*)0x41a990, disableCamCols, 4U);
						else pFunc->Write((void*)0x41a990, enableCamCols, 4U);
					}

					if (ImGui::Checkbox("CollisionCamObject", &Collision->_nocolCamObject)) {
						if (Collision->_nocolCamObject) pFunc->Write((void*)0x41ab20, disableCamCols, 4U);
						else pFunc->Write((void*)0x41ab20, enableCamCols, 4U);
					}

					ImGui::Separator();

					if (ImGui::Checkbox("AntiHook", &ImGuiWindow->AntiHook)) {
						if (ImGuiWindow->AntiHook) CState->SuperCollisionPatch(true);
						else CState->SuperCollisionPatch(false);
					}
				}
				if (ImGui::CollapsingHeader("ChatFlooder")) {
					ImGui::InputText("Text", ImGuiWindow->ChatFlooderText, 255);
					ImGui::InputInt("Speed", &ImGuiWindow->ChatFlooderSpeed);
					ImGui::Checkbox("Flood", &ImGuiWindow->ChatFlooder);
				}

			}

			if (ImGuiWindow->NopSampWindow) 
				CheckboxNopRPC();
			
			if (ImGuiWindow->ProtectWindow) {
				ImGui::Checkbox("log", &LogFunc->log_enabled);
				ImGui::Separator();
				ImGui::Checkbox("Hook.Onfoot", &ImGuiWindow->onfoot);
				ImGui::Checkbox("Hook.Incar", &ImGuiWindow->incar);
				ImGui::Checkbox("Hook.Unoccupied", &ImGuiWindow->unoccupied);
				ImGui::Checkbox("Hook.Bullet", &ImGuiWindow->bullet);
				ImGui::Checkbox("Hook.Aim", &ImGuiWindow->aim);
				ImGui::Checkbox("Hook.Passenger", &ImGuiWindow->passenger);
			}
			if (ImGuiWindow->GtaPatchWindow) {
				if (ImGui::Checkbox("MegaJump", reinterpret_cast<bool*>(0x96916C))) { //Большой прыжок
					if (*reinterpret_cast<bool*>(0x96916C))
						*reinterpret_cast<float*>(0x0085862C) = ImGuiWindow->heightmegaJump; //высота прыжка
				}
				ImGui::Checkbox("Infinity Ammo", reinterpret_cast<bool*>(0x969178));
				ImGui::Checkbox("Infinity Run", reinterpret_cast<bool*>(0xB7CEE4));
				ImGui::Checkbox("Infinity Oxygen", reinterpret_cast<bool*>(0x96916E));
				ImGui::Separator();
				ImGui::Checkbox("EasyHandling", reinterpret_cast<bool*>(0x96914C));
				ImGui::Checkbox("RidingOnWater", reinterpret_cast<bool*>(0x969152));
				ImGui::Checkbox("RidingUnderwater", reinterpret_cast<bool*>(0x6C2759));
				ImGui::Checkbox("InvisibleCars", reinterpret_cast<bool*>(0x96914B));
				ImGui::Checkbox("HighJump BMX", reinterpret_cast<bool*>(0x969161));
			}
			if (ImGuiWindow->SettingsWindow) {
				if(ImGui::Button("ReloadConfig", ImVec2(340, 25)))
					pFunc->cfgFile();

				ImGui::SliderFloat("GameSpeed", &ImGuiWindow->gamespeed, 0.0f, 5.f);

				ImGui::SliderFloat("Height MegaJump", &ImGuiWindow->heightmegaJump, 0.0f, 100.f);
			}
		}
		ImGui::End();
	}
}