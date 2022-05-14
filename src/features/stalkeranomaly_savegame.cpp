#include "stalkeranomaly_savegame.h"

QString AnomalySaveGame::getFilepath() const
{
	return m_file;
}

QDateTime AnomalySaveGame::getCreationTime() const
{
	return m_creation;
}

QString AnomalySaveGame::getName() const
{
	return "Test";
}

QString AnomalySaveGame::getSaveGroupIdentifier() const
{
	return "Group";
}

QStringList AnomalySaveGame::allFiles() const
{
	QStringList ret = { m_file };
	QStringList files = { ".scoc", ".dds" };
	QString base = m_fileInfo.absolutePath() + "/" + m_fileInfo.completeBaseName();

	for (auto& file : files) {
		QFileInfo info{ base + file };
		if (info.exists())
			ret.push_back(info.absoluteFilePath());
	}

	return ret;
}
