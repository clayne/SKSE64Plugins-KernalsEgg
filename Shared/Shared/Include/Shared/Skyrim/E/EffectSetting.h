#pragma once

#include "Shared/PrecompiledHeader.h"

#include "Shared/Skyrim/A/ActorValue.h"
#include "Shared/Skyrim/B/BGSKeywordForm.h"
#include "Shared/Skyrim/B/BGSMenuDisplayObject.h"
#include "Shared/Skyrim/B/BSFixedString.h"
#include "Shared/Skyrim/B/BSSimpleList.h"
#include "Shared/Skyrim/E/EffectArchetypes.h"
#include "Shared/Skyrim/M/MagicSystem.h"
#include "Shared/Skyrim/S/SoundLevel.h"
#include "Shared/Skyrim/T/TESCondition.h"
#include "Shared/Skyrim/T/TESForm.h"
#include "Shared/Skyrim/T/TESFullName.h"
#include "Shared/Utility/Enumeration.h"



namespace Skyrim
{
	class BGSArtObject;
	class BGSExplosion;
	class BGSImpactDataSet;
	class BGSPerk;
	class BGSProjectile;
	class BGSReferenceEffect;
	class SpellItem;
	class TESEffectShader;
	class TESImageSpaceModifier;
	class TESObjectLIGH;

	class EffectSetting :
		public TESForm,              // 0
		public TESFullName,          // 20
		public BGSMenuDisplayObject, // 30
		public BGSKeywordForm        // 40
	{
	public:
		enum class Flags : std::uint32_t
		{
			kNone                      = 0,
			kHostile                   = 1U << 0,
			kRecover                   = 1U << 1,
			kDetrimental               = 1U << 2,
			kSnapToNavigationMesh      = 1U << 3,
			kNoHitEvent                = 1U << 4,
			kDispelEffectsWithKeywords = 1U << 8,
			kNoDuration                = 1U << 9,
			kNoMagnitude               = 1U << 10,
			kNoArea                    = 1U << 11,
			kFXPersist                 = 1U << 12,
			kGoryVisuals               = 1U << 14,
			kHideInUI                  = 1U << 15,
			kNoRecast                  = 1U << 17,
			kPowerAffectsMagnitude     = 1U << 21,
			kPowerAffectsDuration      = 1U << 22,
			kPainless                  = 1U << 26,
			kNoHitEffect               = 1U << 27,
			kNoDeathDispel             = 1U << 28
		};
		static_assert(sizeof(Flags) == 0x4);

		// Override
		virtual ~EffectSetting() override; // 0

		// Override (TESForm)
		virtual void ClearData() override;         // 5
		virtual bool Load(TESFile* file) override; // 6
		virtual void Unknown13(TESForm*) override; // 13
		virtual void Unknown2F(TESForm*) override; // 2F
		virtual void Unknown39(TESForm*) override; // 39

		// Override (BGSKeywordForm)
		virtual bool HasKeyword(const BGSKeyword* keyword) const override; // 4

		// Non-member functions
		static float GetCost(float baseCost, std::int32_t area, std::int32_t duration, float magnitude, bool aimed, bool concentration);

		// Member variables
		std::uint64_t                                                      unknown58;                   // 58
		std::uint64_t                                                      unknown60;                   // 60
		Utility::Enumeration<Flags, std::uint32_t>                         effectSettingFlags;          // 68
		float                                                              baseCost;                    // 6C
		std::uint64_t                                                      unknown70;                   // 70
		Utility::Enumeration<ActorValue, std::uint32_t>                    magicSkill;                  // 78
		Utility::Enumeration<ActorValue, std::uint32_t>                    resistanceActorValue;        // 7C
		std::uint64_t                                                      unknown80;                   // 80
		TESObjectLIGH*                                                     castingLight;                // 88
		float                                                              taperWeight;                 // 90
		std::uint32_t                                                      padding94;                   // 94
		TESEffectShader*                                                   hitEffectShader;             // 98
		TESEffectShader*                                                   enchantEffectShader;         // A0
		std::uint32_t                                                      minimumSkillLevel;           // A8
		std::uint32_t                                                      spellmakingArea;             // AC
		float                                                              spellmakingCastingTime;      // B0
		float                                                              taperCurve;                  // B4
		float                                                              taperDuration;               // B8
		float                                                              secondaryActorValueWeight;   // BC
		Utility::Enumeration<EffectArchetypes::ArchetypeID, std::uint32_t> effectArchetype;             // C0
		Utility::Enumeration<ActorValue, std::uint32_t>                    primaryActorValue;           // C4
		BGSProjectile*                                                     projectile;                  // C8
		BGSExplosion*                                                      explosion;                   // D0
		Utility::Enumeration<MagicSystem::CastingType, std::uint32_t>      castingType;                 // D8
		Utility::Enumeration<MagicSystem::Delivery, std::uint32_t>         delivery;                    // DC
		Utility::Enumeration<ActorValue, std::uint32_t>                    secondaryActorValue;         // E0
		std::uint32_t                                                      unknownE4;                   // E4
		BGSArtObject*                                                      castingArtObject;            // E8
		BGSArtObject*                                                      hitEffectArtObject;          // F0
		BGSImpactDataSet*                                                  impactDataSet;               // F8
		float                                                              skillUsageMultiplier;        // 100
		std::uint32_t                                                      padding104;                  // 104
		std::uint64_t                                                      unknown108;                  // 108
		float                                                              dualCastingScale;            // 110
		std::uint32_t                                                      padding114;                  // 114
		BGSArtObject*                                                      enchantArtObject;            // 118
		BGSReferenceEffect*                                                hitReferenceEffect;          // 120
		BGSReferenceEffect*                                                enchantReferenceEffect;      // 128
		SpellItem*                                                         equipAbility;                // 130
		TESImageSpaceModifier*                                             imageSpaceModifier;          // 138
		BGSPerk*                                                           perkToApply;                 // 140
		Utility::Enumeration<SoundLevel, std::uint32_t>                    castingSoundLevel;           // 148
		float                                                              scriptEffectAIDataScore;     // 14C
		float                                                              scriptEffectAIDataDelayTime; // 150
		std::uint32_t                                                      padding154;                  // 154
		BSSimpleList<EffectSetting*>                                       counterEffectSettings;       // 158
		std::uint64_t                                                      unknown168;                  // 168
		std::uint64_t                                                      unknown170;                  // 170
		std::uint64_t                                                      unknown178;                  // 178
		BSFixedString                                                      magicItemDescription;        // 180
		std::uint64_t                                                      unknown188;                  // 188
		TESCondition                                                       conditions;                  // 190
	};
	static_assert(offsetof(EffectSetting, effectSettingFlags) == 0x68);
	static_assert(offsetof(EffectSetting, baseCost) == 0x6C);
	static_assert(offsetof(EffectSetting, magicSkill) == 0x78);
	static_assert(offsetof(EffectSetting, resistanceActorValue) == 0x7C);
	static_assert(offsetof(EffectSetting, castingLight) == 0x88);
	static_assert(offsetof(EffectSetting, taperWeight) == 0x90);
	static_assert(offsetof(EffectSetting, hitEffectShader) == 0x98);
	static_assert(offsetof(EffectSetting, enchantEffectShader) == 0xA0);
	static_assert(offsetof(EffectSetting, minimumSkillLevel) == 0xA8);
	static_assert(offsetof(EffectSetting, spellmakingArea) == 0xAC);
	static_assert(offsetof(EffectSetting, spellmakingCastingTime) == 0xB0);
	static_assert(offsetof(EffectSetting, taperCurve) == 0xB4);
	static_assert(offsetof(EffectSetting, taperDuration) == 0xB8);
	static_assert(offsetof(EffectSetting, secondaryActorValueWeight) == 0xBC);
	static_assert(offsetof(EffectSetting, effectArchetype) == 0xC0);
	static_assert(offsetof(EffectSetting, primaryActorValue) == 0xC4);
	static_assert(offsetof(EffectSetting, projectile) == 0xC8);
	static_assert(offsetof(EffectSetting, explosion) == 0xD0);
	static_assert(offsetof(EffectSetting, castingType) == 0xD8);
	static_assert(offsetof(EffectSetting, delivery) == 0xDC);
	static_assert(offsetof(EffectSetting, secondaryActorValue) == 0xE0);
	static_assert(offsetof(EffectSetting, castingArtObject) == 0xE8);
	static_assert(offsetof(EffectSetting, hitEffectArtObject) == 0xF0);
	static_assert(offsetof(EffectSetting, impactDataSet) == 0xF8);
	static_assert(offsetof(EffectSetting, skillUsageMultiplier) == 0x100);
	static_assert(offsetof(EffectSetting, dualCastingScale) == 0x110);
	static_assert(offsetof(EffectSetting, enchantArtObject) == 0x118);
	static_assert(offsetof(EffectSetting, hitReferenceEffect) == 0x120);
	static_assert(offsetof(EffectSetting, enchantReferenceEffect) == 0x128);
	static_assert(offsetof(EffectSetting, equipAbility) == 0x130);
	static_assert(offsetof(EffectSetting, imageSpaceModifier) == 0x138);
	static_assert(offsetof(EffectSetting, perkToApply) == 0x140);
	static_assert(offsetof(EffectSetting, castingSoundLevel) == 0x148);
	static_assert(offsetof(EffectSetting, scriptEffectAIDataScore) == 0x14C);
	static_assert(offsetof(EffectSetting, scriptEffectAIDataDelayTime) == 0x150);
	static_assert(offsetof(EffectSetting, counterEffectSettings) == 0x158);
	static_assert(offsetof(EffectSetting, magicItemDescription) == 0x180);
	static_assert(offsetof(EffectSetting, conditions) == 0x190);
	static_assert(sizeof(EffectSetting) == 0x198);
}
