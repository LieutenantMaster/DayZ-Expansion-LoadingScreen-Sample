[WorkbenchPluginAttribute("Launch Client", "Launches the game normal", "alt+6", "", {"ResourceManager", "ScriptEditor"})]
class LaunchClientTool: DayZTool
{
	string BatchFile;

	void LaunchClientTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\LaunchClient.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}