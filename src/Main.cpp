#include "SurrealStudio/src/Core/Application.h"
#include "SurrealStudio/src/Core/SSEngineDefines.h"

#include <memory>
#include <stdexcept>

using namespace SurrealStudio;

#ifdef _WIN64

int main(int argc, char** argv)
{
	try
	{
		std::unique_ptr<SSApplication> app(SSApplication::CreateApplication());
		if (app == nullptr)
		{
			ERROR("SurrealStudio::Application::CreateApplication function is a null pointer!");
			return ENGINE_FAILURE;
		}

		if (!app->Initialize()) return ENGINE_FAILURE; INFO("Surreal Studio intialized!");
		if (!app->Run(argc, argv))   return ENGINE_FAILURE; INFO("Surreal Studio running!");
		if (!app->Shutdown())  return ENGINE_FAILURE; INFO("Surreal Studio shutting down!");

		return ENGINE_SUCCESS;
	}
	catch (const std::exception& e)
	{
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