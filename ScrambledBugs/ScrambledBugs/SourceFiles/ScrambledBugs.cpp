#include "PCH.h"

#include "Fixes/ActivateFurniture.h"
#include "Fixes/ActorValuePercentage.h"
#include "Fixes/EnchantmentCost.h"
#include "Fixes/HarvestedFlags.h"
#include "Fixes/HitEffectRaceCondition.h"
#include "Fixes/ImpactEffectCrash.h"
#include "Fixes/KillCamera.h"
#include "Fixes/LeftHandPowerAttacks.h"
#include "Fixes/MagicEffectFlags.h"
#include "Fixes/ModArmorWeightPerkEntryPoint.h"
#include "Fixes/QuickShot.h"
#include "Fixes/TerrainDecals.h"
#include "Fixes/TrainingMenu.h"
#include "Fixes/WeaponCharge.h"
#include "Patches/AccumulatingMagnitude.h"
#include "Patches/AlreadyCaughtPickpocketing.h"
#include "Patches/AttachHitEffectArt.h"
#include "Patches/CloakHitEffects.h"
#include "Patches/EquipBestAmmo.h"
#include "Patches/ImproveMultipleEnchantmentEffects.h"
#include "Patches/LeveledCharacters.h"
#include "Patches/LockpickingExperience.h"
#include "Patches/PausedGameHitEffects.h"
#include "Patches/PerkEntryPoints/ApplyMultipleSpells.h"
#include "Patches/PerkEntryPoints/CastSpells.h"
#include "Patches/PoisonResistance.h"
#include "Patches/PowerAttackStamina.h"
#include "Patches/ReflectDamage.h"
#include "Patches/ScrollExperience.h"
#include "Patches/SoulGems.h"
#include "Patches/StaffExperience.h"
#include "Patches/SteepSlopes.h"
#include "Patches/TeammateDifficulty.h"
#include "Serialization.h"
#include "Settings.h"
#include "Shared/Relocation/Module.h"
#include "Shared/SKSE/Interfaces.h"
#include "Shared/Utility/Log.h"
#include "Shared/Utility/Trampoline.h"



void Settings()
{
	auto& settings = ScrambledBugs::Settings::GetSingleton();

	Utility::Log::Information("Initializing...\n{}", settings.Serialize().dump(1, '\t'));

	// Fixes
	if (settings.fixes.activateFurniture)
	{
		ScrambledBugs::Fixes::ActivateFurniture::Fix(settings.fixes.activateFurniture);
	}

	if (settings.fixes.actorValuePercentage)
	{
		ScrambledBugs::Fixes::ActorValuePercentage::Fix(settings.fixes.actorValuePercentage);
	}

	if (settings.fixes.enchantmentCost)
	{
		ScrambledBugs::Fixes::EnchantmentCost::Fix(settings.fixes.enchantmentCost);
	}

	if (settings.fixes.harvestedFlags)
	{
		ScrambledBugs::Fixes::HarvestedFlags::Fix(settings.fixes.harvestedFlags);
	}

	if (settings.fixes.hitEffectRaceCondition)
	{
		ScrambledBugs::Fixes::HitEffectRaceCondition::Fix(settings.fixes.hitEffectRaceCondition);
	}

	if (settings.fixes.impactEffectCrash)
	{
		ScrambledBugs::Fixes::ImpactEffectCrash::Fix(settings.fixes.impactEffectCrash);
	}

	if (settings.fixes.killCamera)
	{
		ScrambledBugs::Fixes::KillCamera::Fix(settings.fixes.killCamera);
	}

	if (settings.fixes.leftHandPowerAttacks)
	{
		ScrambledBugs::Fixes::LeftHandPowerAttacks::Fix(settings.fixes.leftHandPowerAttacks);
	}

	if (settings.fixes.magicEffectFlags)
	{
		ScrambledBugs::Fixes::MagicEffectFlags::Fix(settings.fixes.magicEffectFlags);
	}

	if (settings.fixes.modArmorWeightPerkEntryPoint)
	{
		ScrambledBugs::Fixes::ModArmorWeightPerkEntryPoint::Fix(settings.fixes.modArmorWeightPerkEntryPoint);
	}

	if (settings.fixes.quickShot && settings.fixes.quickShotPlaybackSpeed > 0.0F)
	{
		ScrambledBugs::Fixes::QuickShot::Fix(settings.fixes.quickShot, settings.fixes.quickShotPlaybackSpeed);
	}

	if (settings.fixes.terrainDecals)
	{
		ScrambledBugs::Fixes::TerrainDecals::Fix(settings.fixes.terrainDecals);
	}

	if (settings.fixes.trainingMenu)
	{
		ScrambledBugs::Fixes::TrainingMenu::Fix(settings.fixes.trainingMenu);
	}

	if (settings.fixes.weaponCharge)
	{
		ScrambledBugs::Fixes::WeaponCharge::Fix(settings.fixes.weaponCharge);
	}

	// Patches
	if (settings.patches.accumulatingMagnitude)
	{
		ScrambledBugs::Patches::AccumulatingMagnitude::Patch(settings.patches.accumulatingMagnitude);
	}

	if (settings.patches.alreadyCaughtPickpocketing)
	{
		ScrambledBugs::Patches::AlreadyCaughtPickpocketing::Patch(settings.patches.alreadyCaughtPickpocketing);
	}

	if (settings.patches.attachHitEffectArt)
	{
		ScrambledBugs::Patches::AttachHitEffectArt::Patch(settings.patches.attachHitEffectArt);
	}

	if (settings.patches.cloakHitEffects)
	{
		ScrambledBugs::Patches::CloakHitEffects::Patch(settings.patches.cloakHitEffects);
	}

	if (settings.patches.equipBestAmmo)
	{
		ScrambledBugs::Patches::EquipBestAmmo::Patch(settings.patches.equipBestAmmo);
	}

	if (settings.patches.improveMultipleEnchantmentEffects)
	{
		ScrambledBugs::Patches::ImproveMultipleEnchantmentEffects::Patch(settings.patches.improveMultipleEnchantmentEffects);
	}

	if (settings.patches.leveledCharacters)
	{
		ScrambledBugs::Patches::LeveledCharacters::Patch(settings.patches.leveledCharacters);
	}

	if (settings.patches.lockpickingExperience)
	{
		ScrambledBugs::Patches::LockpickingExperience::Patch(settings.patches.lockpickingExperience);
	}

	if (settings.patches.pausedGameHitEffects)
	{
		ScrambledBugs::Patches::PausedGameHitEffects::Patch(settings.patches.pausedGameHitEffects);
	}

	if (settings.patches.perkEntryPoints.applyMultipleSpells)
	{
		ScrambledBugs::Patches::PerkEntryPoints::ApplyMultipleSpells::Patch(settings.patches.perkEntryPoints.applyMultipleSpells, settings.patches.perkEntryPoints.castSpells);
	}
	else if (settings.patches.perkEntryPoints.castSpells)
	{
		ScrambledBugs::Patches::PerkEntryPoints::CastSpells::Patch(settings.patches.perkEntryPoints.castSpells);
	}

	if (settings.patches.poisonResistance)
	{
		ScrambledBugs::Patches::PoisonResistance::Patch(settings.patches.poisonResistance);
	}

	if (settings.patches.powerAttackStamina)
	{
		ScrambledBugs::Patches::PowerAttackStamina::Patch(settings.patches.powerAttackStamina);
	}

	if (settings.patches.reflectDamage)
	{
		ScrambledBugs::Patches::ReflectDamage::Patch(settings.patches.reflectDamage);
	}

	if (settings.patches.scrollExperience)
	{
		ScrambledBugs::Patches::ScrollExperience::Patch(settings.patches.scrollExperience);
	}

	if (settings.patches.blackSoulGems || settings.patches.underfilledSoulGems)
	{
		ScrambledBugs::Patches::SoulGems::Patch(settings.patches.blackSoulGems, settings.patches.underfilledSoulGems);
	}

	if (settings.patches.staffExperience)
	{
		ScrambledBugs::Patches::StaffExperience::Patch(settings.patches.staffExperience);
	}

	if (settings.patches.steepSlopes)
	{
		ScrambledBugs::Patches::SteepSlopes::Patch(settings.patches.steepSlopes);
	}

	if (settings.patches.teammateDifficulty)
	{
		ScrambledBugs::Patches::TeammateDifficulty::Patch(settings.patches.teammateDifficulty);
	}

	Utility::Log::Information("Initialized.\n{}", settings.Serialize().dump(1, '\t'));

	Utility::Trampoline::GetSingleton().Commit();
}

extern "C" __declspec(dllexport) bool __cdecl SKSEPlugin_Query(SKSE::Interface* queryInterface, SKSE::PluginInfo* pluginInfo)
{
	static std::string name = Relocation::Plugin::GetSingleton().GetPath().stem().string();

	pluginInfo->infoVersion = SKSE::PluginInfo::kVersion;
	pluginInfo->name        = name.c_str();
	pluginInfo->version     = 17;

	if (queryInterface->IsEditor())
	{
		Utility::Log::Critical("Loading in editor.");

		return false;
	}

	auto runtimeVersion = queryInterface->RuntimeVersion();

	if (runtimeVersion < Relocation::Version(1, 5, 39, 0))
	{
		Utility::Log::Critical(
			"Unsupported runtime version, {}.{}.{}.{}.",
			runtimeVersion.major,
			runtimeVersion.minor,
			runtimeVersion.revision,
			runtimeVersion.build);

		return false;
	}

	return true;
}

extern "C" __declspec(dllexport) bool __cdecl SKSEPlugin_Load(SKSE::Interface* loadInterface)
{
	SKSE::Cache::GetSingleton().Initialize(loadInterface);

	Settings();

	auto serializationInterface = SKSE::Cache::GetSingleton().GetSerializationInterface();
	serializationInterface->SetUniqueID(ScrambledBugs::Serialization::kUniqueID);
	serializationInterface->SetSaveCallback(std::addressof(ScrambledBugs::Serialization::Save));
	serializationInterface->SetLoadCallback(std::addressof(ScrambledBugs::Serialization::Load));

	return true;
}
