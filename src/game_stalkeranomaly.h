#pragma once

#include <iplugingame.h>
#include <utility.h>

class AnomalyGame :
	public MOBase::IPluginGame
{
	Q_OBJECT
	Q_INTERFACES(MOBase::IPlugin MOBase::IPluginGame)
	Q_PLUGIN_METADATA(IID "com.qudix.game_stalkeranomaly" FILE "game_stalkeranomaly.json")

	using FeatureMap = std::map<std::type_index, std::any>;
	using SaveGamePtr = std::shared_ptr<const MOBase::ISaveGame>;
	using SaveGameVec = std::vector<SaveGamePtr>;

	static constexpr auto FALLBACK_VERSION = "1.0.0";

public:
	AnomalyGame() = default;

public: // IPLugin
	bool init(MOBase::IOrganizer* a_organizer) override;

	QString name() const override;
	QString localizedName() const override;
	QString author() const override;
	QString description() const override;
	MOBase::VersionInfo version() const override;
	QList<MOBase::PluginSetting> settings() const override;

public: // IPLuginGame
	QString binaryName() const override;
	QString gameVersion() const override;
	QString gameName() const override;
	QString gameShortName() const override;
	QString gameNexusName() const override;
	int32_t nexusGameID() const override;
	QIcon gameIcon() const override;
	QDir gameDirectory() const override;
	QDir dataDirectory() const override;
	QDir documentsDirectory() const override;
	QDir savesDirectory() const override;
	QString getLauncherName() const override;
	QString getSupportURL() const override;

	QList<MOBase::ExecutableInfo> executables() const override;

	void detectGame() override;
	bool looksValid(QDir const& a_path) const override;

	void setGamePath(const QString& a_path) override { m_gamePath = a_path; }
	bool isInstalled() const override { return !m_gamePath.isEmpty(); }

	void initializeProfile(const QDir& a_directory, ProfileSettings a_settings) const override;

	SaveGameVec listSaves(QDir a_folder) const override;

	// None
	QString steamAPPId() const override { return {}; }
	QStringList primaryPlugins() const override { return {}; }
	QStringList primarySources() const override { return {}; }
	QStringList gameVariants() const override { return {}; }
	QStringList validShortNames() const override { return {}; }
	QStringList iniFiles() const override { return {}; }
	QStringList DLCPlugins() const override { return {}; }
	QStringList CCPlugins() const override { return {}; }
	QList<MOBase::ExecutableForcedLoadSetting> executableForcedLoads() const override { return {}; }
	LoadOrderMechanism loadOrderMechanism() const override { return LoadOrderMechanism::FileTime; }
	SortMechanism sortMechanism() const override { return SortMechanism::NONE; }
	int32_t nexusModOrganizerID() const override { return 0; }
	void setGameVariant(const QString&) override {}

protected: // IPluginGame
	FeatureMap featureList() const override { return m_features; }

private:
	template <class T>
	void register_feature(T* a_type) {
		auto index = std::type_index(typeid(T));
		if (m_features.find(index) != m_features.end()) {
			delete std::any_cast<T*>(m_features[index]);
		}

		m_features[index] = a_type;
	}

	QString identify_path() const;
	QString identify_version(QString a_binaryPath) const;

	QFileInfo from_rel(QString a_binaryPath) const;

private:
	MOBase::IOrganizer* m_organizer;

	QString m_gamePath;

	FeatureMap m_features;
};
