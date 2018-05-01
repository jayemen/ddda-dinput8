#include "InclinationProfiles.h"
#include "stdafx.h"
#include "ImGui/imgui_internal.h"

const float DEFAULT = 500.0;
bool pawnEnabled = false;
bool pawn1Enabled = false;
bool pawn2Enabled = false;

enum Vocations
{
	Assassin = 0,
	Fighter = 1,
	MagickArcher = 2,
	MysticKnight = 3,
	Ranger = 4,
	Sorcerer = 5,
	Strider = 6,
	Warrior = 7,
	Last = Warrior,
	Length = Last + 1
};

enum Inclinations 
{
	Acquisitor = 0,
	Challenger = 1,
	Guardian = 2,
	Medicant = 3,
	Mitigator = 4,
	Nexus = 5,
	Pioneer = 6,
	Scather = 7,
	Utilitarian = 8,
	Last = Utilitarian,
	Length = Last + 1
};

const char * const inclinationNames[Inclinations::Length]  =
{
	"Acquisitor",
	"Challenger",
	"Guardian",
	"Medicant",
	"Mitigator",
	"Nexus",
	"Pioneer",
	"Scather",
	"Utilitarian"
};

const char * const vocationNames[Vocations::Length] =
{
	"Assassin",
	"Fighter",
	"MagickArcher",
	"MysticKnight",
	"Ranger",
	"Sorcerer",
	"Strider",
	"Warrior",
};

float profiles[Vocations::Length][Inclinations::Length] = 
{
	{ DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
	{ DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
	{ DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
	{ DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
	{ DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
	{ DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
	{ DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
	{ DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT }
};

static void renderInclinationUI()
{
	if (ImGui::CollapsingHeader("Inclination Profiles")) 
	{
		if (ImGui::Checkbox("Pawn Enabled", &pawnEnabled))
		{
			config.setBool()
		}
	}
}

void Hooks::InclinationProfiles()
{
	for (int i = 0; i < Vocations::Length; ++i) 
	{
		auto inclinations = config.getFloats("inclinationProfiles", vocationNames[i]);
		std::copy(inclinations.begin(), inclinations.end(), profiles[i]);
		InGameUIAdd(renderInclinationUI);
	}

	// pawnEnabled = config.getBool("inclinationProfiles", )
}
