#pragma once

#include <string>

namespace SurrealStudio {

	struct SurrealStudioApplicationSpecification
	{
		std::string applicationName; 
		unsigned int applicationWidth;
		unsigned int applicationHeight;
		bool VSync = true;
	};

	class SSApplication
	{
	public:

		SSApplication(const SurrealStudioApplicationSpecification& ssApplicationSpecification);
		~SSApplication() = default;

		bool Initialize();
		bool Run(int arg, char** argv);
		bool Shutdown();

		static SSApplication* CreateApplication();

	private:

		const SurrealStudioApplicationSpecification& m_Specification;
	};
}