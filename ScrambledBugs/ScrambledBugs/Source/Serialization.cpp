#include "PrecompiledHeader.h"

#include "Serialization.h"

#include "Settings.h"



namespace ScrambledBugs
{
	bool Serialization::EnchantmentCost::LoadGame(SKSE::SerializationInterface* serializationInterface)
	{
		serializationInterface->ReadRecordData(*this);

		if (!serializationInterface->ResolveFormID(this->formID, this->formID))
		{
			SPDLOG_ERROR("Failed to resolve form ID, 0x{:X}.", this->formID);

			return false;
		}

		auto* enchantmentItem = static_cast<Skyrim::EnchantmentItem*>(Skyrim::TESDataHandler::GetForm(this->formID));

		if (!enchantmentItem || enchantmentItem->formType != Skyrim::FormType::kEnchantment)
		{
			SPDLOG_ERROR("Enchantment not found, form ID 0x{:X}.", this->formID);

			return false;
		}

		auto* enchantmentItemData = reinterpret_cast<Skyrim::EnchantmentItem::Data*>(enchantmentItem->GetData());

		if (!enchantmentItemData)
		{
			SPDLOG_ERROR("Data not found, form ID 0x{:X}.", this->formID);

			return false;
		}

		enchantmentItemData->enchantmentCost      = this->enchantmentCost;
		enchantmentItemData->enchantmentItemFlags = this->enchantmentItemFlags;

		return true;
	}

	bool Serialization::EnchantmentCost::SaveGame(SKSE::SerializationInterface* serializationInterface, Skyrim::MagicItem* magicItem)
	{
		if (!magicItem || magicItem->formType != Skyrim::FormType::kEnchantment)
		{
			SPDLOG_ERROR("Enchantment not found.");

			return false;
		}

		auto*       enchantmentItem     = static_cast<Skyrim::EnchantmentItem*>(magicItem);
		const auto* enchantmentItemData = reinterpret_cast<const Skyrim::EnchantmentItem::Data*>(enchantmentItem->GetConstantData());

		if (!enchantmentItemData)
		{
			SPDLOG_ERROR("Data not found.");

			return false;
		}

		this->formID               = enchantmentItem->formID;
		this->enchantmentCost      = enchantmentItemData->enchantmentCost;
		this->enchantmentItemFlags = enchantmentItemData->enchantmentItemFlags;

		serializationInterface->WriteRecord(EnchantmentCost::kType, EnchantmentCost::kVersion, *this);

		return true;
	}

	void Serialization::LoadGame(SKSE::SerializationInterface* serializationInterface)
	{
		SPDLOG_INFO("Loading Game...");

		const auto& settings = Settings::GetSingleton();

		auto*                   createdObjectManager = Skyrim::BGSCreatedObjectManager::GetSingleton();
		Skyrim::BSSpinLockGuard lockGuard(createdObjectManager->lock);

		std::uint32_t type, version, length;

		while (serializationInterface->GetNextRecordInformation(type, version, length))
		{
			switch (type)
			{
				case EnchantmentCost::kType:
				{
					if (!settings.fixes.enchantmentCost)
					{
						continue;
					}

					if (version != EnchantmentCost::kVersion)
					{
						SPDLOG_ERROR("{} version mismatch, {}.", type, version);

						continue;
					}

					if (length != sizeof(EnchantmentCost))
					{
						SPDLOG_ERROR("{} size mismatch, 0x{:X}.", type, length);

						continue;
					}

					EnchantmentCost().LoadGame(serializationInterface);

					break;
				}
				default:
				{
					SPDLOG_ERROR("Type mismatch, {}.", type);

					break;
				}
			}
		}

		SPDLOG_INFO("Loaded Game.");
	}

	void Serialization::SaveGame(SKSE::SerializationInterface* serializationInterface)
	{
		SPDLOG_INFO("Saving Game...");

		const auto& settings = Settings::GetSingleton();

		if (settings.fixes.enchantmentCost)
		{
			auto*                   createdObjectManager = Skyrim::BGSCreatedObjectManager::GetSingleton();
			Skyrim::BSSpinLockGuard lockGuard(createdObjectManager->lock);

			for (const auto& armorEnchantmentItem : createdObjectManager->armorEnchantmentItems)
			{
				EnchantmentCost().SaveGame(serializationInterface, armorEnchantmentItem.magicItem);
			}

			for (const auto& weaponEnchantmentItem : createdObjectManager->weaponEnchantmentItems)
			{
				EnchantmentCost().SaveGame(serializationInterface, weaponEnchantmentItem.magicItem);
			}
		}

		SPDLOG_INFO("Saved Game.");
	}
}
