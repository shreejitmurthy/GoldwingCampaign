#include "AssetManager.hpp"

void AssetManager::LoadFontAsset(const std::string &name, const std::string &filePath) {
    fonts[name] = LoadFont(filePath.c_str());
}

void AssetManager::LoadFontAsset(const std::string &name, Font font) {
    fonts[name] = font;
}

void AssetManager::LoadTextureAsset(const std::string &name, const std::string &filePath) {
    textures[name] = LoadTexture(filePath.c_str());
}

void AssetManager::LoadTextureAsset(const std::string &name, Texture texture) {
    textures[name] = texture;
}

void AssetManager::LoadModelAsset(const std::string &name, const std::string &filePath) {
    models[name] = LoadModel(filePath.c_str());
}

void AssetManager::LoadModelAsset(const std::string &name, Model model) {
    models[name] = model;
}

Font AssetManager::GetFont(const std::string &name) {
    return fonts.at(name);
}

Texture2D AssetManager::GetTexture(const std::string &name) {
    return textures.at(name);
}

Model AssetManager::GetModel(const std::string &name) {
    return models.at(name);
}

void AssetManager::UnloadAll() {
    for (auto& [name, font] : fonts) UnloadFont(font);
    for (auto& [name, texture] : textures) UnloadTexture(texture);
    for (auto& [name, model] : models) UnloadModel(model);
}
