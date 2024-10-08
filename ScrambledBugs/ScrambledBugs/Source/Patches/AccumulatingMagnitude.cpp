#include "PrecompiledHeader.h"

#include "Patches/AccumulatingMagnitude.h"

#include "Shared/Utility/Conversion.h"
#include "Shared/Utility/Memory.h"



namespace ScrambledBugs::Patches
{
	/*
	* Swap the maximum magnitude and the accumulation rate (magnitude) of accumulating magnitude magic effects
	* The power of accumulating magnitude magic effects then affects the maximum magnitude and not the accumulation rate (magnitude)
	*/
	void AccumulatingMagnitude::Load(bool& accumulatingMagnitude)
	{
		AccumulatingMagnitude::instantiate_ =
			reinterpret_cast<decltype(AccumulatingMagnitude::instantiate_)*>(Skyrim::Addresses::ActiveEffectFactory::InstantiateFunctions())[Utility::Conversion::ToUnderlying(Skyrim::EffectArchetypes::ArchetypeID::kAccumulatingMagnitude)];

		reinterpret_cast<decltype(AccumulatingMagnitude::Instantiate)**>(Skyrim::Addresses::ActiveEffectFactory::InstantiateFunctions())[Utility::Conversion::ToUnderlying(Skyrim::EffectArchetypes::ArchetypeID::kAccumulatingMagnitude)] =
			std::addressof(AccumulatingMagnitude::Instantiate);

		Utility::Memory::SafeWriteVirtualFunction(Skyrim::Addresses::FindMaxMagnitudeVisitor::VirtualFunctionTable(), 0x1, reinterpret_cast<std::uintptr_t>(std::addressof(AccumulatingMagnitude::FunctionCallOperator)));
		Utility::Memory::SafeWriteVirtualFunction(Skyrim::Addresses::AccumulatingValueModifierEffect::VirtualFunctionTable(), 0x1D, reinterpret_cast<std::uintptr_t>(std::addressof(AccumulatingMagnitude::UpdateActorValue)));
	}

	float AccumulatingMagnitude::FindMaximumWardPower(Skyrim::MagicTarget* magicTarget, Skyrim::ActiveEffect* finishedActiveEffect)
	{
		Skyrim::FindMaxMagnitudeVisitor findMaximumMagnitudeVisitor;

		findMaximumMagnitudeVisitor.finishedActiveEffect = finishedActiveEffect;
		findMaximumMagnitudeVisitor.maximumMagnitude     = -1.0F;

		magicTarget->ForEachActiveEffect(findMaximumMagnitudeVisitor);

		return findMaximumMagnitudeVisitor.maximumMagnitude;
	}

	Skyrim::ForEachResult AccumulatingMagnitude::FunctionCallOperator(Skyrim::FindMaxMagnitudeVisitor* findMaximumMagnitudeVisitor, Skyrim::ActiveEffect* activeEffect)
	{
		// findMaximumMagnitudeVisitor != nullptr

		if (!activeEffect)
		{
			return Skyrim::ForEachResult::kContinue;
		}

		if (activeEffect == findMaximumMagnitudeVisitor->finishedActiveEffect)
		{
			return Skyrim::ForEachResult::kContinue;
		}

		if (activeEffect->GetEffectSetting()->effectArchetype != Skyrim::EffectArchetypes::ArchetypeID::kAccumulatingMagnitude)
		{
			return Skyrim::ForEachResult::kContinue;
		}

		auto* accumulatingValueModifierEffect = static_cast<Skyrim::AccumulatingValueModifierEffect*>(activeEffect);

		if (accumulatingValueModifierEffect->actorValue != Skyrim::ActorValue::kWardPower)
		{
			return Skyrim::ForEachResult::kContinue;
		}

		/* Get the accumulation rate instead of the maximum magnitude */
		auto accumulationRate = accumulatingValueModifierEffect->GetCurrentMagnitude();

		if (accumulationRate > findMaximumMagnitudeVisitor->maximumMagnitude)
		{
			findMaximumMagnitudeVisitor->maximumMagnitude = accumulationRate;
		}

		return Skyrim::ForEachResult::kContinue;
	}

	Skyrim::AccumulatingValueModifierEffect* AccumulatingMagnitude::Instantiate(Skyrim::Actor* caster, Skyrim::MagicItem* magicItem, Skyrim::EffectItem* effectItem)
	{
		// accumulatingValueModifierEffect != nullptr

		auto* accumulatingValueModifierEffect = AccumulatingMagnitude::instantiate_(caster, magicItem, effectItem);

		/* Swap the accumulation rate and the maximum magnitude */
		std::swap(accumulatingValueModifierEffect->magnitude, accumulatingValueModifierEffect->maximumMagnitude);

		return accumulatingValueModifierEffect;
	}

	void AccumulatingMagnitude::UpdateActorValue(Skyrim::AccumulatingValueModifierEffect* accumulatingValueModifierEffect, float frameTime)
	{
		// accumulatingValueModifierEffect != nullptr

		if (accumulatingValueModifierEffect->holdDuration <= 0.0F)
		{
			auto* magicTarget = accumulatingValueModifierEffect->magicTarget;

			if (magicTarget)
			{
				auto* targetActor = magicTarget->GetMagicTargetAsActor();

				if (targetActor)
				{
					/* Swap the accumulation rate and the maximum magnitude */
					auto maximumMagnitude = accumulatingValueModifierEffect->GetCurrentMagnitude();
					auto accumulationRate = accumulatingValueModifierEffect->maximumMagnitude * frameTime;

					if (accumulatingValueModifierEffect->actorValue == Skyrim::ActorValue::kWardPower)
					{
						/* Update maximum ward power */
						auto maximumWardPower = AccumulatingMagnitude::FindMaximumWardPower(magicTarget, nullptr);
						targetActor->SetMaximumWardPower(maximumWardPower);

						if (maximumWardPower > 0.0F)
						{
							maximumMagnitude = maximumWardPower;
						}
					}

					auto currentMagnitude = targetActor->GetActorValue(accumulatingValueModifierEffect->actorValue);

					if (currentMagnitude + accumulationRate > maximumMagnitude)
					{
						accumulationRate = maximumMagnitude - currentMagnitude;
					}

					accumulatingValueModifierEffect->ModifyActorValue(targetActor, accumulationRate, Skyrim::ActorValue::kNone);
					accumulatingValueModifierEffect->currentMagnitude += accumulationRate;
				}
			}
		}
		else
		{
			accumulatingValueModifierEffect->holdDuration -= frameTime;
		}
	}

	decltype(AccumulatingMagnitude::Instantiate)* AccumulatingMagnitude::instantiate_{ nullptr };
}
