#pragma once

#include <moddatacontent.h>

class AnomalyGame;

class AnomalyModDataContent :
	public ModDataContent
{
    using FileTreePtr = std::shared_ptr<const MOBase::IFileTree>;

public:
    enum EContent {
        Interface,
        Texture,
        Mesh,
        Script,
        Sound,
        MCM,
        Config
    };

    AnomalyModDataContent(const AnomalyGame* a_game) :
        m_game(a_game)
    {}

public:
    std::vector<Content> getAllContents() const override;
    std::vector<int32_t> getContentsFor(FileTreePtr a_tree) const override;

private:
    const AnomalyGame* m_game;
};
