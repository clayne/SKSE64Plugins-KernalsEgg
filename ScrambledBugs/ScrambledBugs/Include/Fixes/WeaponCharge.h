#pragma once

#include "PrecompiledHeader.h"



namespace ScrambledBugs::Fixes
{
	class WeaponCharge
	{
	public:
		static void Load(bool& weaponCharge);

	private:
		static void RefreshEquippedActorValueCharge(Skyrim::Actor* actor, Skyrim::TESBoundObject* boundObject, Skyrim::ExtraDataList* extraDataList, bool leftHand);
	};
}
