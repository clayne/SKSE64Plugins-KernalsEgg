#pragma once

#include "Shared/PrecompiledHeader.h"

#include "Shared/Skyrim/B/BSIntrusiveRefCounted.h"
#include "Shared/Skyrim/B/BSTArray.h"
#include "Shared/Skyrim/B/BSTSmartPointer.h"
#include "Shared/Skyrim/C/CraftingSubMenu.h"
#include "Shared/Skyrim/F/FormType.h"
#include "Shared/Skyrim/M/MagicItemTraversalFunctor.h"
#include "Shared/Utility/Enumeration.h"



namespace Skyrim
{
	class EnchantmentItem;
	class InventoryEntryData;
	class TESBoundObject;

	namespace CraftingSubMenus
	{
		class EnchantConstructMenu :
			public CraftingSubMenu // 0
		{
		public:
			enum class Category : std::uint32_t
			{
				kDisenchant  = 0,
				kSoulGem     = 1,
				kItem        = 2,
				kEnchantment = 3
			};
			static_assert(sizeof(Category) == 0x4);

			enum class FilterFlag : std::uint32_t
			{
				kNone             = 0,
				kEnchantWeapon    = 1U << 0,
				kDisenchantWeapon = 1U << 1,
				kEnchantArmor     = 1U << 2,
				kDisenchantArmor  = 1U << 3,
				kEffectWeapon     = 1U << 4,
				kEffectArmor      = 1U << 5,
				kSoulGem          = 1U << 6
			};
			static_assert(sizeof(FilterFlag) == 0x4);

			class CategoryListEntry :
				public BSIntrusiveRefCounted // 0
			{
			public:
				// Add
				virtual ~CategoryListEntry();                  // 0
				virtual void Unknown1(CategoryListEntry*);     // 1
				virtual void Unknown2(CategoryListEntry*);     // 2
				virtual void Unknown3(CategoryListEntry*) = 0; // 3
				virtual void Unknown4(CategoryListEntry*);     // 4

				// Member variables
				Utility::Enumeration<FilterFlag, std::uint32_t> filterFlag; // C
				bool                                            selected;   // 10
				bool                                            enabled;    // 11
				std::uint16_t                                   padding12;  // 12
				std::uint32_t                                   padding14;  // 14
			};
			static_assert(offsetof(CategoryListEntry, filterFlag) == 0xC);
			static_assert(offsetof(CategoryListEntry, selected) == 0x10);
			static_assert(offsetof(CategoryListEntry, enabled) == 0x11);
			static_assert(sizeof(CategoryListEntry) == 0x18);

			class EnchantmentEntry :
				public CategoryListEntry // 0
			{
			public:
				// Override
				virtual ~EnchantmentEntry() override; // 0

				// Override (CategoryListEntry)
				virtual void Unknown1(CategoryListEntry*) override; // 1
				virtual void Unknown2(CategoryListEntry*) override; // 2
				virtual void Unknown3(CategoryListEntry*) override; // 3
				virtual void Unknown4(CategoryListEntry*) override; // 4

				// Member variables
				EnchantmentItem* enchantmentItem; // 18
				float            power;           // 20
				float            maximumPower;    // 24
			};
			static_assert(offsetof(EnchantmentEntry, enchantmentItem) == 0x18);
			static_assert(offsetof(EnchantmentEntry, power) == 0x20);
			static_assert(offsetof(EnchantmentEntry, maximumPower) == 0x24);
			static_assert(sizeof(EnchantmentEntry) == 0x28);

			class ItemChangeEntry :
				public CategoryListEntry // 0
			{
			public:
				// Override
				virtual ~ItemChangeEntry() override; // 0

				// Override (CategoryListEntry)
				virtual void Unknown1(CategoryListEntry*) override; // 1
				virtual void Unknown2(CategoryListEntry*) override; // 2
				virtual void Unknown3(CategoryListEntry*) override; // 3
				virtual void Unknown4(CategoryListEntry*) override; // 4

				// Member variables
				InventoryEntryData* inventoryEntryData; // 18
			};
			static_assert(offsetof(ItemChangeEntry, inventoryEntryData) == 0x18);
			static_assert(sizeof(ItemChangeEntry) == 0x20);

			class CreateEffectFunctor :
				public MagicItemTraversalFunctor // 0
			{
			public:
				// Override
				virtual ~CreateEffectFunctor() override; // 0

				// Override (MagicItemTraversalFunctor)
				virtual ForEachResult operator()(EffectItem* effectItem) override; // 1

				// Member variables
				BSTArray<EffectItem>                          effectItems;         // 10
				EffectItem*                                   costliestEffectItem; // 28
				EnchantmentEntry*                             enchantmentEntry;    // 30
				EnchantmentItem*                              enchantmentItem;     // 38
				Utility::Enumeration<FormType, std::uint32_t> formType;            // 40
				std::uint32_t                                 padding44;           // 44
				TESBoundObject*                               boundObject;         // 48
				float                                         effectiveness;       // 50
				std::uint32_t                                 padding54;           // 54
			};
			static_assert(offsetof(CreateEffectFunctor, effectItems) == 0x10);
			static_assert(offsetof(CreateEffectFunctor, costliestEffectItem) == 0x28);
			static_assert(offsetof(CreateEffectFunctor, enchantmentEntry) == 0x30);
			static_assert(offsetof(CreateEffectFunctor, enchantmentItem) == 0x38);
			static_assert(offsetof(CreateEffectFunctor, formType) == 0x40);
			static_assert(offsetof(CreateEffectFunctor, boundObject) == 0x48);
			static_assert(offsetof(CreateEffectFunctor, effectiveness) == 0x50);
			static_assert(sizeof(CreateEffectFunctor) == 0x58);

			struct Selections
			{
			public:
				// Member variables
				BSTSmartPointer<ItemChangeEntry>            item;                    // 0
				BSTSmartPointer<ItemChangeEntry>            soulGem;                 // 8
				BSTArray<BSTSmartPointer<EnchantmentEntry>> enchantments;            // 10
				std::uint32_t                               maximumEnchantmentCount; // 28
				std::uint32_t                               padding2C;               // 2C
			};
			static_assert(offsetof(Selections, item) == 0x0);
			static_assert(offsetof(Selections, soulGem) == 0x8);
			static_assert(offsetof(Selections, enchantments) == 0x10);
			static_assert(offsetof(Selections, maximumEnchantmentCount) == 0x28);
			static_assert(sizeof(Selections) == 0x30);

			// Override
			virtual ~EnchantConstructMenu() override; // 0

			// Override (CraftingSubMenu)
			virtual void Accept(CallbackProcessor* callbackProcessor) override; // 1
			virtual void Unknown4(CraftingSubMenu*) override;                   // 4
			virtual void Unknown5(CraftingSubMenu*) override;                   // 5
			virtual void Unknown7(CraftingSubMenu*) override;                   // 7

			// Member variables
			Utility::Enumeration<FilterFlag, std::uint32_t> disenchantFilterFlag;  // 100
			Utility::Enumeration<FilterFlag, std::uint32_t> dividerFilterFlag;     // 104
			Utility::Enumeration<FilterFlag, std::uint32_t> itemFilterFlag;        // 108
			Utility::Enumeration<FilterFlag, std::uint32_t> enchantmentFilterFlag; // 10C
			Utility::Enumeration<FilterFlag, std::uint32_t> soulGemFilterFlag;     // 110
			std::uint32_t                                   padding114;            // 114
			BSTArray<BSTSmartPointer<CategoryListEntry>>    categoryListEntries;   // 118
			std::uint64_t                                   unknown130;            // 130
			std::uint64_t                                   unknown138;            // 138
			std::uint64_t                                   unknown140;            // 140
			std::uint64_t                                   unknown148;            // 148
			std::uint64_t                                   unknown150;            // 150
			std::uint64_t                                   unknown158;            // 158
			std::uint64_t                                   unknown160;            // 160
			std::uint64_t                                   unknown168;            // 168
			Selections                                      selections;            // 170
			std::uint64_t                                   unknown1A0;            // 1A0
			CreateEffectFunctor                             createEffectFunctor;   // 1A8
			std::uint64_t                                   unknown200;            // 200
			std::uint32_t                                   unknown208;            // 208
			Utility::Enumeration<Category, std::uint32_t>   currentCategory;       // 20C
			Utility::Enumeration<FilterFlag, std::uint32_t> enabledFilters;        // 210
			std::uint32_t                                   unknown214;            // 214
			std::uint64_t                                   unknown218;            // 218
		};
		static_assert(offsetof(EnchantConstructMenu, disenchantFilterFlag) == 0x100);
		static_assert(offsetof(EnchantConstructMenu, dividerFilterFlag) == 0x104);
		static_assert(offsetof(EnchantConstructMenu, itemFilterFlag) == 0x108);
		static_assert(offsetof(EnchantConstructMenu, enchantmentFilterFlag) == 0x10C);
		static_assert(offsetof(EnchantConstructMenu, soulGemFilterFlag) == 0x110);
		static_assert(offsetof(EnchantConstructMenu, categoryListEntries) == 0x118);
		static_assert(offsetof(EnchantConstructMenu, selections) == 0x170);
		static_assert(offsetof(EnchantConstructMenu, createEffectFunctor) == 0x1A8);
		static_assert(offsetof(EnchantConstructMenu, currentCategory) == 0x20C);
		static_assert(offsetof(EnchantConstructMenu, enabledFilters) == 0x210);
		static_assert(sizeof(EnchantConstructMenu) == 0x220);
	}
}
