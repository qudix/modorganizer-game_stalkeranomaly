#include "stalkeranomaly_moddatacontent.h"

#include <ifiletree.h>

std::vector<AnomalyModDataContent::Content> AnomalyModDataContent::getAllContents() const
{
	static std::vector<Content> contents{
		{ EContent::Interface, QT_TR_NOOP("Interface"), ":/MO/gui/content/interface" },
		{ EContent::Texture, QT_TR_NOOP("Textures"), ":/MO/gui/content/texture" },
		{ EContent::Mesh, QT_TR_NOOP("Meshes"), ":/MO/gui/content/mesh" },
		{ EContent::Script, QT_TR_NOOP("Scripts"), ":/MO/gui/content/script" },
		{ EContent::Sound, QT_TR_NOOP("Sounds"), ":/MO/gui/content/sound" },
		{ EContent::MCM, QT_TR_NOOP("MCM"), ":/MO/gui/content/menu" },
		{ EContent::Config, QT_TR_NOOP("Configs"), ":/MO/gui/content/inifile" }
	};

	return contents;
}

std::vector<int32_t> AnomalyModDataContent::getContentsFor(FileTreePtr a_tree) const
{
	using FileTreeEntry = std::shared_ptr<const MOBase::FileTreeEntry>;
	using WalkReturn = MOBase::IFileTree::WalkReturn;

	std::vector<int32_t> contents;
	a_tree->walk([&](const QString& a_path, FileTreeEntry a_entry) -> WalkReturn {
		auto name = a_entry->name();
		if (a_entry->isFile()) {
			auto suffix = a_entry->suffix().toLower();
			if (suffix == "dds" || suffix == "thm") {
				contents.push_back(EContent::Texture);
				if (a_path.startsWith("gamedata/textures/ui", Qt::CaseInsensitive))
					contents.push_back(EContent::Interface);
			} else if (suffix == "omf" || suffix == "ogf") {
				contents.push_back(EContent::Mesh);
			} else if (suffix == "script") {
				contents.push_back(EContent::Script);
				if (name.contains("_mcm", Qt::CaseInsensitive))
					contents.push_back(EContent::MCM);
			} else if (suffix == "ogg") {
				contents.push_back(EContent::Sound);
			} else if (suffix == "ltx" || suffix == "xml") {
				contents.push_back(EContent::Config);
				if (a_path.startsWith("gamedata/configs/ui", Qt::CaseInsensitive))
					contents.push_back(EContent::Interface);
			}
		}

		return WalkReturn::CONTINUE;
	}, "/");

	return contents;
}
