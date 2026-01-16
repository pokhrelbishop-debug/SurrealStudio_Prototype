#include "SGSIDESSScriptExplorerPanel.h"

#include <stdexcept>
#include <iostream>
#include <filesystem>

namespace SurrealStudio {

	namespace SGSIDE {

		bool SGSIDESSScriptExplorerPanel::DrawSGSIDESSScriptExplorerPanel()
		{
			try
			{
				return true;
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl; return false;
			}
			catch (...) { std::cerr << "Some unknown exception occurred!"; return false; }
		}

		bool SGSIDESSScriptExplorerPanel::DrawCreateNewFile(const char* SGSIDEFileName_PYTHONFILE, const char* SGSIDEFileName_PYTHONFILE_path)
		{
			try
			{
				return true;
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl; return false;
			}
			catch (...) { std::cerr << "Some unknown exception occurred!"; return false; }
		}

		bool SGSIDESSScriptExplorerPanel::DrawShowFileHierarchy()
		{
			try
			{
				return true;
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl; return false;
			}
			catch (...) { std::cerr << "Some unknown exception occurred!"; return false; }
		}
	}
}