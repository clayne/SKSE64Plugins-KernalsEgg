#pragma once

#include "PrecompiledHeader.h"



namespace ScrambledBugs::Patches
{
	class SteepSlopes
	{
	public:
		static void Load(bool& steepSlopes);

	private:
		static float GetScale(Skyrim::Actor* actor);

		static decltype(SteepSlopes::GetScale)* getScale_;
	};
}
