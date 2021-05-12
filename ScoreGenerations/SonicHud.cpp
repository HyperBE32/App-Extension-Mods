#include "SonicHud.h"
#include "ScoreListener.h"
#include "Mod.h"
#include "StateHooks.h"

// Declare class variables.
unsigned int SonicHud::totalRingCount = 0;
unsigned int SonicHud::ringCount = 0;
unsigned int SonicHud::elapsedTime = 0;

/// <summary>
/// Replaces leading nulls from the string printer with dashes which are invisible in the textures.
/// </summary>
/// <param name="rings">Ring count from input register.</param>
void __fastcall UpdateRingCount(unsigned int rings)
{
	// Update current ring count.
	SonicHud::ringCount = rings;

	// Update total ring count.
	if (rings > SonicHud::totalRingCount)
	{
		SonicHud::totalRingCount = rings;
	}
}

__declspec(naked) void DefaultRingFormatterMidAsmHook()
{
	static void* returnAddress = (void*)0x1098E59;

	__asm
	{
		// Get ring count from registers.
		mov ecx, [esp + 100h + 0xFFFFFF30]
		mov esi, [ecx + 10h]

		mov ecx, esi
		call UpdateRingCount
		mov edx, eax

		jmp [returnAddress]
	}
}

__declspec(naked) void FinalBossRingFormatterMidAsmHook()
{
	static void* interruptAddress = (void*)0x41CAA0;
	static void* returnAddress = (void*)0x12281C5;

	__asm
	{
		call [interruptAddress]

		// Get ring count from registers.
		mov eax, [esp + 50h + 0xFFFFFFD8]
		mov [esp + 50h + 0xFFFFFFC0], eax

		mov ecx, eax
		call UpdateRingCount
		mov edx, eax

		jmp [returnAddress]
	}
}

/// <summary>
/// Updates the elapsed time.
/// </summary>
/// <param name="minutes">Minutes from EDI.</param>
/// <param name="seconds">Seconds from EAX.</param>
void __fastcall UpdateElapsedTime(unsigned int minutes, unsigned int seconds)
{
	// Update real-time elapsed time.
	SonicHud::elapsedTime = (minutes * 60) + seconds;
}

__declspec(naked) void TimeFormatterMidAsmHook()
{
	static void* interruptAddress = (void*)0xA6901D;
	static void* returnAddress = (void*)0x1098D52;

	__asm
	{
		call [interruptAddress]

		mov ecx, eax
		mov edx, edi
		call UpdateElapsedTime
		mov edx, eax

		jmp [returnAddress]
	}
}

FUNCTION_PTR(void, __thiscall, ProcMsgSetPinballHud, 0x1095D40, void* This, const SonicHud::MsgSetPinballHud& msgSetPinballHud);

HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* This, void* Edx, void* pUpdateInfo)
{
	SonicHud::MsgSetPinballHud msgSetPinballHud { };
	msgSetPinballHud.flags = 1;
	msgSetPinballHud.score = ScoreListener::score;

	// Checks if the current stage is Casino Night before assigning the local score.
	if (strcmp(StateHooks::stageID, "cnz100") != 0)
		ProcMsgSetPinballHud(This, msgSetPinballHud);

	originalCHudSonicStageUpdate(This, Edx, pUpdateInfo);
}

/// <summary>
/// Installs the mid-ASM hooks.
/// </summary>
void SonicHud::Install()
{
	// Display the Casino Night score.
	WRITE_NOP(0x109C1DA, 2);

	// Set score string format.
	WRITE_MEMORY(0x1095D7D, char*, Mod::scoreFormat.c_str());

	// Install hook to update the score counter.
	INSTALL_HOOK(CHudSonicStageUpdate);

	// Jump to store elapsed time locally for time bonus.
	WRITE_JUMP(0x1098D4D, &TimeFormatterMidAsmHook);

	// Jump to ring formatters to update the ring count.
	WRITE_JUMP(0x1098E4C, &DefaultRingFormatterMidAsmHook);
	WRITE_JUMP(0x12281B8, &FinalBossRingFormatterMidAsmHook);
}