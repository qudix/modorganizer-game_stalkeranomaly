#pragma once

#include <isavegame.h>

class AnomalyGame;

class AnomalySaveGame :
	public MOBase::ISaveGame
{
public:
	AnomalySaveGame(const QString& a_file, const AnomalyGame* a_game) :
		m_file(a_file),
		m_fileInfo(m_file),
		m_game(a_game),
		m_creation(m_fileInfo.lastModified())
	{}

	~AnomalySaveGame() = default;

public: // ISaveGame
	QString getFilepath() const override;
	QDateTime getCreationTime() const override;
	QString getName() const override;
	QString getSaveGroupIdentifier() const override;
	QStringList allFiles() const override;

private:
	QString m_file;
	QFileInfo m_fileInfo;
	const AnomalyGame* m_game;
	QDateTime m_creation;
};
