unsigned int StatisticsListener::totalRingCount = 0;
unsigned int StatisticsListener::totalVelocity = 0;
unsigned int StatisticsListener::minutes = 0;
unsigned int StatisticsListener::seconds = 0;
unsigned int StatisticsListener::ringCount = 0;

#pragma region ----- Hooked Functions -----

/// <summary>
/// Replaces leading nulls from the string printer with dashes which are invisible in the textures.
/// </summary>
/// <param name="rings">Ring count from input register.</param>
void __fastcall UpdateRingCount(unsigned int rings)
{
	// Update current ring count.
	StatisticsListener::ringCount = rings;

	// Update total ring count.
	if (rings > StatisticsListener::totalRingCount)
	{
		StatisticsListener::totalRingCount = rings;
	}
}

/// <summary>
/// Updates the elapsed time.
/// </summary>
/// <param name="minutes">Minutes from EDI.</param>
/// <param name="seconds">Seconds from EAX.</param>
void __fastcall UpdateElapsedTime(unsigned int minutes, unsigned int seconds)
{
	// Update real-time minutes and seconds.
	StatisticsListener::minutes = minutes;
	StatisticsListener::seconds = seconds;
}

#pragma endregion

#pragma region ----- Mid-ASM Hooks -----

__declspec(naked) void DefaultRingFormatter_MidAsmHook()
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

__declspec(naked) void FinalBossRingFormatter_MidAsmHook()
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


__declspec(naked) void TimeFormatter_MidAsmHook()
{
	static void* returnAddress = (void*)0x1098D47;

	__asm
	{
		pop ecx
		pop edx
		push edx
		push ecx
		call UpdateElapsedTime
		mov edx, eax

		lea ecx, [esp + 94h]
		jmp [returnAddress]
	}
}

#pragma endregion

unsigned int StatisticsListener::GetElapsedTime()
{
	return (minutes * 60) + seconds;
}

void StatisticsListener::Install()
{
	// Set score string format.
	WRITE_MEMORY(0x1095D7D, char*, Configuration::scoreFormat.c_str());

	// Store elapsed time locally for the time bonus.
	WRITE_JUMP(0x1098D40, &TimeFormatter_MidAsmHook);

	// Update the ring count.
	WRITE_JUMP(0x1098E4C, &DefaultRingFormatter_MidAsmHook);
	WRITE_JUMP(0x12281B8, &FinalBossRingFormatter_MidAsmHook);
}