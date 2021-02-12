[WorkbenchPluginAttribute("Launch Local MP", "Launches the game and server, automatically connects", "alt+4", "", {"ResourceManager", "ScriptEditor"})]
class ExpansionLaunchLocalMPModTool: DayZTool
{
	string BatchFile;

	void ExpansionLaunchLocalMPModTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\LaunchLocalMP.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}
