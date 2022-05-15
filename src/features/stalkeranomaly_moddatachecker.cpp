#include "stalkeranomaly_moddatachecker.h"

#include <ifiletree.h>

using FileNameSet = std::set<QString, MOBase::FileNameComparator>;

static FileNameSet g_folders{
    "appdata",
    "bin",
    "db",
    "gamedata",
};

auto AnomalyModDataChecker::dataLooksValid(FileTreePtr a_tree) const
	-> CheckReturn
{
    for (auto entry : *a_tree) {
        if (entry->isDir()) {
            if (g_folders.count(entry->name()) > 0)
                return CheckReturn::VALID;
        }
    }

    return CheckReturn::INVALID;
}
