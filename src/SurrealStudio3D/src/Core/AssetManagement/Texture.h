#pragma once

#include <string>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace AssetManagement {

			class Texture
			{
			public:

				enum class TextureType
				{
					None = 0,
					BuiltIn,
					Custom
				};

				enum class TextureBuiltIn 
				{
					None = 0,
					White,
					Black, Gray, Yellow, Red, Green, Blue,
				};

				TextureType m_TextureType;
				
				bool LoadTexture(TextureType& textureType, const std::string& textureFilePath);
				bool UnloadTexture(TextureType& textureType, const std::string& textureFilePath);

			private:

				TextureType m_CurrentTextureType = TextureType::None;
			};
		}
	}
}