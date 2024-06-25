#include "PrecompiledHeader.h"

#include "Fixes/WeaponCharge.h"

#include "Addresses.h"
#include "Shared/Utility/Memory.h"



namespace ScrambledBugs::Fixes
{
	void WeaponCharge::Fix(bool& weaponCharge)
	{
		Utility::Memory::SafeWriteAbsoluteJump(
			Addresses::Fixes::WeaponCharge::UpdateEquippedEnchantmentCharge,
			reinterpret_cast<std::uintptr_t>(std::addressof(WeaponCharge::UpdateEquippedEnchantmentCharge)));
	}

	void WeaponCharge::UpdateEquippedEnchantmentCharge(Skyrim::Actor* actor, Skyrim::TESBoundObject* boundObject, Skyrim::ExtraDataList* extraDataList, bool leftHand)
	{
		if (!boundObject)
		{
			return;
		}

		auto* player = Skyrim::PlayerCharacter::GetSingleton();

		if (actor == player)
		{
			player->ResetInsufficientWeaponChargeMessage(leftHand);
		}

		auto* enchantment = boundObject->GetEnchantment(extraDataList);

		if (!enchantment)
		{
			return;
		}

		if (enchantment->GetCastingType() == Skyrim::MagicSystem::CastingType::kConstantEffect)
		{
			return;
		}

		auto castingSource  = leftHand ? Skyrim::MagicSystem::CastingSource::kLeftHand : Skyrim::MagicSystem::CastingSource::kRightHand;
		auto costActorValue = enchantment->GetCostActorValue(castingSource);

		if (costActorValue != Skyrim::ActorValue::kNone)
		{
			actor->RemoveActorValueModifiers(costActorValue);

			auto maximumCharge = boundObject->GetMaximumCharge(extraDataList);
			actor->SetActorValue(costActorValue, maximumCharge);

			if (extraDataList && extraDataList->HasExtraData(Skyrim::ExtraDataType::kCharge))
			{
				auto charge = extraDataList->GetCharge();
				actor->RestoreActorValue(Skyrim::ActorValueModifier::kDamage, costActorValue, -(maximumCharge - charge));
			}
		}

		actor->SetSelectedSpell(castingSource, enchantment);
	}
}
