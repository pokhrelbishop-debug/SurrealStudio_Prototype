#include "SurrealStudio/src/Core/Application.h"
#include "SurrealStudio/src/Core/SSEngineDefines.h"
#include "../src/EngineCore/Engine.h"

#include <memory>
#include <stdexcept>

using namespace SurrealStudio;

#ifdef _WIN64

int main(int argc, char** argv)
{
	try
	{
		std::unique_ptr<SSApplication> app(SSApplication::CreateApplication());
		auto engine = std::make_unique<EngineCore::Engine>();
		
		if (app == nullptr)
		{
			ERROR("SurrealStudio::Application::CreateApplication function is a null pointer!");
			return ENGINE_FAILURE;
		}
		else if (engine == nullptr)
		{
			ERROR("Line 17, in Main.cpp is a null pointer!");
			return ENGINE_FAILURE;
		}

		engine->Init();
		engine->Update();

		app->Run(argc, argv);

		engine->Shutdown();

		return ENGINE_SUCCESS;
	}
	catch (const std::exception& e) {
		ERROR(e.what());
		return SurrealStudio::ENGINE_FAILURE;
	}
	catch (...)
	{
		ERROR("Some unknown exception occurred!");
		return ENGINE_FAILURE;
	}
}

#else
	#error Surreal Studio only supports 64 bit Windows!
#endif // _WIN64