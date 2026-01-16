#pragma once

namespace SurrealStudio {

	namespace SGSIDE {

		class SGSIDESSScriptExplorerPanel
		{
		public:

			bool DrawSGSIDESSScriptExplorerPanel();
			bool DrawCreateNewFile(const char* SGSIDEFileName_PYTHONFILE, const char* SGSIDEFileName_PYTHONFILE_path);

			bool DrawShowFileHierarchy();
		};
	}
}

