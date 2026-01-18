#include "Time.h"

#include <chrono>

namespace SurrealStudio {

	namespace EngineCore {
		// Use a steady (monotonic) clock for frame intervals
		using Clock = std::chrono::steady_clock;
		static Clock::time_point s_LastTime;

		float Time::s_DeltaTime = 0.0f;
		float Time::s_Time = 0.0f;

		void Time::Init()
		{
			s_LastTime = Clock::now();
			s_DeltaTime = 0.0f;
			s_Time = 0.0f;
		}

		void Time::Update()
		{
			auto now = Clock::now();
			std::chrono::duration<float> delta = now - s_LastTime;

			// Properly assign delta and update last time
			s_DeltaTime = delta.count();
			s_LastTime = now;

			// Accumulate elapsed time
			s_Time += s_DeltaTime;
		}

		float Time::GetDeltaTime()
		{
			return s_DeltaTime;
		}

		float Time::GetTime()
		{
			return s_Time;
		}
	}
}