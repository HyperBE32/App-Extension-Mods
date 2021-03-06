void* CLevelInfoData;
int ringLifeBonusCap = 100;
bool ringLifeReceived = false;

// 1.0.0: 0x1507D0A60
// 1.0.4: 0x15A60E0A0
// 1.0.9: 0x15B07DD30
SIG_SCAN
(
	sigCLevelInfoCtor,
	"\x40\x53\x48\x83\xEC\x20\x45\x31\xC0\x48\x89\xCB\x41\x8D\x50\x03\xE8\x00\x00\x00\x00\x31\xC9\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x03\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x43\x18\x31\xC0\x48\x89\x8B\x00\x00\x00\x00\x89\x8B\x00\x00\x00\x00\x48\x89\x8B\x00\x00\x00\x00\x48\x89\x8B\x00\x00\x00\x00\x89\x8B\x00\x00\x00\x00\x66\x89\x8B\x00\x00\x00\x00\x88\x8B\x00\x00\x00\x00\x48\x89\x43\x68\x48\x89\x43\x70\x48\x89\x43\x78\x48\x89\x83\x00\x00\x00\x00\x48\x89\x83\x00\x00\x00\x00\x48\x89\x83\x00\x00\x00\x00\x48\x89\x83\x00\x00\x00\x00\x48\x89\x83\x00\x00\x00\x00\x48\x89\x83\x00\x00\x00\x00\x48\x89\xD8\xC7\x43\x00\x00\x00\x00\x00\x89\x4B\x6C\xC7\x83\x00\x00\x00\x00\x00\x00\x00\x00\x89\x8B\x00\x00\x00\x00\x48\x83\xC4\x20\x5B\xC3",
	"xxxxxxxxxxxxxxxxx????xxxxx????xxxxxx????xxxxxxxxx????xx????xxx????xxx????xx????xxx????xx????xxxxxxxxxxxxxxx????xxx????xxx????xxx????xxx????xxx????xxxxx?????xxxxx????????xx????xxxxxx"
);
HOOK(void, __fastcall, CLevelInfoCtor, sigCLevelInfoCtor(), void* a1)
{
	CLevelInfoData = a1;

	// Reset life received flag on info construction.
	ringLifeReceived = false;

	originalCLevelInfoCtor(a1);
}

// 1.0.0: 0x1507D36D0
// 1.0.4: 0x15A615290
// 1.0.9: 0x15B07F4F0
SIG_SCAN
(
	sigCLevelInfoDtor,

	/* 1.0.0 -> 1.0.4 */
	"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8D\x05\x00\x00\x00\x00\x48\x89\xCF\x48\x89\x01\x89\xD3\x48\x83\xC1\x18\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x01\xE8\x00\x00\x00\x00\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x07\xF6\xC3\x01\x74\x0D\xBA\x00\x00\x00\x00\x48\x89\xF9\xE8\x00\x00\x00\x00\x48\x8B\x5C\x24\x00\x48\x89\xF8\x48\x83\xC4\x20\x5F\xC3",
	"xxxx?xxxxxxxx????xxxxxxxxxxxxxxx????xxxx????xxx????xxxxxxxxx????xxxx????xxxx?xxxxxxxxx",

	/* 1.0.9 */
	"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8D\x05\x00\x00\x00\x00\x48\x89\xCF\x48\x89\x01\x89\xD3\x48\x83\xC1\x18\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x01\xE8\x00\x00\x00\x00\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x07\xF6\xC3\x01\x74\x14\x8B\x15\x00\x00\x00\x00\x81\xF2\x00\x00\x00\x00\x48\x89\xF9\xE8\x00\x00\x00\x00\x48\x8B\x5C\x24\x00\x48\x89\xF8\x48\x83\xC4\x20\x5F\xC3",
	"xxxx?xxxxxxxx????xxxxxxxxxxxxxxx????xxxx????xxx????xxxxxxxxxx????xx????xxxx????xxxx?xxxxxxxxx"
);
HOOK(void, __fastcall, CLevelInfoDtor, sigCLevelInfoDtor(), void* a1, char a2)
{
	CLevelInfoData = nullptr;

	originalCLevelInfoDtor(a1, a2);
}

// 1.0.0: 0x1416DDA90
// 1.0.4: 0x1416DDC60
// 1.0.9: 0x1416E0130
SIG_SCAN
(
	sigReturnToTitle,
	"\x40\x53\x48\x83\xEC\x40\x48\xC7\x44\x24\x00\x00\x00\x00\x00\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00\x90\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x4B\x48\x8B\xC8\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x3E\x8B\x58\x08\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x20\x48\x8B\xC8\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x13\x48\x8B\xC8\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x06\x48\x8B\x48\x20\xEB\x02\x33\xC9\x89\x5C\x24\x38\x48\x8D\x54\x24\x00\xE8\x00\x00\x00\x00\x90\x48\x83\xC4\x40\x5B\xC3",
	"xxxxxxxxxx?????xxxx?x????xx????xxxxxxxxx????xxxxxxxxx????xxxxxxxxx????xxxxxxxxx????xxxxxxxxxxxxxxxxxxxxx?x????xxxxxxx"
);
FUNCTION_PTR(void, __cdecl, ReturnToTitle, sigReturnToTitle());

// 1.0.0: 0x141753250
// 1.0.4: 0x141753420
// 1.0.9: 0x141754060
SIG_SCAN
(
	sigMsgPLNotifyDeadCtor,
	"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x8B\xDA\x48\x8B\xF9\xBA\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8D\x05\x00\x00\x00\x00\x89\x5F\x18\x48\x8B\x5C\x24\x00\x48\x89\x07\x48\x8B\xC7\x48\x83\xC4\x20\x5F\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x40\x53\x48\x83\xEC\x20\x48\x8B\xD9\xBA\x00\x00\x00\x00\xB9\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x4C\x8B\xC0\x48\x85\xC0\x74\x49\x48\x8D\x05\x00\x00\x00\x00\x49\x89\x00\x48\x8D\x05\x00\x00\x00\x00\x8B\x53\x08\x41\x89\x50\x08\x8B\x53\x0C\x41\x89\x50\x0C\x8B\x4B\x10\x41\x89\x48\x10\x0F\xB6\x4B\x14\x41\x88\x48\x14\x0F\xB6\x4B\x15\x49\x89\x00\x41\x88\x48\x15\x8B\x43\x18\x41\x89\x40\x18\x49\x8B\xC0\x48\x83\xC4\x20\x5B\xC3\x48\x83\xC4\x20\x5B\xC3",
	"xxxx?xxxxxxxxxxx????x????xxx????xxxxxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????x????x????xxxxxxxxxxx????xxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
);
HOOK(void, __fastcall, MsgPLNotifyDeadCtor, sigMsgPLNotifyDeadCtor(), void* a1)
{
	int* lives = (int*)((char*)CLevelInfoData + 112);

	// Clamp lives to zero to prevent it falling into negatives.
	if ((*lives - 1) != 0)
		--*lives;
	else
		ReturnToTitle();

	originalMsgPLNotifyDeadCtor(a1);
}

// 1.0.0: 0x15089BB00
// 1.0.4: 0x15A66DE90
// 1.0.9: 0x15B0ACDA0
SIG_SCAN
(
	sigMsgPlayerPassTailsSaveMarkerCtor,

	/* 1.0.0 */
	"\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x48\x89\xD3\x0F\x29\x74\x24\x00\x8B\x15\x00\x00\x00\x00\x81\xF2\x00\x00\x00\x00\x41\x0F\xB6\xF9\x0F\x28\xF2\x48\x89\xCE\xE8\x00\x00\x00\x00\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x06\x8B\x03\x89\x46\x18\x8B\x43\x04\x89\x46\x1C\x8B\x43\x08\x48\x8B\x5C\x24\x00\x89\x46\x20\x0F\xB6\x44\x24\x00\x88\x46\x29\x8B\x44\x24\x68\x89\x46\x2C\x48\x89\xF0\xF3\x0F\x11\x76\x00\x0F\x28\x74\x24\x00\x40\x88\x7E\x28\x48\x8B\x74\x24\x00\x48\x83\xC4\x30\x5F\xC3\xCC\x4C\x8B\x1C\x24\x48\x83\xC4\x08\xE9\x00\x00\x00\x00",
	"xxxx?xxxx?xxxxxxxxxxxx?xx????xx????xxxxxxxxxxx????xxx????xxxxxxxxxxxxxxxxxxxxx?xxxxxxx?xxxxxxxxxxxxxxxxx?xxxx?xxxxxxxx?xxxxxxxxxxxxxxxx????",

	/* 1.0.9 */
	"\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x48\x89\xD3\x0F\x29\x74\x24\x00\xBA\x00\x00\x00\x00\x41\x0F\xB6\xF9\x0F\x28\xF2\x48\x89\xCE\xE8\x00\x00\x00\x00\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x06\x8B\x03\x89\x46\x18\x8B\x43\x04\x89\x46\x1C\x8B\x43\x08\x48\x8B\x5C\x24\x00\x89\x46\x20\x0F\xB6\x44\x24\x00\x88\x46\x29\x8B\x44\x24\x68\x89\x46\x2C\x48\x89\xF0\xF3\x0F\x11\x76\x00\x0F\x28\x74\x24\x00\x40\x88\x7E\x28\x48\x8B\x74\x24\x00\x48\x83\xC4\x30\x5F\xC3",
	"xxxx?xxxx?xxxxxxxxxxxx?x????xxxxxxxxxxx????xxx????xxxxxxxxxxxxxxxxxxxxx?xxxxxxx?xxxxxxxxxxxxxxxxx?xxxx?xxxxxxxx?xxxxxx",

	/* 1.0.4 */
	"\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x48\x89\xD3\x0F\x29\x74\x24\x00\xBA\x00\x00\x00\x00\x41\x0F\xB6\xF9\x0F\x28\xF2\x48\x89\xCE\xE8\x00\x00\x00\x00\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x06\x8B\x03\x89\x46\x18\x8B\x43\x04\x89\x46\x1C\x8B\x43\x08\x48\x8B\x5C\x24\x00\x89\x46\x20\x0F\xB6\x44\x24\x00\x88\x46\x29\x8B\x44\x24\x68\x89\x46\x2C\x48\x89\xF0\xF3\x0F\x11\x76\x00\x0F\x28\x74\x24\x00\x40\x88\x7E\x28\x48\x8B\x74\x24\x00\x48\x83\xC4\x30\x5F\xC3\xCC\x4C\x8B\x24\x24\x48\x8D\x64\x24\x00\x48\x8B\x04\x24\x48\x8D\x64\x24\x00\xE9\x00\x00\x00\x00\x4C\x8B\x1C\x24\x48\x8D\x64\x24\x00\xE9\x00\x00\x00\x00",
	"xxxx?xxxx?xxxxxxxxxxxx?x????xxxxxxxxxxx????xxx????xxxxxxxxxxxxxxxxxxxxx?xxxxxxx?xxxxxxxxxxxxxxxxx?xxxx?xxxxxxxx?xxxxxxxxxxxxxxx?xxxxxxxx?x????xxxxxxxx?x????"
);
HOOK(void, __fastcall, MsgPlayerPassTailsSaveMarkerCtor, sigMsgPlayerPassTailsSaveMarkerCtor(), __int64 a1, DWORD* a2, float a3, char a4, char a5, int a6)
{
	return;
}

// 1.0.0: 0x1418B1380
// 1.0.4: 0x1418B1830
// 1.0.9: 0x1418B4270
SIG_SCAN
(
	sigCStateFallingDead,
	"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x83\x79\x1C\x00\x48\x8B\xDA\x48\x8B\xF9\x75\x41\x8B\x41\x18\xD1\xE8\xA8\x01\x74\x38\x48\x8B\xCA\xE8\x00\x00\x00\x00\x48\x8B\xC8\xE8\x00\x00\x00\x00\x48\x8B\xCB\x84\xC0\x75\x07\xE8\x00\x00\x00\x00\xEB\x05\xE8\x00\x00\x00\x00\x48\x8B\xCB\xE8\x00\x00\x00\x00\xBA\x00\x00\x00\x00\x48\x8B\xCF\xE8\x00\x00\x00\x00\x48\x8B\x5C\x24\x00\xB0\x01\x48\x83\xC4\x20\x5F\xC3",
	"xxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxx????xxx????xxxx????x????xxxx????xxxx?xxxxxxxx"
);

void CLevelInfo::Init()
{
	if (!StringHelper::Compare(Configuration::tailsSave, "."))
	{
		// Skip MsgPLNotifyTailsSave in CStateFallingDead.
		WRITE_JUMP((char*)sigCStateFallingDead() + 0x34, (char*)sigCStateFallingDead() + 0x3D);

		INSTALL_HOOK(CLevelInfoCtor);
		INSTALL_HOOK(CLevelInfoDtor);
		INSTALL_HOOK(MsgPLNotifyDeadCtor);
		INSTALL_HOOK(MsgPlayerPassTailsSaveMarkerCtor);
	}
}

void CLevelInfo::OnFrame()
{
	// Check if a level is loaded before getting parameters.
	if (CLevelInfoData != nullptr)
	{
		switch (Configuration::ringLifeType)
		{
			case Configuration::RingLifeType::Disabled:
				return;

			case Configuration::RingLifeType::Once:
			{
				if (ringLifeReceived)
					return;

				break;
			}

			case Configuration::RingLifeType::Enabled:
				ringLifeReceived = false;
				break;
		}

		int* lives = (int*)((char*)CLevelInfoData + 112);
		int* rings = (int*)((char*)CLevelInfoData + 116);

		// Reset bonus cap if the player loses their rings.
		if (*rings == 0)
			ringLifeBonusCap = 100;

		while (*rings >= ringLifeBonusCap && !ringLifeReceived)
		{
			// Increment life counter.
			*lives += 1;

			// Increase bonus cap for the next 100 rings.
			ringLifeBonusCap += 100;

			// Set life received flag to cancel the next if using RingLifeType::Once.
			ringLifeReceived = true;
		}
	}
}