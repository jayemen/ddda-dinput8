#include "stdafx.h"
#include "InclinationProfiles.h"
#include "ImGui/imgui_internal.h"

const float DEFAULT = 500.0;
static bool pawnEnabled = false;
static bool pawn1Enabled = false;
static bool pawn2Enabled = false;

namespace Vocation {
	enum Enum
	{
		Assassin = 0,
		Fighter,
		MagickArcher,
		MysticKnight,
		Ranger,
		Sorcerer,
		Strider,
		Warrior,
		Last = Warrior,
		Length = Last + 1
	};
}

namespace Inclination
{
	enum Enum
	{
		Acquisitor = 0,
		Challenger,
		Guardian,
		Medicant,
		Mitigator,
		Nexus,
		Pioneer,
		Scather,
		Utilitarian,
		Last = Utilitarian,
		Length = Last + 1
	};
}

namespace Pawn {
	enum Enum {
		Main = 0,
		Pawn1,
		Pawn2,
		Last = Pawn2,
		Length = Last + 1
	};
}

static char const * const inclinationNames[Inclination::Enum::Length]  =
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

static char const * const vocationNames[Vocation::Enum::Length] =
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

static float profiles[Vocation::Enum::Length][Inclination::Enum::Length] =
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

static void writeStats(Pawn::Enum pawn, int vocation) 
{

}

static void renderInclinationUI()
{
	if (ImGui::CollapsingHeader("Inclination Profiles")) 
	{
		if (ImGui::Checkbox("Pawn Enabled", &pawnEnabled))
			config.setBool("inclinationProfiles", "pawnEnabled", pawnEnabled);

		if (ImGui::Checkbox("Pawn1 Enabled", &pawn1Enabled))
			config.setBool("inclinationProfiles", "pawn1Enabled", pawn1Enabled);

		if (ImGui::Checkbox("Pawn2 Enabled", &pawn2Enabled))
			config.setBool("inclinationProfiles", "pawn2Enabled", pawn2Enabled);

		for (int vocation = 0; vocation < Vocation::Enum::Length; ++vocation) 
		{
			const char * const vocationName = vocationNames[vocation];

			if (ImGui::TreeNode(vocationName))
			{
				for (int inclination = 0; inclination < Inclination::Enum::Length; ++inclination)
				{
					ImGui::InputFloat(inclinationNames[inclination], &profiles[vocation][inclination]);
				}

				ImGui::TreePop();
			}
		}

		if (ImGui::Button("Save")) 
		{
			for (int vocation = 0; vocation < Vocation::Enum::Length; ++vocation)
			{
				auto values = std::vector<float>(profiles[vocation], std::end(profiles[vocation]));
				config.setFloats("inclinationProfiles", vocationNames[vocation], std::move(values));
			}
		}
	}
}

void Hooks::InclinationProfiles()
{
	for (int vocation = 0; vocation < Vocation::Enum::Length; ++vocation)
	{
		auto values = config.getFloats("inclinationProfiles", vocationNames[vocation]);
		std::copy(values.begin(), values.end(), profiles[vocation]);
	}

	pawnEnabled = config.getBool("inclinationProfiles", "pawnEnabled", false);
	pawn1Enabled = config.getBool("inclinationProfiles", "pawn1Enabled", false);
	pawn2Enabled = config.getBool("inclinationProfiles", "pawn2Enabled", false);
	InGameUIAdd(renderInclinationUI);
}
