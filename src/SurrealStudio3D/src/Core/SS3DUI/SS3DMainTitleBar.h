#pragma once

namespace SurrealStudio {

	namespace SurrealStudio3D {

		class SS3DMainTitleBar
		{
		public:

			bool SS3DMainTitleBar_DrawFileTab();
			bool SS3DMainTitleBar_DrawSettingsTab();
			bool SS3DMainTitleBar_DrawSGSIDETab();
			bool SS3DMainTitleBar_DrawSpritemakerTab();
			bool SS3DMainTitleBar_DrawImportTab();
			bool SS3DMainTitleBar_DrawExportTab();

			bool SS3DMainTitleBar_DrawMainTitleBar();

		private:

			bool m_OpenImportDialog = true;
			bool m_OpenExportDialog = true;
			bool m_OpenSettingsDialog = true;
			bool m_EnableVSync = true;
			bool m_EnableHighGraphicsResolution = true;

			float m_PhyicsUpdateRate = 0.0f;
			float m_GravityValue = 0.0f;

			bool m_ShowSceneHierarchyPanel = false;  // Default
		};
	}
}
