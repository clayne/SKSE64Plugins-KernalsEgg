#pragma once

#include "PrecompiledHeader.h"



namespace ScrambledBugs::Fixes
{
	class IngredientRespawn
	{
	public:
		static void Load(bool& ingredientRespawn);

	private:
		static void SetEmpty(Skyrim::TESObjectREFR* reference, bool empty);

		static decltype(IngredientRespawn::SetEmpty)* setEmpty_;
	};
}
