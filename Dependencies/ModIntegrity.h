using namespace std;

#pragma once

#define MOD_INFO "mod.ini"

#include <Crypto.h>
#include <fstream>
#include <iterator>
#include <shellapi.h>
#include <StringHelper.h>
#include <vector>

class ModIntegrity
{
public:
	struct Hash
	{
		const char* File;
		const char* Hash;
	};

	/// <summary>
	/// Verifies whether or not the data in the mod is exact to the pre-generated hashes.
	/// </summary>
	static bool VerifyData(vector<Hash> hashes);

	/// <summary>
	/// Verifies whether or not the input author is exact to the author in the mod config.
	/// </summary>
	static bool VerifyAuthor(const char* author);

	/// <summary>
	/// Throws an error message as requested.
	/// </summary>
	/// <param name="title">The name of the mod to appear on the message box window.</param>
	/// <param name="message">The message to display.</param>
	/// <param name="url">The URL to link to for the legitimate source.</param>
	static void Throw(const char* title, const char* message, const char* url);
};

inline bool ModIntegrity::VerifyData(vector<Hash> hashes)
{
	for (Hash const& hash : hashes)
	{
		// Hash storage.
		const uint8_t* expectedHash = StringHelper::HexStringToByteArray(hash.Hash);
		uint8_t computedHash[16];

		// Load data for hash computation.
		ifstream modData(hash.File, ios::binary);
		vector<char> bytes((istreambuf_iterator<char>(modData)), (istreambuf_iterator<char>()));

#if _DEBUG
		printf("[Mod Integrity] Expected Hash = %s\n", hash.Hash);
#endif

		// Compute MD5 hash from bytes of the expected hash location.
		Crypto::ComputeMD5(computedHash, data(bytes), bytes.size());

		// Close file stream.
		modData.close();

#if _DEBUG
		printf("[Mod Integrity] Computed Hash = %s\n", StringHelper::ByteArrayToHexString(computedHash, sizeof(computedHash)).c_str());
#endif

		// Compare hashes in memory.
		if (memcmp(expectedHash, computedHash, 16) != 0)
		{
#if _DEBUG
			printf("[Mod Integrity] Integrity check failed!\n");
#endif

			return false;
		}
	}

	return true;
}

inline bool ModIntegrity::VerifyAuthor(const char* author)
{
	INIReader modInfo(MOD_INFO);

	// Compare author field in the mod config with the input author.
	if (!StringHelper::Compare(modInfo.Get("Desc", "Author", author), author))
		return false;

	return true;
}

inline void ModIntegrity::Throw(const char* title = "Mod Integrity", const char* message = "", const char* url = "")
{
	if (StringHelper::IsEmpty(message))
	{
		if (StringHelper::IsEmpty(url))
		{
			// Set default exception message if it's empty.
			message = "Integrity check failed - please download this mod from a legitimate source!";
		}
		else
		{
			// Change default exception message if there's a URL present.
			message = "Integrity check failed - click OK to visit the legitimate source for this mod.";
		}
	}

	int result = MessageBox
	(
		nullptr,
		TEXT(message),
		TEXT(StringHelper::IsEmpty(title) ? "Mod Integrity" : title),
		StringHelper::IsEmpty(url) ? MB_ICONERROR : MB_ICONERROR | MB_OKCANCEL
	);

	// Open the URL in the web browser.
	if (result == IDOK && !StringHelper::IsEmpty(url))
		ShellExecute(0, 0, url, 0, 0, SW_SHOW);
}