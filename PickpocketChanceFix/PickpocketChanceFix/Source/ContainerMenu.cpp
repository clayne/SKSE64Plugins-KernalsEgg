#include "PrecompiledHeader.h"

#include "ContainerMenu.h"

#include "GFxFunctionHandler.h"
#include "Shared/Utility/Memory.h"



namespace PickpocketChanceFix
{
	void ContainerMenu::Load()
	{
		auto* ui = Skyrim::UI::GetSingleton();

		if (ui)
		{
			auto iterator = ui->menuEntries.find(Skyrim::ContainerMenu::GetMenuName());

			if (iterator != ui->menuEntries.end())
			{
				ContainerMenu::createMenu_    = (*iterator).second.createMenu;
				(*iterator).second.createMenu = std::addressof(ContainerMenu::CreateMenu);
			}
		}

		ContainerMenu::advanceMovie_ = reinterpret_cast<decltype(ContainerMenu::advanceMovie_)>(Utility::Memory::ReadVirtualFunction(Skyrim::Addresses::ContainerMenu::VirtualFunctionTable(), 0x5));

		Utility::Memory::SafeWriteVirtualFunction(Skyrim::Addresses::ContainerMenu::VirtualFunctionTable(), 0x5, reinterpret_cast<std::uintptr_t>(std::addressof(ContainerMenu::AdvanceMovie)));
	}

	Skyrim::IMenu* ContainerMenu::CreateMenu()
	{
		auto* containerMenu = static_cast<Skyrim::ContainerMenu*>(ContainerMenu::createMenu_());

		if (containerMenu)
		{
			if (containerMenu->movieView)
			{
				Skyrim::GFxValue itemCard;

				if ((containerMenu->root.GetMember("ItemCard_mc", std::addressof(itemCard)) || containerMenu->root.GetMember("itemCard", std::addressof(itemCard))) && itemCard.IsObject())
				{ // Vanilla or SkyUI
					auto functionHandler = Skyrim::make_gpointer<PickpocketChanceFix::QuantitySliderChange>(containerMenu);

					Skyrim::GFxValue function;

					containerMenu->movieView->CreateFunction(std::addressof(function), functionHandler.get());

					if (containerMenu->root.SetMember("onQuantitySliderChange", function))
					{
						std::array<Skyrim::GFxValue, 3> arguments = { /* event */ "sliderChange", /* scope */ containerMenu->root, /* callback */ "onQuantitySliderChange" };

						itemCard.Invoke("addEventListener", nullptr, arguments.data(), arguments.size());
					}
				}
			}

			if (containerMenu->delegate)
			{
				ContainerMenu::quantitySliderOpen_  = containerMenu->delegate->callbackHashes.GetAlternative("QuantitySliderOpen")->callbackFunction;
				ContainerMenu::requestItemCardInfo_ = containerMenu->delegate->callbackHashes.GetAlternative("RequestItemCardInfo")->callbackFunction;

				containerMenu->delegate->callbackHashes.GetAlternative("QuantitySliderOpen")->callbackFunction  = std::addressof(ContainerMenu::QuantitySliderOpen);
				containerMenu->delegate->callbackHashes.GetAlternative("RequestItemCardInfo")->callbackFunction = std::addressof(ContainerMenu::RequestItemCardInfo);
			}
		}

		return containerMenu;
	}

	void ContainerMenu::AdvanceMovie(Skyrim::ContainerMenu* containerMenu, float interval, std::uint32_t currentTime)
	{
		auto pickpocketChance = ContainerMenu::GetPickpocketChance(containerMenu);

		// Skyrim Souls RE sets pickpocket chance before ContainerMenu::AdvanceMovie
		ContainerMenu::advanceMovie_(containerMenu, interval, currentTime);

		if (pickpocketChance.has_value())
		{
			ContainerMenu::SetPickpocketChance(containerMenu, pickpocketChance.value().first, pickpocketChance.value().second);
		}
	}

	void ContainerMenu::RequestItemCardInfo(const Skyrim::FxDelegateArguments& delegateArguments)
	{
		// Description Framework hooks a call in ContainerMenu::RequestItemCardInfo
		ContainerMenu::requestItemCardInfo_(delegateArguments);

		auto* containerMenu = static_cast<Skyrim::ContainerMenu*>(delegateArguments.GetDelegateHandler());

		if (containerMenu)
		{
			auto pickpocketChance = ContainerMenu::GetPickpocketChance(containerMenu);

			if (pickpocketChance.has_value())
			{
				ContainerMenu::SetPickpocketChance(containerMenu, pickpocketChance.value().first, pickpocketChance.value().second);
			}
		}
	}

	void ContainerMenu::QuantitySliderOpen(const Skyrim::FxDelegateArguments& delegateArguments)
	{
		ContainerMenu::quantitySliderOpen_(delegateArguments);

		auto* containerMenu = static_cast<Skyrim::ContainerMenu*>(delegateArguments.GetDelegateHandler());

		if (containerMenu && containerMenu->itemCard)
		{
			if (delegateArguments.GetArgumentCount() >= 1 && delegateArguments[0].IsBoolean())
			{
				const auto& opening = delegateArguments[0];

				containerMenu->itemCard->object.DeleteMember("quantitySliderChange");
				containerMenu->itemCard->object.SetMember("quantitySliderOpen", opening);
			}
		}
	}

	std::optional<std::pair<std::int32_t, bool>> ContainerMenu::GetPickpocketChance(Skyrim::ContainerMenu* containerMenu)
	{
		if (Skyrim::ContainerMenu::GetContainerMode() != Skyrim::ContainerMenu::ContainerMode::kPickpocket)
		{
			return std::nullopt;
		}

		if (!containerMenu || !containerMenu->itemList || !containerMenu->itemCard)
		{
			return std::nullopt;
		}

		Skyrim::GFxValue isViewingContainer;

		if (!containerMenu->root.Invoke("isViewingContainer", std::addressof(isViewingContainer)) || !isViewingContainer.IsBoolean())
		{
			return std::nullopt;
		}

		auto* selectedItem = containerMenu->itemList->GetSelectedItem();

		if (!selectedItem)
		{
			return std::nullopt;
		}

		auto* inventoryEntryData = selectedItem->standardItemData.inventoryEntryData;

		if (!inventoryEntryData)
		{
			return std::nullopt;
		}

		auto* boundObject = inventoryEntryData->boundObject;

		if (!boundObject)
		{
			return std::nullopt;
		}

		auto formWeight = boundObject->GetFormWeight();

		// ContainerMenu::RequestItemCardInfo does not set a minimum weight
		if (formWeight < 0.0F)
		{
			formWeight = 0.0F;
		}

		std::int32_t count = 1;

		Skyrim::GFxValue quantitySliderOpen;

		if (containerMenu->itemCard->object.GetMember("quantitySliderOpen", std::addressof(quantitySliderOpen)) && quantitySliderOpen.IsBoolean() && quantitySliderOpen.GetBoolean())
		{
			Skyrim::GFxValue quantitySliderChange;

			if (containerMenu->itemCard->object.GetMember("quantitySliderChange", std::addressof(quantitySliderChange)) && quantitySliderChange.IsNumber())
			{ // Quantity slider opened and changed
				count = static_cast<std::int32_t>(quantitySliderChange.GetNumber());
			}
			else
			{ // Quantity slider opened and not changed
				count = inventoryEntryData->countDelta;
			}
		}
		// ContainerMenu::RequestItemCardInfo does not check isViewingContainer
		else if (formWeight == 0.0F && isViewingContainer.GetBoolean())
		{ // Quantity slider not opened and not changed
			count = inventoryEntryData->countDelta;
		}

		auto* targetReference = Skyrim::ContainerMenu::GetTargetReference().get();

		if (!targetReference || targetReference->formType != Skyrim::FormType::kActor)
		{
			return std::nullopt;
		}

		auto* targetActor = static_cast<Skyrim::Actor*>(targetReference);

		// ContainerMenu::RequestItemCardInfo does not check isViewingContainer
		auto stealValue = targetActor->GetStealValue(inventoryEntryData, count, isViewingContainer.GetBoolean());

		// ContainerMenu::RequestItemCardInfo does not set a minimum value
		if (stealValue < 1)
		{
			stealValue = 1;
		}

		auto* playerCharacter = Skyrim::PlayerCharacter::GetSingleton();

		if (!playerCharacter)
		{
			return std::nullopt;
		}

		auto detected = targetActor->RequestDetectionLevel(playerCharacter, Skyrim::DetectionPriority::kNormal) > 0;

		auto pickpocketChance = Skyrim::AIFormulas::ComputePickpocketSuccess(
			playerCharacter->GetClampedActorValue(Skyrim::ActorValue::kPickpocket), // Skyrim Souls RE does not clamp the actor value
			targetActor->GetActorValue(Skyrim::ActorValue::kPickpocket),
			stealValue,
			formWeight * static_cast<float>(count), // ContainerMenu::RequestItemCardInfo does not multiply weight by count
			playerCharacter,
			targetActor,
			detected,
			boundObject);

		if (pickpocketChance > 100)
		{
			pickpocketChance = 100;
		}
		else if (pickpocketChance < 0)
		{
			pickpocketChance = 0;
		}

		return std::make_optional(std::make_pair(pickpocketChance, isViewingContainer.GetBoolean()));
	}

	void ContainerMenu::SetPickpocketChance(Skyrim::ContainerMenu* containerMenu, std::int32_t pickpocketChance, bool isViewingContainer)
	{
		if (!containerMenu || !containerMenu->movieView)
		{
			return;
		}

		Skyrim::GFxValue percentTextInstance;

		if (containerMenu->movieView->GetVariable(std::addressof(percentTextInstance), "_root.Menu_mc.ItemCardFadeHolder_mc.StealTextInstance.PercentTextInstance") && percentTextInstance.IsObject())
		{ // Vanilla
			Skyrim::GFxValue textField;

			if (containerMenu->movieView->GetVariable(std::addressof(textField), isViewingContainer ? "_root.TranslationBass.ToStealTextInstance" : "_root.TranslationBass.ToPlaceTextInstance") && textField.IsObject())
			{
				Skyrim::GFxValue text;

				if (textField.GetText(std::addressof(text)) && text.IsString())
				{
					percentTextInstance.SetTextHTML(std::format("<font face=\'$EverywhereBoldFont\' size=\'24\' color=\'#FFFFFF\'>{}%</font>{}", pickpocketChance, text.GetString()).c_str());
				}
			}
		}
		else if (containerMenu->movieView->GetVariable(std::addressof(percentTextInstance), "_root.Menu_mc.itemCardFadeHolder.StealTextInstance.PercentTextInstance") && percentTextInstance.IsObject())
		{ // SkyUI
			Skyrim::GFxValue                result;
			std::array<Skyrim::GFxValue, 1> arguments = { /* string */ isViewingContainer ? "$ TO STEAL" : "$ TO PLACE" };

			if (containerMenu->movieView->Invoke("skyui.util.Translator.translate", std::addressof(result), arguments.data(), static_cast<std::uint32_t>(arguments.size())) && result.IsString())
			{
				percentTextInstance.SetTextHTML(std::format("<font face=\'$EverywhereBoldFont\' size=\'24\' color=\'#FFFFFF\'>{}%</font>{}", pickpocketChance, result.GetString()).c_str());
			}
		}
	}

	decltype(ContainerMenu::CreateMenu)*   ContainerMenu::createMenu_{ nullptr };
	decltype(ContainerMenu::AdvanceMovie)* ContainerMenu::advanceMovie_{ nullptr };

	decltype(ContainerMenu::RequestItemCardInfo)* ContainerMenu::requestItemCardInfo_{ nullptr };
	decltype(ContainerMenu::QuantitySliderOpen)*  ContainerMenu::quantitySliderOpen_{ nullptr };
}
