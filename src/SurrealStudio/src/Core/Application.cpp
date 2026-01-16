#include "Application.h"
#include "SSEngineDefines.h"
#include "SurrealStudioMainWindow.h"

#include <stdexcept>
#include <iostream>
#include <memory>

namespace SurrealStudio {

	SSApplication::SSApplication(const SurrealStudioApplicationSpecification& ssApplicationSpecification)
		: m_Specification(ssApplicationSpecification)
	{
	}

	bool SSApplication::Initialize()
	{
		try
		{
			INFO("Surreal Studio is starting!");
			return true;
		}
		catch (const std::exception& e)
		{
			ERROR(e.what());
			return false;
		}
		catch (...)
		{
			ERROR("Some unknown exception occured!");
			return false;
		}
	}

	bool SSApplication::Run(int argc, char** argv)
	{
		try
		{
			std::cout << "Welcome to Surreal Studio (GAME ENGINE)" << "\n" << std::endl;
			auto app = std::make_unique<SSSurrealStudioMainWindow>();
			app->Initialize();
			app->MainLoop();
			app->DestroySSApp();
			return true;
		}
		catch (const std::exception& e)
		{
			ERROR(e.what());
			return false;
		}
		catch (...)
		{
			ERROR("Some unknown exception occured!");
			return false;
		}

	}

	bool SSApplication::Shutdown()
	{
		try
		{
			INFO("Surreal Studio shutting down!");
			return true;
		}
		catch (const std::exception& e)
		{
			ERROR(e.what());
			return false;
		}
		catch (...)
		{
			ERROR("Some unknown exception occured!");
			return false;
		}

	}

	SSApplication* SSApplication::CreateApplication()
	{
		try
		{
			SurrealStudioApplicationSpecification applicationSpecification;

			applicationSpecification.applicationName = "Surreal Studio";
			applicationSpecification.applicationWidth = 800;
			applicationSpecification.applicationHeight = 600;
			applicationSpecification.VSync = true;

			return new SSApplication(applicationSpecification);
			
		}
		catch (const std::exception& e)
		{
			ERROR(e.what());
			std::exit(ENGINE_FAILURE);
		}
		catch (...)
		{
			ERROR("Some unkown exception occured!");
			std::exit(ENGINE_FAILURE);
		}
	}
}