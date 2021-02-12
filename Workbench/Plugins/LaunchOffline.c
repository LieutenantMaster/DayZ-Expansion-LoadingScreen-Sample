[WorkbenchPluginAttribute("Launch Offline", "Launches the game in offline mode", "alt+3", "", {"ResourceManager", "ScriptEditor"})]
class ExpansionLaunchOfflineModTool: DayZTool
{
	string BatchFile;

	void ExpansionLaunchOfflineModTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\LaunchOffline.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}