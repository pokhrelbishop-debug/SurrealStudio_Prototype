#pragma once

#include "Asset.h"

#include <vector>
#include <memory>
#include <string>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace AssetManagement {

			class AssetManager
			{
			public:

				AssetManager() = default;
				~AssetManager() = default;

				std::vector<std::shared_ptr<Asset>> m_Assets;
				int m_NextAssetID = 0;

				// Basic asset management
				void AddAsset(std::shared_ptr<Asset> asset);
				bool DeleteAsset(int assetID);

				std::shared_ptr<Asset> GetAsset(int assetID);
				std::shared_ptr<Asset> GetAssetByName(std::string name);

				bool UpdateAsset(int assetID, std::shared_ptr<Asset> updatedAsset);

				// Loading and saving from disk
				std::shared_ptr<Asset> LoadAssetFromFile(std::string filePath);
				bool SaveAssetToFile(int assetID, const std::string& filePath);

				void MakeSurrealStudio3DAsset_PROJECTSTRUCTURE();
			};
		}
	}
}