#pragma once

#include "PrecompiledHeader.h"



namespace ScrambledBugs::Patches
{
	class StaffExperience
	{
	public:
		static void Load(bool& staffExperience, bool& ignoreEnchantmentCost);

	private:
		static bool GetSkillUsageDataEnchantment(Skyrim::EnchantmentItem* enchantmentItem, Skyrim::MagicItem::SkillUsageData& skillUsageData);
		static bool GetSkillUsageDataStaffEnchantment(Skyrim::EnchantmentItem* enchantmentItem, Skyrim::MagicItem::SkillUsageData& skillUsageData);

		static bool                                                     ignoreEnchantmentCost_;
		static decltype(StaffExperience::GetSkillUsageDataEnchantment)* getSkillUsageDataEnchantment_;
	};
}
