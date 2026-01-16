#include "AssetManager.h"

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem> // C++17
#include <cctype>

namespace fs = std::filesystem;

namespace SurrealStudio {

    namespace SurrealStudio3D {

        namespace AssetManagement {

            // --- Add an asset ---
            void AssetManager::AddAsset(std::shared_ptr<Asset> asset)
            {
                asset->m_AssetID = m_NextAssetID++;
                m_Assets.push_back(asset);
                asset->m_IsDirty = false;
            }

            // --- Delete an asset by ID ---
            bool AssetManager::DeleteAsset(int assetID)
            {
                auto it = std::remove_if(m_Assets.begin(), m_Assets.end(),
                    [assetID](const std::shared_ptr<Asset>& a) { return a->m_AssetID == assetID; });

                if (it != m_Assets.end())
                {
                    m_Assets.erase(it, m_Assets.end());
                    return true;
                }

                return false;
            }

            // --- Get an asset by ID ---
            std::shared_ptr<Asset> AssetManager::GetAsset(int assetID)
            {
                for (const auto& asset : m_Assets)
                {
                    if (asset->m_AssetID == assetID)
                        return asset;
                }
                return nullptr;
            }

            // --- Get an asset by name ---
            std::shared_ptr<Asset> AssetManager::GetAssetByName(std::string name)
            {
                for (const auto& asset : m_Assets)
                {
                    if (asset->m_AssetName == name)
                        return asset;
                }
                return nullptr;
            }

            // --- Update an asset by ID ---
            bool AssetManager::UpdateAsset(int assetID, std::shared_ptr<Asset> updatedAsset)
            {
                for (auto& asset : m_Assets)
                {
                    if (asset->m_AssetID == assetID)
                    {
                        asset = updatedAsset;
                        return true;
                    }
                }
                return false;
            }

            // --- Load asset from a text file ---
            std::shared_ptr<Asset> AssetManager::LoadAssetFromFile(std::string filePath)
            {
                std::ifstream assetFile(filePath);
                if (!assetFile.is_open())
                {
                    std::cerr << "Failed to open file: " << filePath << std::endl;
                    return nullptr;
                }

                auto asset = std::make_shared<Asset>();
                asset->m_AssetID = m_NextAssetID++;
                asset->m_Asset_FilePathToAsset = filePath;

                std::string line;
                while (std::getline(assetFile, line))
                {
                    line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) { return !std::isspace(ch); }));
                    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), line.end());

                    if (line.empty() || line[0] == '#') continue;

                    std::istringstream iss(line);
                    std::string key, value;
                    if (!std::getline(iss, key, ':') || !std::getline(iss, value)) continue;

                    value.erase(value.begin(), std::find_if(value.begin(), value.end(), [](unsigned char ch) { return !std::isspace(ch); }));

                    if (key == "AssetName")
                        asset->m_AssetName = value;
                    else if (key == "AssetType")
                    {
                        if (value == "Mesh") asset->m_AssetType = std::make_unique<Asset::AssetType>(Asset::AssetType::Mesh);
                        else if (value == "Material") asset->m_AssetType = std::make_unique<Asset::AssetType>(Asset::AssetType::Material);
                        else if (value == "Texture") asset->m_AssetType = std::make_unique<Asset::AssetType>(Asset::AssetType::Texture);
                        else if (value == "Animation") asset->m_AssetType = std::make_unique<Asset::AssetType>(Asset::AssetType::Animation);
                        else asset->m_AssetType = std::make_unique<Asset::AssetType>(Asset::AssetType::Other);
                    }
                    else if (key == "Position")
                    {
                        float x, y, z;
                        char comma;
                        std::istringstream ss(value);
                        ss >> x >> comma >> y >> comma >> z;
                        asset->m_AssetTransform.position = { x, y, z };
                    }
                    else if (key == "Rotation")
                    {
                        float x, y, z;
                        char comma;
                        std::istringstream ss(value);
                        ss >> x >> comma >> y >> comma >> z;
                        asset->m_AssetTransform.rotation = { x, y, z };
                    }
                    else if (key == "Scale")
                    {
                        float x, y, z;
                        char comma;
                        std::istringstream ss(value);
                        ss >> x >> comma >> y >> comma >> z;
                        asset->m_AssetTransform.scale = { x, y, z };
                    }
                }

                assetFile.close();
                return asset;
            }

            // --- Save asset to file (simple text-based) ---
            bool AssetManager::SaveAssetToFile(int assetID, const std::string& filePath)
            {
                auto asset = GetAsset(assetID);
                if (!asset) return false;

                std::ofstream outFile(filePath);
                if (!outFile.is_open()) return false;

                outFile << "AssetName:" << asset->m_AssetName << "\n";
                if (asset->m_AssetType)
                {
                    switch (*asset->m_AssetType)
                    {
                    case Asset::AssetType::Mesh: outFile << "AssetType:Mesh\n"; break;
                    case Asset::AssetType::Material: outFile << "AssetType:Material\n"; break;
                    case Asset::AssetType::Texture: outFile << "AssetType:Texture\n"; break;
                    case Asset::AssetType::Animation: outFile << "AssetType:Animation\n"; break;
                    default: outFile << "AssetType:Other\n"; break;
                    }
                }
                outFile << "Position:" << asset->m_AssetTransform.position.x << ","
                    << asset->m_AssetTransform.position.y << "," << asset->m_AssetTransform.position.z << "\n";
                outFile << "Rotation:" << asset->m_AssetTransform.rotation.x << ","
                    << asset->m_AssetTransform.rotation.y << "," << asset->m_AssetTransform.rotation.z << "\n";
                outFile << "Scale:" << asset->m_AssetTransform.scale.x << ","
                    << asset->m_AssetTransform.scale.y << "," << asset->m_AssetTransform.scale.z << "\n";

                outFile.close();
                return true;
            }

            // --- Create project folder structure ---
            void AssetManager::MakeSurrealStudio3DAsset_PROJECTSTRUCTURE()
            {
                namespace fs = std::filesystem;

                fs::create_directories("Project/Assets/Meshes");
                fs::create_directories("Project/Assets/Textures");
                fs::create_directories("Project/Assets/Materials");
                fs::create_directories("Project/Scripts");
                fs::create_directories("Project/ExternalDependencies");

                std::cout << "Project structure created.\n";
            }

        } // namespace AssetManagement
    } // namespace SurrealStudio3D
} // namespace SurrealStudio
