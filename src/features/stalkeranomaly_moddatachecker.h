#pragma once

#include <moddatachecker.h>

namespace MOBase
{
	class IFileTree;
}

class AnomalyGame;

class AnomalyModDataChecker :
	public ModDataChecker
{
	using FileTreePtr = std::shared_ptr<const MOBase::IFileTree>;

public:
	AnomalyModDataChecker(const AnomalyGame* a_game) :
		m_game(a_game)
	{}

public:
	CheckReturn dataLooksValid(FileTreePtr a_tree) const override;

private:
	const AnomalyGame* m_game;
};
