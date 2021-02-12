[WorkbenchPluginAttribute("Launch Server", "Launches the server normal", "alt+8", "", {"ResourceManager", "ScriptEditor"})]
class LaunchServerTool: DayZTool
{
	string BatchFile;

	void LaunchServerTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\LaunchServer.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}