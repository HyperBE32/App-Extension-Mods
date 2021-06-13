/// <summary>
/// Hooked function that returns Sonic Forces' icon - following the same pattern as LoadIconA.
/// </summary>
HICON __stdcall LoadSonicForcesIcon(HINSTANCE hInstance, LPCSTR lpIconName)
{
	return LoadIconA(DllMain::handle, (LPCSTR)IDI_ICON);
}

void Patches::Install()
{
	if (Configuration::windowTitle)
	{
		// Write 'SONIC FORCES' in the title bar.
		WRITE_MEMORY(0xE7A99D, uint8_t, 0x3C);
		WRITE_MEMORY(0x1606C3C, uint8_t, "SONIC FORCES\0");

		// Use Sonic Forces' icon for the window.
		WRITE_CALL(0xE7B843, &LoadSonicForcesIcon);
		WRITE_NOP(0xE7B848, 1);
	}

	// Freeze lives.
	WRITE_NOP(0xD59A67, 6);

	// Disable 1-UP from rings.
	WRITE_NOP(0xE68562, 5);

	// Remove 1-UP object.
	WRITE_MEMORY(0x166463C, uint8_t, 0x00);

	// Remove 1-UP item box.
	WRITE_MEMORY(0x167DDE4, uint8_t, 0x00);

	// Disable chaos energy particles.
	WRITE_JUMP(0x112435C, (void*)0x112440C);
	WRITE_NOP(0x1124733, 5);

	// Disable title loading video (fixes hang on title screen).
	WRITE_MEMORY(0xD6966E, uint8_t, 0xE9, 0x14, 0x01, 0x00, 0x00);

	// Disable loading hints (fixes mission text appearing on the loading screen).
	WRITE_MEMORY(0x448959, uint8_t, 0xE9, 0x12, 0x01, 0x00, 0x00);

	// Use Sonic Unleashed's intro XNCP for normal stages.
	WRITE_MEMORY(0x168F1F8, uint8_t, "_b\0");

	if (!Configuration::homingReticle)
	{
		// Use Sonic Generations' lock-on XNCP.
		WRITE_MEMORY(0x15E36E4, uint8_t, "_b\0");
		WRITE_MEMORY(0x155E5E8, uint8_t, "_b\0");

#if _DEBUG
		printf("[Forces HUD] Homing reticle is disabled!\n");
#endif
	}

	if (Configuration::boostText)
	{
		// Force enable the boost button prompt (in case of patch conflicts).
		WRITE_MEMORY(0x109BC7C, uint8_t, 0x8B, 0x8D, 0x5C, 0x02, 0x00, 0x00);
	}
	else
	{
		// Force disable the boost button prompt based on configuration.
		WRITE_MEMORY(0x109BC7C, uint8_t, 0xE9, 0x71, 0x01, 0x00, 0x00);
	}

	if (Configuration::homingSound)
	{
		// Use custom sound ID for the homing sound.
		WRITE_MEMORY(0xDEBDB7, uint8_t, 0x2C, 0x0F, 0x01);
	}
}