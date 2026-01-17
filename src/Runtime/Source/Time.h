#pragma once

namespace SurrealStudio {

	namespace Runtime {

		class Time
		{
		public:
			static void Init();
			static void Update();

			static float GetDeltaTime();
			static float GetTime()	;

		private:
			static float s_DeltaTime;
			static float s_Time;
		};
	}
}