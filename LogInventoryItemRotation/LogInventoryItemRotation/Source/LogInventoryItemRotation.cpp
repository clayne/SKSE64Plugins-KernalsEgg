#include "PrecompiledHeader.h"

#include "Events.h"
#include "Shared/Relocation/Module.h"



namespace LogInventoryItemRotation
{
	namespace Log
	{
		void Load()
		{
			auto path   = std::filesystem::path(Relocation::DynamicLinkLibrary::GetSingleton().GetPath()).replace_extension("log");
			auto logger = spdlog::basic_logger_mt(path.string(), path.string(), true);

			logger->flush_on(spdlog::level::info);
			logger->set_level(spdlog::level::info);
			logger->set_pattern("[%Y-%m-%d %T.%e %z] [%l] [%t] [%s:%#] %v");

			spdlog::set_default_logger(std::move(logger));
		}
	}

	void Load()
	{
		Events::Register();
	}
}

#ifdef SKYRIM_ANNIVERSARY_EDITION
extern "C" __declspec(dllexport) constinit SKSE::PluginVersionData SKSEPlugin_Version{
	.pluginVersion   = 3,
	.pluginName      = "Log Inventory Item Rotation",
	.author          = "KernalsEgg",
	.addressLibrary  = true,
	.compatible16629 = true
};
#else
extern "C" __declspec(dllexport) bool __cdecl SKSEPlugin_Query(SKSE::Interface* queryInterface, SKSE::PluginInformation* pluginInformation)
{
	pluginInformation->informationVersion = SKSE::PluginInformation::kVersion;
	pluginInformation->name               = "Log Inventory Item Rotation";
	pluginInformation->version            = 3;

	return true;
}
#endif

extern "C" __declspec(dllexport) bool __cdecl SKSEPlugin_Load(SKSE::Interface* loadInterface)
{
	LogInventoryItemRotation::Log::Load();
	SKSE::Storage::GetSingleton().Load(loadInterface);
	LogInventoryItemRotation::Load();

	return true;
}
