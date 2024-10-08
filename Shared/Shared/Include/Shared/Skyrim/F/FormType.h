#pragma once

#include "Shared/PrecompiledHeader.h"



namespace Skyrim
{
	enum class FormType
	{
		kNone                = 0,
		kKeyword             = 0x4,  // BGSKeyword
		kGlobal              = 0x9,  // TESGlobal
		kFaction             = 0xB,  // TESFaction
		kMagicEffect         = 0x12, // EffectSetting
		kScript              = 0x13, // Script
		kEnchantment         = 0x15, // EnchantmentItem
		kSpell               = 0x16, // SpellItem
		kScroll              = 0x17, // ScrollItem
		kArmor               = 0x1A, // TESObjectARMO
		kBook                = 0x1B, // TESObjectBOOK
		kContainer           = 0x1C, // TESObjectCONT
		kDoor                = 0x1D, // TESObjectDOOR
		kLight               = 0x1F, // TESObjectLIGH
		kStatic              = 0x22, // TESObjectSTAT
		kTree                = 0x26, // TESObjectTREE
		kFlora               = 0x27, // TESFlora
		kFurniture           = 0x28, // TESFurniture
		kWeapon              = 0x29, // TESObjectWEAP
		kAmmunition          = 0x2A, // TESAmmo
		kNPC                 = 0x2B, // TESNPC
		kConstructibleObject = 0x31, // BGSConstructibleObject
		kProjectile          = 0x32, // BGSProjectile
		kSoulGem             = 0x34, // TESSoulGem
		kCell                = 0x3C, // TESObjectCELL
		kReference           = 0x3D, // TESObjectREFR
		kActor               = 0x3E, // Actor, Character, PlayerCharacter
		kImpactDataSet       = 0x65, // BGSImpactDataSet
		kShout               = 0x77, // TESShout
		kTotal               = 0x8A
	};
}
