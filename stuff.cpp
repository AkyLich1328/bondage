#include "stuff.h"

void stuff() {
	
	if (SF->getGame()->isKeyPressed(0x1B) && ImGuiWindow->ImGuiDrawMenu == true) {//закрыть на esc
		ImGuiWindow->ImGuiDrawMenu = false;
		SF->getSAMP()->getMisc()->ToggleCursor(false);
	}
	if (SF->getGame()->isKeyPressed(0x79)) {//f10
		ImGuiWindow->ImGuiDrawMenu ^= true;
		SF->getSAMP()->getMisc()->ToggleCursor(ImGuiWindow->ImGuiDrawMenu);
	}

	if (ImGuiWindow->CarDamager)
		CState->carDamager();

	if (ImGuiWindow->GlassesLagger)
		CState->GlassesLagger();

	if (ImGuiWindow->Invize)
		CState->Invize();

	if (ImGuiWindow->GpciSpoofer)
		CState->GpciSpoofer();


	if (ImGuiWindow->OnfootRvanka)
		CState->OnfootRvanka();

	if (ImGuiWindow->Pylsator)
		CState->Pylsator();

	if (ImGuiWindow->SetGameSpeed)
		*reinterpret_cast<float*>(0xB7CB64) = ImGuiWindow->gamespeed;

	if (ImGuiWindow->AirBreak)
		CState->AirBreak();

	if (ImGuiWindow->NoReload)
		CState->NoReload();

	if (ImGuiWindow->GotoMark) {
		if (SF->getGame()->isKeyPressed(0x01)) {
			CState->TeleportMetkaMap();
		}
	}

	if (ImGuiWindow->CarShoter)
		CState->carShooter();

	if (ImGuiWindow->CarWall)
		CState->carWall();

	if (ImGuiWindow->Damager)
		CState->SendBulletPlayer(ImGuiWindow->InputDamagerPlayerId);

	if (ImGuiWindow->SpeedHack)
		CState->SpeedHack();

	if (ImGuiWindow->CarFly)
		CState->CarFly();

	if (ImGuiWindow->SpinnerSlapper)
		CState->spinner();

	if (ImGuiWindow->SilentCarshot)
		CState->SilentCarshot();

	if (ImGuiWindow->AutoMending) {
		if (*(DWORD*)0xBA18FC) {
			if (PEDSELF->GetVehicle()->GetHealth() < 450) {
				PEDSELF->GetVehicle()->Fix();
				PEDSELF->GetVehicle()->SetHealth(1000.f);
			}
		}
	}

	if (ImGuiWindow->DriftController) {
		if (*(DWORD*)0xBA18FC) {
			struct actor_info *self = SF->getGame()->actorInfoGet(-1, ACTOR_ALIVE);
			struct vehicle_info *info = SF->getGame()->vehicleInfoGet(-1, 0);
			self->fCurrentRotation = -GAME->GetCamera()->GetCameraRotation();
			PEDSELF->GetVehicle()->SetOrientation(0, 0, self->fCurrentRotation);
			self->fTargetRotation = self->fCurrentRotation;
			info->base.matrix[4] = sinf(-self->fCurrentRotation);
			info->base.matrix[5] = cosf(-self->fCurrentRotation);
		}
	}
	
	pool_vehicle = *(struct pool **)0x00B74494;
	if (pool_vehicle == nullptr || pool_vehicle->start == nullptr || pool_vehicle->size <= 0)
		return;

	if (ImGuiWindow->ChatFlooder)
		CState->sentChatMessage(ImGuiWindow->ChatFlooderText, ImGuiWindow->ChatFlooderSpeed);

}