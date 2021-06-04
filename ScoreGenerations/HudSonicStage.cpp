bool HudSonicStage::isMission = false;
float superSonicDeltaTimer = 0;

FUNCTION_PTR(void, __thiscall, SendMsgSetPinballHud, 0x1095D40, void* thisDeclaration, const HudSonicStage::MsgSetPinballHud& msgSetPinballHud);

HOOK(void, __fastcall, CHudSonicStageUpdate, 0x1098A50, void* thisDeclaration, void* edx, float* pUpdateInfo)
{
	// Update the Super Sonic timer and reward score after two seconds.
	HudSonicStage::UpdateSuperSonicTimer(pUpdateInfo);

	// Process the Casino Night score message.
	if (!HudSonicStage::IsCasino() && !HudSonicStage::IsStageForbidden())
		HudSonicStage::ProcessMsgSetPinballHud(thisDeclaration);

	originalCHudSonicStageUpdate(thisDeclaration, edx, pUpdateInfo);
}

HOOK(bool, __fastcall, ScriptImplInitialise, 0x1105120, int thisDeclaration)
{
	return HudSonicStage::isMission = originalScriptImplInitialise(thisDeclaration);
}

void HudSonicStage::UpdateSuperSonicTimer(float* pUpdateInfo)
{
	// Update the timer using delta time.
	superSonicDeltaTimer += *pUpdateInfo;

	if (superSonicDeltaTimer > Configuration::superSonicTimer)
	{
		// Reset the timer.
		superSonicDeltaTimer = 0;

		// Reward score every two seconds if the player is Super Sonic.
		if (PlayerListener::IsSuper())
			ScoreListener::Reward(ScoreListener::ScoreType::Super);
	}
}

void HudSonicStage::ProcessMsgSetPinballHud(void* thisDeclaration)
{
	// Set up message for Casino Night score.
	HudSonicStage::MsgSetPinballHud msgSetPinballHud;
	msgSetPinballHud.flags = 1;
	msgSetPinballHud.score = ScoreListener::score;

	SendMsgSetPinballHud(thisDeclaration, msgSetPinballHud);
}

bool HudSonicStage::IsStageForbidden()
{
	// Forbid missions from using the score counter.
	if (isMission)
		return true;

	// Check if the current stage ID matches any in the list.
	for (vector<string>::const_iterator i = Configuration::forbiddenStages.begin(); i != Configuration::forbiddenStages.end(); ++i)
	{
		// Stage ID matches - HUD must be special.
		if (StringHelper::Compare(StateHooks::stageID, i->c_str()))
			return true;
	}

	return false;
}

bool HudSonicStage::IsCasino()
{
	if (Configuration::overrideForbiddenCasino)
		return false;

	if (StringHelper::Compare(StateHooks::stageID, "cnz100"))
		return true;

	return false;
}

void HudSonicStage::Install()
{
	// Install hook to update the score counter.
	INSTALL_HOOK(CHudSonicStageUpdate);

	// Install hook to check for missions.
	INSTALL_HOOK(ScriptImplInitialise);
}