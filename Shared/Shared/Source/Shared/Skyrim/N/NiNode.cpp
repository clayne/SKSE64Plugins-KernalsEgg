#include "Shared/PrecompiledHeader.h"

#include "Shared/Skyrim/N/NiNode.h"

#include "Shared/Skyrim/Addresses.h"
#include "Shared/Utility/TypeTraits.h"



namespace Skyrim
{
	NiNode* NiNode::CreateObject()
	{
		auto* function{ reinterpret_cast<decltype(NiNode::CreateObject)*>(
			Addresses::NiNode::CreateObject()) };

		return function();
	}

	std::uint32_t NiNode::AddDecal(const BGSDecalManager::AdditionData& additionData)
	{
		auto* function{ reinterpret_cast<
			Utility::TypeTraits::MakeFunctionPointer<decltype(&NiNode::AddDecal)>::type>(
			Addresses::NiNode::AddDecal()) };

		return function(this, additionData);
	}
}
