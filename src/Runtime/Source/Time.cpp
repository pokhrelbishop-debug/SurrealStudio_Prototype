#include "Time.h"

#include <chrono>

namespace SurrealStudio {

	namespace Runtime
	{
		// variables needed
		static std::chrono::high_resolution_clock::time_point s_LastTime;

		float Time::s_DeltaTime = 0.0f;
		float Time::s_Time = 0.0f;

		void Time::Init()
		{
			s_LastTime = std::chrono::high_resolution_clock::now();
		}

		void Time::Update()
		{
			auto now = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> delta = now - s_LastTime;
			s_LastTime = now;

			s_LastTime = delta.count();
			s_Time += s_DeltaTime;
		}

		float Time::GetDetlaTime() 
		{
			return s_DeltaTime;
		}

		float Time::GetTime() 
		{
			return s_Time;
		}
	}
}