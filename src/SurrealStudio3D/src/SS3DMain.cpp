#include <iostream>
#include <stdexcept>

#include "SS3DEngineDefines.h"

namespace SurrealStudio {

	namespace SurrealStudio3D {

		int INT_SS3D_MAIN_FUNC__SS(int argc, char** argv)
		{
			try
			{
				return ENGINE_SUCCESS;
			}
			catch (const std::exception& e) {
				SS3D_ERROR(e.what()); return ENGINE_FAILURE;
			}
			catch (...) { SS3D_ERROR("Some unknown exception occurred!"); return ENGINE_FAILURE; }
		}
	}
}