#include "game_stalkeranomaly.h"

#include "features/stalkeranomaly_savegame.h"

bool AnomalyGame::init(MOBase::IOrganizer* a_organizer)
{
	m_organizer = a_organizer;

	return true;
}

QString AnomalyGame::name() const
{
	return "game_stalkeranomaly";
}

QString AnomalyGame::localizedName() const
{
	return tr("STALKER Anomaly");
}

QString AnomalyGame::author() const
{
	return "Qudix";
}

QString AnomalyGame::description() const
{
	return tr("Adds support for the game S.T.A.L.K.E.R. Anomaly.");
}

MOBase::VersionInfo AnomalyGame::version() const
{
	return { 0, 6, 0 };
}

QList<MOBase::PluginSetting> AnomalyGame::settings() const
{
	return {};
}

QString AnomalyGame::binaryName() const
{
	return "AnomalyLauncher.exe";
}

QString AnomalyGame::gameVersion() const
{
	auto path = gameDirectory().absoluteFilePath(binaryName());
	return identify_version(path);
}

QString AnomalyGame::gameName() const
{
	return "STALKER Anomaly";
}

QString AnomalyGame::gameShortName() const
{
	return "stalkeranomaly";
}

QString AnomalyGame::gameNexusName() const
{
	return "stalkeranomaly";
}

int32_t AnomalyGame::nexusGameID() const
{
	return 3743;
}

QIcon AnomalyGame::gameIcon() const
{
	auto path = gameDirectory().absoluteFilePath(binaryName());
	return MOBase::iconForExecutable(path);
}

QDir AnomalyGame::gameDirectory() const
{
	return { m_gamePath };
}

QDir AnomalyGame::dataDirectory() const
{
	return gameDirectory().absoluteFilePath("");
}

QDir AnomalyGame::documentsDirectory() const
{
	return dataDirectory().absoluteFilePath("appdata");
}

QDir AnomalyGame::savesDirectory() const
{
	return documentsDirectory().absoluteFilePath("savedgames");
}

QString AnomalyGame::getLauncherName() const
{
	return binaryName();
}

QString AnomalyGame::getSupportURL() const
{
	return "https://www.stalker-anomaly.com/";
}

QList<MOBase::ExecutableInfo> AnomalyGame::executables() const
{
	return {
		{ "Anomaly Launcher", from_rel("AnomalyLauncher.exe") },
		{ "Anomaly (DX11-AVX)", from_rel("bin/AnomalyDX11AVX.exe") },
		{ "Anomaly (DX11)", from_rel("bin/AnomalyDX11.exe") },
		{ "Anomaly (DX10-AVX)", from_rel("bin/AnomalyDX10AVX.exe") },
		{ "Anomaly (DX10)", from_rel("bin/AnomalyDX10.exe") },
		{ "Anomaly (DX9-AVX)", from_rel("bin/AnomalyDX9AVX.exe") },
		{ "Anomaly (DX9)", from_rel("bin/AnomalyDX9.exe") },
		{ "Anomaly (DX8-AVX)", from_rel("bin/AnomalyDX8AVX.exe") },
		{ "Anomaly (DX8)", from_rel("bin/AnomalyDX8.exe") }
	};
}

void AnomalyGame::detectGame()
{
	m_gamePath = identify_path();
}

bool AnomalyGame::looksValid(QDir const& a_path) const
{
	return a_path.exists(binaryName());
}

void AnomalyGame::initializeProfile(const QDir& a_directory, ProfileSettings a_settings) const
{
	// None
}

AnomalyGame::SaveGameVec AnomalyGame::listSaves(QDir a_folder) const
{
	QStringList filters{ "*.scop" };
	SaveGameVec saves;
	for (auto& info : a_folder.entryInfoList(filters, QDir::Files)) {
		auto save = std::make_shared<const AnomalySaveGame>(info.filePath(), this);
		saves.push_back(save);
	}

	return saves;
}

QString AnomalyGame::identify_path() const
{
	return {};
}

QString AnomalyGame::identify_version(QString a_binaryPath) const
{
	auto version = MOBase::getFileVersion(a_binaryPath);
	if (version.startsWith(FALLBACK_VERSION)) {
		auto pversion = MOBase::getProductVersion(a_binaryPath);
		if (!pversion.isEmpty()) {
			return pversion;
		}
	}

	return version;
}

QFileInfo AnomalyGame::from_rel(QString a_binaryPath) const
{
	return QFileInfo{ gameDirectory().absoluteFilePath(a_binaryPath) };
}
