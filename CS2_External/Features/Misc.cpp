#include "Misc.h"
#include "..\Sources\Language.h"
#include <iostream>

void Misc::CheatList() noexcept
{
	if (!MenuConfig::CheatList)
		return;

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowBgAlpha(0.3f);
	ImGui::SetNextWindowSize(ImVec2(200, 0));
	ImGui::Begin("Cheats List", nullptr, windowFlags);

	CheatText("ESP", ESPConfig::ESPenbled);
	if (MenuConfig::AimBot && (MenuConfig::AimAlways || GetAsyncKeyState(AimControl::HotKey)))
		ImGui::Text("Aimbot [Toggle]");
	CheatText("RCS", MenuConfig::RCS);
	CheatText("Glow", MenuConfig::Glow);
	CheatText("Radar", MenuConfig::ShowRadar);
	if (MenuConfig::TriggerBot && (MenuConfig::TriggerAlways || GetAsyncKeyState(MenuConfig::TriggerHotKey)))
		ImGui::Text("TriggerBot [Toggle]");

	CheatText("Crosshair", CrosshairConfig::ShowCrossHair);
	CheatText("Headshot Line", MenuConfig::ShowHeadShootLine);
	CheatText("No Flash", MenuConfig::NoFlash);
	//CheatText("Bhop", MenuConfig::BunnyHop);
	CheatText("HitSound", MenuConfig::HitSound);
	CheatText("Bomb Timer", MenuConfig::bmbTimer);
	//CheatText("Spec List", MenuConfig::SpecList);

	ImGui::End();
}

void Misc::Watermark() noexcept
{
	if (!MenuConfig::WaterMark)
		return;

//	globalvars GV;
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
	ImGui::SetNextWindowBgAlpha(0.3f);
	ImGui::Begin("Watermark", nullptr, windowFlags);

	static auto FrameRate = 1.0f;
	struct tm ptm;
//	FrameRate = 0.9f * FrameRate + 0.1f * GV.GetFrameCount();
	FrameRate = ImGui::GetIO().Framerate;
	getCurrentTime(&ptm);

	ImGui::Text("AimStar | %d fps | %02d:%02d:%02d",
		FrameRate != 0.0f ? static_cast<int>(FrameRate) : 0,
		ptm.tm_hour, ptm.tm_min, ptm.tm_sec);
	ImGui::End();
}

void Misc::HitSound(const CEntity& aLocalPlayer, int& PreviousTotalHits) noexcept
{
	if (!MenuConfig::HitSound)
		return;

	std::string soundDir = MenuConfig::SoundPath + "\\Hit.wav";
	std::wstring sound = Misc::STR2LPCWSTR(soundDir);

	uintptr_t pBulletServices;
	int totalHits;
	ProcessMgr.ReadMemory(aLocalPlayer.Pawn.Address + Offset::Pawn.BulletServices, pBulletServices);
	ProcessMgr.ReadMemory(pBulletServices + Offset::Pawn.TotalHit, totalHits);

	if (totalHits != PreviousTotalHits) {
		if (totalHits == 0 && PreviousTotalHits != 0)
		{
			// `totalHits` changed from non-zero to zero, do not play hitsound
		}
		else
		{
			// Play the HitSound
			PlaySoundW(sound.c_str(), NULL, SND_FILENAME | SND_ASYNC);
		}
	}
	PreviousTotalHits = totalHits;
}

void Misc::NoFlash(const CEntity& aLocalPlayer) noexcept
{
	if (!MenuConfig::NoFlash)
		return;

	float duration = 0.0f;
	ProcessMgr.WriteMemory(aLocalPlayer.Pawn.Address + Offset::Pawn.flFlashDuration, duration);
}

void Misc::EdgeJump(const CEntity& aLocalPlayer) noexcept
{
	// Unfinished
	float Gravity;
	ProcessMgr.ReadMemory(aLocalPlayer.Pawn.Address + Offset::Entity.GravityScale, Gravity);
	std::cout << Gravity << std::endl;
}

void Misc::Invincible(const CEntity& Player) noexcept
{
	if (!MenuConfig::infinity)
		return;

	float Health;
	ProcessMgr.ReadMemory(Player.Pawn.Address + Offset::ServerPawn.CurrentHealth, Health);

}