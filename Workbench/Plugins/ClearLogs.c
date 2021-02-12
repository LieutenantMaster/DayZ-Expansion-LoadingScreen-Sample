[WorkbenchPluginAttribute("Clear Log-Files", "Clears game and server log files", "alt+7", "", {"ResourceManager", "ScriptEditor"})]
class ClearLogsTool: DayZTool
{
	string BatchFile;

	void ClearLogsTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\ClearLogs.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}