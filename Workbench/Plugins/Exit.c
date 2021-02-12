[WorkbenchPluginAttribute("Exit Game", "Exits the game", "alt+2", "", {"ResourceManager", "ScriptEditor"})]
class ExpansionExitModTool: DayZTool
{
	string BatchFile;

	void ExpansionExitModTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\Exit.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}