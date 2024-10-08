#include "PrecompiledHeader.h"

#include "DecalManager.h"



namespace Trails
{
	void DecalManager::AddDecal(Skyrim::BGSDecalManager* decalManager, const Skyrim::BGSDecalManager::CreationData& creationData, bool forceDecal, Skyrim::BGSDecalGroup* decalGroup)
	{
		decalManager->unknown14 = true;

		static auto* decals = Skyrim::INIPrefSettingCollection::InitializeSetting("bDecals:Decals");

		if (decals->GetBool())
		{
			if (creationData.target3D)
			{
				auto* target3DNode = creationData.target3D->AsNetImmerseNode();

				if (target3DNode)
				{
					static auto* forceAllDecals = Skyrim::INISettingCollection::InitializeSetting("bForceAllDecals:Decals");

					target3DNode->AddDecal(Skyrim::BGSDecalManager::AdditionData{
						.creationData               = std::addressof(creationData),
						.forceDecal                 = forceDecal || forceAllDecals->GetBool(),
						.unknown9                   = creationData.unknownC0 != 0,
						.decalCount                 = decalManager->decalCount,
						.skinDecalCount             = decalManager->skinDecalCount,
						.skinDecalCountCurrentFrame = decalManager->skinDecalCountCurrentFrame,
						.decalCountCurrentFrame     = decalManager->decalCountCurrentFrame,
						.unknown1C                  = 0,
						.decalGroup                 = decalGroup });
				}
			}
		}
	}
}
