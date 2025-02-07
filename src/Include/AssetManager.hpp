#pragma once

#include "raylib.h"
#include <unordered_map>
#include <string>

class AssetManager {
private:
    std::unordered_map<std::string, Font> fonts;
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Model> models;

public:
    void LoadFontAsset(const std::string& name, const std::string& filePath);

    void LoadFontAsset(const std::string& name, const std::string& filePath, int fontSize);

    void LoadTextureAsset(const std::string& name, const std::string& filePath);

    void LoadModelAsset(const std::string& name, const std::string& filePath);

    Font GetFont(const std::string& name);

    Texture2D GetTexture(const std::string& name);

    Model GetModel(const std::string& name);

    void UnloadAll();
};
