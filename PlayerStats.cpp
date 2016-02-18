﻿#include "stdafx.h"
#include "PlayerStats.h"

void renderStatsParty(const char *label, int offset)
{
	if (!ImGui::TreeNode(label))
		return;

	int baseOffset = 0xA7000 + offset;
	ImGui::InputScalar<int>("Level", GetBasePtr(baseOffset + 0xDD0), 0);
	ImGui::InputScalar<int>("Discipline Points", GetBasePtr(baseOffset + 0xA14), 0);
	ImGui::InputScalar<int>("XP", GetBasePtr(baseOffset + 0x994), 0);

	int statsOffset = baseOffset + 0x96C;
	ImGui::InputFloatN("HP (Current/Max/Max+)", GetBasePtr<float>(statsOffset + 4 * 0), 3, 0.0f, FLT_MAX, 2);
	ImGui::InputFloatN("Stamina (Current/Max/Max+)", GetBasePtr<float>(statsOffset + 4 * 3), 3, 0.0f, FLT_MAX, 2);

	ImGui::Columns(2, nullptr, false);
	ImGui::InputFloat("Strength", GetBasePtr<float>(statsOffset + 4 * 6));
	ImGui::NextColumn();
	ImGui::InputFloat("Defenses", GetBasePtr<float>(statsOffset + 4 * 7));
	ImGui::Columns();

	ImGui::Columns(2, nullptr, false);
	ImGui::InputFloat("Magick", GetBasePtr<float>(statsOffset + 4 * 8));
	ImGui::NextColumn();
	ImGui::InputFloat("Magick Defenses", GetBasePtr<float>(statsOffset + 4 * 9));
	ImGui::Columns();

	if (ImGui::TreeNode("Vocations"))
	{
		int vocationOffset = statsOffset + 13 * 4;
		ImGui::InputScalar<int>("Fighter", GetBasePtr(vocationOffset += 0), 0, 9);
		ImGui::InputScalar<int>("Strider", GetBasePtr(vocationOffset += 4), 0, 9);
		ImGui::InputScalar<int>("Mage", GetBasePtr(vocationOffset += 4), 0, 9);
		if (!offset)// player
		{
			ImGui::InputScalar<int>("Mystic Knight", GetBasePtr(vocationOffset += 4), 0, 9);
			ImGui::InputScalar<int>("Assassin", GetBasePtr(vocationOffset += 4), 0, 9);
			ImGui::InputScalar<int>("Magic Archer", GetBasePtr(vocationOffset += 4), 0, 9);
		}
		ImGui::InputScalar<int>("Warrior", GetBasePtr(vocationOffset += 4), 0, 9);
		ImGui::InputScalar<int>("Ranger", GetBasePtr(vocationOffset += 4), 0, 9);
		ImGui::InputScalar<int>("Sorcerer", GetBasePtr(vocationOffset += 4), 0, 9);
		ImGui::TreePop();
	}

	if (offset == 0x7F0 && ImGui::TreeNode("Inclinations"))//main pawn
	{
		int inclinationsOffset = statsOffset + 0x1224;
		ImGui::InputFloatN("Scather", GetBasePtr<float>(inclinationsOffset += 0), 1, 0);
		ImGui::InputFloatN("Medicant", GetBasePtr<float>(inclinationsOffset += 4 * 3), 1, 0);
		ImGui::InputFloatN("Mitigator", GetBasePtr<float>(inclinationsOffset += 4 * 3), 1, 0);
		ImGui::InputFloatN("Challenger", GetBasePtr<float>(inclinationsOffset += 4 * 3), 1, 0);
		ImGui::InputFloatN("Utilitarian", GetBasePtr<float>(inclinationsOffset += 4 * 3), 1, 0);
		ImGui::InputFloatN("Guardian", GetBasePtr<float>(inclinationsOffset += 4 * 3), 1, 0);
		ImGui::InputFloatN("Nexus", GetBasePtr<float>(inclinationsOffset += 4 * 3), 1, 0);
		ImGui::InputFloatN("Pioneer", GetBasePtr<float>(inclinationsOffset += 4 * 3), 1, 0);
		ImGui::InputFloatN("Acquisitor", GetBasePtr<float>(inclinationsOffset += 4 * 3), 1, 0);
		ImGui::TreePop();
	}
	ImGui::TreePop();
}

void renderStatsSkill(int offset, int skillCount, const char *label, TwEnumVal *enumVal, int enumCount)
{
	if (ImGui::TreeNode(label))
	{
		for (int i = 0; i < skillCount; i++)
			ImGui::ComboEnum<UINT32>(("##" + std::to_string(i)).c_str(), GetBasePtr(offset + 4 * i), enumVal, enumCount);
		ImGui::TreePop();
	}
}

TwEnumVal skillsAugments[], skillsSword[], skillsLongsword[], skillsDagger[], skillsStaves[];
TwEnumVal skillsShield[], skillsMagickShield[], skillsBow[], skillsLongbow[], skillsMagickBow[];
void renderStatsSkills(const char *label, int offset)
{
	if (ImGui::TreeNode(label))
	{
		int skillsOffset = 0xA7808 + offset;
		renderStatsSkill(skillsOffset + 24 * 12, 6, "Augments", skillsAugments, 83);
		renderStatsSkill(skillsOffset + 24 * 0, 3, "Sword", skillsSword, 21);
		renderStatsSkill(skillsOffset + 24 * 1, 3, "Mace", skillsSword, 21);
		renderStatsSkill(skillsOffset + 24 * 2, 3, "Longsword", skillsLongsword, 11);
		renderStatsSkill(skillsOffset + 24 * 6, 3, "Warhammer", skillsLongsword, 11);
		renderStatsSkill(skillsOffset + 24 * 3, 3, "Dagger", skillsDagger, 21);
		renderStatsSkill(skillsOffset + 24 * 4, 6, "Staff", skillsStaves, 31);
		renderStatsSkill(skillsOffset + 24 * 5, 6, "Archistaff", skillsStaves, 31);
		renderStatsSkill(skillsOffset + 24 * 7, 3, "Shield", skillsShield, 10);
		renderStatsSkill(skillsOffset + 24 * 8, 3, "Magick Shield", skillsMagickShield, 16);
		renderStatsSkill(skillsOffset + 24 * 9, 3, "Bow", skillsBow, 10);
		renderStatsSkill(skillsOffset + 24 * 10, 3, "Longbow", skillsLongbow, 10);
		renderStatsSkill(skillsOffset + 24 * 11, 3, "Magic kBow", skillsMagickBow, 10);
		ImGui::TreePop();
	}
}

void renderStatsUI()
{
	if (ImGui::CollapsingHeader("Stats"))
	{
		ImGui::InputScalar<int>("Gold", GetBasePtr(0xA7A18), 0);
		ImGui::InputScalar<int>("Rift Crystals", GetBasePtr(0xA7A1C), 0);
		renderStatsParty("Player", 0);
		renderStatsParty("Main Pawn", 0x7F0);
		renderStatsParty("Pawn 1", 0x7F0 + 0x1660);
		renderStatsParty("Pawn 2", 0x7F0 + 0x1660 + 0x1660);
	}

	if (ImGui::CollapsingHeader("Skills"))
	{
		renderStatsSkills("Player", 0);
		renderStatsSkills("Main Pawn", 0x7F0);
		renderStatsSkills("Pawn 1", 0x7F0 + 0x1660);
		renderStatsSkills("Pawn 2", 0x7F0 + 0x1660 + 0x1660);
	}
}

void Hooks::PlayerStats() { InGameUIAdd(renderStatsUI); }

TwEnumVal skillsSword[] =
{
	{ -1, "-1: Empty" },
	{ 40, "40: Blink Strike | Burst Strike" },
	{ 41, "41: Broad Cut | Broad Slash" },
	{ 42, "42: Downthrust | Downcrack" },
	{ 43, "43: Tusk Toss | Antler Toss" },
	{ 44, "44: Compass Slash | Full Moon Slash" },
	{ 45, "45: Skyward Lash | Heavenward Lash" },
	{ 46, "46: Flesh Skewer | Soul Skewer" },
	{ 47, "47: Hindsight Slash | Hindsight Sweep" },
	{ 48, "48: Stone Will | Steel Will" },
	{ 49, "49: Legion's Bite | Dragon's Maw" },
	{ 50, "50: Perilous Sigil | Ruinous Sigil" },
	{ 51, "51: Magick Cannon | Great Cannon" },
	{ 52, "52: Funnel Sigil | Vortex Sigil" },
	{ 53, "53: Sky Dance | Sky Rapture" },
	{ 54, "54: Stone Grove | Stone Forest" },
	{ 55, "55: Intimate Strike | Initimate Gambit" },
	{ 56, "56: Windmill Slash | Great Windmill" },
	{ 57, "57: Powder Charge | Powder Blast" },
	{ 58, "58: Gouge | Dire Gouge" },
	{ 59, "59: Clarity | Clairvoyance" }
};

TwEnumVal skillsLongsword[] =
{
	{ -1, "-1: Empty" },
	{ 100, "100: Upward Strike | Whirlwind Slash" },
	{ 101, "101: Pommel Strike | Pommel Bash" },
	{ 102, "102: Savage Lunge | Indomitable Lunge" },
	{ 103, "103: Escape Slash | Exodus Slash" },
	{ 104, "104: Savage Lash | Indomitable Lash" },
	{ 105, "105: Ladder Blade | Catapult Blade" },
	{ 106, "106: Spark Slash | Corona Slash" },
	{ 107, "107: Act of Atonement | Act of Vengeance" },
	{ 108, "108: Battle Cry | War Cry" },
	{ 109, "109: Arc of Might | Arc of Deliverance" }
};

TwEnumVal skillsDagger[] =
{
	{ -1, "-1: Empty" },
	{ 150, "150: Biting Wind | Cutting Wind" },
	{ 151, "151: Toss and Trigger | Advanced Trigger" },
	{ 152, "152: Scarlet Kisses | Hundred Kisses" },
	{ 153, "153: Dazzle Hold | Dazzle Blast" },
	{ 154, "154: Sprint | Mad Dash" },
	{ 155, "155: Helm Splitter | Skull Splitter" },
	{ 156, "156: Ensnare | Implicate" },
	{ 157, "157: Pilfer | Master Thief" },
	{ 158, "158: Reset | Instant Reset" },
	{ 159, "159: Stepping Stone | Leaping Stone" },
	{ 160, "160: Sunburst | Sunflare" },
	{ 161, "161: Shadowpin | Shadowshackle" },
	{ 162, "162: Scension | Grand Scension" },
	{ 163, "163: Magick Rebuffer | Magick Rebalancer" },
	{ 164, "164: Wind Harness | Gale Harness" },
	{ 165, "165: Back Kick | Escape Onslaught" },
	{ 166, "166: Spiderbite | Snakebite" },
	{ 167, "167: Backfire | Immolation" },
	{ 168, "168: Stealth | Invisibility" },
	{ 169, "169: Easy Kill | Masterful Kill" }
};

TwEnumVal skillsStaves[] =
{
	{ -1, "-1: Empty" },
	{ 210, "210: Ingle | High Ingle" },
	{ 211, "211: Frazil | High Frazil" },
	{ 212, "212: Levin | High Levin" },
	{ 213, "213: Comestion | High Comestion" },
	{ 214, "214: Frigor | High Frigor" },
	{ 215, "215: Brontide | High Brontide" },
	{ 216, "216: Grapnel | High Grapnel" },
	{ 217, "217: Silentium | High Silentium" },
	{ 218, "218: Blearing | High Blearing" },
	{ 219, "219: Lassitude | High Lassitude" },
	{ 220, "220: Anodyne | High Anodyne" },
	{ 221, "221: Halidom | High Halidom" },
	{ 222, "222: Fire Boon | Fire Affinity" },
	{ 223, "223: Ice Boon | Ice Affinity" },
	{ 224, "224: Thunder Boon | Thunder Affinity" },
	{ 225, "225: Holy Boon | Holy Affinity" },
	{ 226, "226: Dark Boon | Dark Affinity" },
	{ 227, "227: Bolide | High Bolide" },
	{ 228, "228: Gicel | High Gicel" },
	{ 229, "229: Fulmination | High Fulmination" },
	{ 230, "230: Seism | High Seism" },
	{ 231, "231: Maelstrom | High Maelstrom" },
	{ 232, "232: Exequy | High Exequy" },
	{ 233, "233: Petrifaction | High Petrifaction" },
	{ 234, "234: Miasma | High Miasma" },
	{ 235, "235: Perdition | High Perdition" },
	{ 236, "236: Sopor | High Sopor" },
	{ 237, "237: Voidspell | High Voidspell" },
	{ 238, "238: Spellscreen | High Spellscreen" },
	{ 239, "239: Necromancy | High Necromancy" }
};

/*TwEnumVal skillsStaff[] =
{
	{ -1, "-1: Empty" },
	{ 210, "210: Ingle | High Ingle" },
	{ 211, "211: Frazil | High Frazil" },
	{ 212, "212: Levin | High Levin" },
	{ 213, "213: Comestion | High Comestion" },
	{ 214, "214: Frigor | High Frigor" },
	{ 215, "215: Brontide | High Brontide" },
	{ 216, "216: Grapnel | High Grapnel" },
	{ 217, "217: Silentium | High Silentium" },
	{ 218, "218: Blearing | High Blearing" },
	{ 220, "220: Anodyne | High Anodyne" },
	{ 221, "221: Halidom | High Halidom" },
	{ 222, "222: Fire Boon | Fire Affinity" },
	{ 223, "223: Ice Boon | Ice Affinity" },
	{ 224, "224: Thunder Boon | Thunder Affinity" },
	{ 225, "225: Holy Boon | Holy Affinity" },
	{ 226, "226: Dark Boon | Dark Affinity" },
	{ 227, "227: Bolide | High Bolide" },
	{ 235, "235: Perdition | High Perdition" },
	{ 236, "236: Sopor | High Sopor" },
	{ 238, "238: Spellscreen | High Spellscreen" }
};

TwEnumVal skillsArchistaff[] =
{
	{ -1, "-1: Empty" },
	{ 210, "210: Ingle | High Ingle" },
	{ 211, "211: Frazil | High Frazil" },
	{ 212, "212: Levin | High Levin" },
	{ 213, "213: Comestion | High Comestion" },
	{ 214, "214: Frigor | High Frigor" },
	{ 215, "215: Brontide | High Brontide" },
	{ 217, "217: Silentium | High Silentium" },
	{ 218, "218: Blearing | High Blearing" },
	{ 219, "219: Lassitude | High Lassitude"},
	{ 222, "222: Fire Boon | Fire Affinity" },
	{ 223, "223: Ice Boon | Ice Affinity" },
	{ 224, "224: Thunder Boon | Thunder Affinity" },
	{ 225, "225: Holy Boon | Holy Affinity" },
	{ 226, "226: Dark Boon | Dark Affinity" },
	{ 227, "227: Bolide | High Bolide" },
	{ 228, "228: Gicel | High Gicel" },
	{ 229, "229: Fulmination | High Fulmination" },
	{ 230, "230: Seism | High Seism" },
	{ 231, "231: Maelstrom | High Maelstrom" },
	{ 232, "232: Exequy | High Exequy" },
	{ 233, "233: Petrifaction | High Petrifaction" },
	{ 234, "234: Miasma | High Miasma" },
	{ 237, "237: Voidspell | High Voidspell" },
	{ 239, "239: Necromancy | High Necromancy" }
};*/

TwEnumVal skillsShield[] =
{
	{ -1, "-1: Empty" },
	{ 270, "270: Shield Strike | Shield Storm" },
	{ 271, "271: Springboard | Launchboard" },
	{ 272, "272: Shield Summons | Shield Drum" },
	{ 273, "273: Cymbal Attack | Cymbal Onslaught" },
	{ 274, "274: Sheltered Spike | Sheltered Assault" },
	{ 275, "275: Perfect Defense | Divine Defense" },
	{ 276, "276: Moving Castle | Swift Castle" },
	{ 277, "277: Flight Response | Enhanced Response" },
	{ 278, "278: Staredown | Showdown" }
};

TwEnumVal skillsMagickShield[] =
{
	{ -1, "-1: Empty" },
	{ 310, "310: Firecounter | Flame Riposte" },
	{ 311, "311: Icecounter | Frost Riposte" },
	{ 312, "312: Thundercounter | Thunder Riposte" },
	{ 313, "313: Holycounter | Blessed Riposte" },
	{ 314, "314: Darkcounter | Abyssal Riposte" },
	{ 315, "315: Fire Enchanter | Flame Trance" },
	{ 316, "316: Ice Enchanter | Ice Enchanter" },
	{ 317, "317: Thunder Enchanter | Thunder Enchanter" },
	{ 318, "318: Holy Enchanter | Blessed Trance" },
	{ 319, "319: Dark Enchanter | Abyssal Trance" },
	{ 320, "320: Holy Glare | Holy Furor" },
	{ 321, "321: Dark Anguish | Abyssal Anguish" },
	{ 322, "322: Holy Wall | Holy Fortress" },
	{ 323, "323: Demonspite | Demonswrath" },
	{ 324, "324: Holy Aid | Holy Grace" }
};

TwEnumVal skillsBow[] =
{
	{ -1, "-1: Empty" },
	{ 350, "350: Threefold Arrow | Fivefold Flurry" },
	{ 351, "351: Triad Shot | Pentad Shot" },
	{ 352, "352: Full Bend | Mighty Bend" },
	{ 353, "353: Cloudburst Volley | Downpour Volley" },
	{ 354, "354: Splinter Dart | Fracture Dart" },
	{ 355, "355: Whistle Dart | Shriek Dart" },
	{ 356, "356: Keen Sight | Lyncean Sight" },
	{ 357, "357: Puncture Dart | Skewer Dart" },
	{ 358, "358: Blunting Arrow | Plegic Arrow" }
};

TwEnumVal skillsLongbow[] =
{
	{ -1, "-1: Empty" },
	{ 400, "400: Sixfold Arrow | Tenfold Flurry" },
	{ 401, "401: Heptad Shot | Endecad Shot" },
	{ 402, "402: Dire Arrow | Deathly Arrow" },
	{ 403, "403: Foot Binder | Body Binder" },
	{ 404, "404: Invasive Arrow | Crippling Arrow" },
	{ 405, "405: Flying Din | Fearful Din" },
	{ 406, "406: Meteor Shot | Comet Shot" },
	{ 407, "407: Whirling Arrow | Spiral Arrow" },
	{ 408, "408: Gamble Draw | Great Gamble" }
};

TwEnumVal skillsMagickBow[] =
{
	{ -1, "-1: Empty" },
	{ 359, "359: Threefold Bolt | Sixfold Bolt" },
	{ 360, "360: Seeker | True Seeker" },
	{ 361, "361: Explosive Bolt | Explosive Rivet" },
	{ 362, "362: Ricochet Seeker | Ricochet Hunter" },
	{ 363, "363: Magickal Flare | Magickal Gleam" },
	{ 364, "364: Funnel Trail | Vortex Trail" },
	{ 365, "365: Ward Arrow | Great Ward Arrow" },
	{ 366, "366: Bracer Arrow | Great Bracer Arrow" },
	{ 367, "367: Sacrificial Bolt | Great Sacrifice" }
};

TwEnumVal skillsAugments[] =
{
	{ -1, "-1: Empty" },
	{ 0, "0: Fitness" },
	{ 1, "1: Sinew" },
	{ 2, "2: Egression" },
	{ 3, "3: Prescience" },
	{ 4, "4: Exhilaration" },
	{ 5, "5: Vehemence" },
	{ 6, "6: Vigilance" },
	{ 10, "10: Leg-Strength" },
	{ 11, "11: Arm-Strength" },
	{ 12, "12: Grit" },
	{ 13, "13: Damping" },
	{ 14, "14: Dexterity" },
	{ 15, "15: Eminence" },
	{ 16, "16: Endurance" },
	{ 20, "20: Infection" },
	{ 21, "21: Equanimity" },
	{ 22, "22: Beatitude" },
	{ 23, "23: Perpetuation" },
	{ 24, "24: Intervention" },
	{ 25, "25: Attunement" },
	{ 26, "26: Apotropaism" },
	{ 30, "30: Adamance" },
	{ 31, "31: Periphery" },
	{ 32, "32: Sanctuary" },
	{ 33, "33: Restoration" },
	{ 34, "34: Retribution" },
	{ 35, "35: Reinforcement" },
	{ 36, "36: Fortitude" },
	{ 40, "40: Watchfulness" },
	{ 41, "41: Preemption" },
	{ 42, "42: Autonomy" },
	{ 43, "43: Bloodlust" },
	{ 44, "44: Entrancement" },
	{ 45, "45: Sanguinity" },
	{ 46, "46: Toxicity" },
	{ 50, "50: Resilience" },
	{ 51, "51: Resistance" },
	{ 52, "52: Detection" },
	{ 53, "53: Regeneration" },
	{ 54, "54: Allure" },
	{ 55, "55: Potential" },
	{ 56, "56: Magnitude" },
	{ 60, "60: Temerity" },
	{ 61, "61: Audacity" },
	{ 62, "62: Proficiency" },
	{ 63, "63: Ferocity" },
	{ 64, "64: Impact" },
	{ 65, "65: Bastion" },
	{ 66, "66: Clout" },
	{ 70, "70: Trajectory" },
	{ 71, "71: Morbidity" },
	{ 72, "72: Precision" },
	{ 73, "73: Stability" },
	{ 74, "74: Efficacy" },
	{ 75, "75: Radiance" },
	{ 76, "76: Longevity" },
	{ 80, "80: Gravitas" },
	{ 81, "81: Articulacy" },
	{ 82, "82: Conservation" },
	{ 83, "83: Emphasis" },
	{ 84, "84: Suasion" },
	{ 85, "85: Acuity" },
	{ 86, "86: Awareness" },
	{ 91, "91: Suasion" },
	{ 92, "92: Thrift" },
	{ 93, "93: Weal" },
	{ 94, "94: Renown" },
	{ 100, "100: Predation" },
	{ 101, "101: Fortune" },
	{ 102, "102: Tenacity" },
	{ 103, "103: Conveyance" },
	{ 104, "104: Acquisition" },
	{ 105, "105: Acquisition" },
	{ 106, "106: Prolongation" },
	{ 107, "107: Mettle" },
	{ 108, "108: Athleticism" },
	{ 109, "109: Recuperation" },
	{ 110, "110: Adhesion" },
	{ 111, "111: Opportunism" },
	{ 112, "112: Flow" },
	{ 113, "113: Grace" },
	{ 114, "114: Facility" }
};