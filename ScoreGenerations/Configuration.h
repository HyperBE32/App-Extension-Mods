#pragma once

#define INI_FILE "ScoreGenerations.ini"

class Configuration
{
	/// <summary>
	/// Determines if the configuration was overridden.
	/// </summary>
	static bool overrideFlag;

public:
	/// <summary>
	/// The configuration being used for settings.
	/// </summary>
	static INIReader config;

	/// <summary>
	/// The path to the configuration.
	/// </summary>
	static string configPath;

	/// <summary>
	/// Gets the directory containing the configuration.
	/// </summary>
	static string GetConfigDirectory();

	/// <summary>
	/// Reads the INI configuration file for the mod.
	/// </summary>
	static void Read(string path);

	/// <summary>
	/// The maximum amount of score the player can obtain.
	/// </summary>
	static unsigned int scoreLimit;

	/// <summary>
	/// The amount of time in seconds the player is rewarded for being Super Sonic.
	/// </summary>
	static unsigned int superSonicTimer;

	/// <summary>
	/// Formatting used for the string printer for score.
	/// </summary>
	static string scoreFormat;

	/// <summary>
	/// Determines if the mod overriding the configuration uses a custom XNCP.
	/// </summary>
	static bool customXNCP;

	/// <summary>
	/// Not as intimidating as it sounds - just tells Score Generations that you're never in Casino Night Zone regardless.
	/// </summary>
	static bool overrideForbiddenCasino;

	/// <summary>
	/// List of forbidden stages that should not display the score counter.
	/// </summary>
	static vector<string> forbiddenStages;
};