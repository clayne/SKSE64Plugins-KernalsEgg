#pragma once

#include "PrecompiledHeader.h"



namespace ScrambledBugs::Patterns
{
	namespace Fixes
	{
		namespace EnchantmentCost
		{
			bool Compare();
		}

		namespace HarvestedFlags
		{
			bool SetEmpty();
		}

		namespace ImpactEffectCrash
		{
			bool DecalApplier();
			bool UpdateDecals();
		}

		namespace KillCamera
		{
			bool HasWeapon();
		}

		namespace ProjectileFadeDuration
		{
			bool HasFaded();
			bool HasProcessedImpacts();
		}

		namespace TerrainDecals
		{
			bool FreeCellMopp();
		}

		namespace TrainingMenu
		{
			bool GetPermanentActorValue();
		}
	}

	namespace Patches
	{
		namespace AlreadyCaughtPickpocketing
		{
			bool IsAngryWithPlayer();
			bool HasBeenPickpocketed();
		}

		namespace AttachHitEffectArt
		{
			bool SetCastPermanentMagicFunctorFlags();
		}

		namespace CloakHitEffects
		{
			bool IsNotCostliestEffect();
		}

		namespace LockpickingExperience
		{
			bool HasNotBeenUnlocked();
		}

		namespace PerkEntryPoints
		{
			namespace ApplyMultipleSpells
			{
				bool ApplyBashingSpell();
				bool ApplyCombatHitSpell();
				bool ApplyCombatHitSpellArrowProjectile();
				bool ApplyReanimateSpell();
				bool ApplySneakingSpell();
				bool ApplyWeaponSwingSpell();
			}

			namespace CastSpells
			{
				bool ApplyBashingSpell();
				bool ApplyCombatHitSpell();
				bool ApplyCombatHitSpellArrowProjectile();
				bool ApplyReanimateSpell();
				bool ApplyWeaponSwingSpell();
			}
		}

		namespace PowerAttackStamina
		{
			bool GetAttackStaminaActor();
			bool GetAttackStaminaPlayerCharacter();
			bool HasStaminaActor();
			bool HasStaminaPlayerCharacter();
		}

		namespace ReflectDamage
		{
			bool CompareReflectDamage();
		}

		namespace SteepSlopes
		{
			bool GetScale();
		}
	}
}
