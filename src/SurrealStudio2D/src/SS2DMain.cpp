#include "Core/SS2DEngineDefines.h"

#include <iostream>
#include <stdexcept>
#include <stdio.h>

#ifdef _WIN64

namespace SurrealStudio {

	namespace SurrealStudio2D {

		int INT_WIN64_SS2D_MAIN(int argc, char** argv)
		{
			try
			{
				return ENGINE_SUCCESS;
			}
			catch (const std::exception& e)
			{
				SS2DERROR(e.what());
				return ENGINE_FAILURE;
			}
			catch (...)
			{
				SS2DERROR("Some unknown exception occured!");
				return ENGINE_FAILURE;
			}
		}
	}
}

#else
	#error Surreal Studio only supports 64 bit windows!
#endif