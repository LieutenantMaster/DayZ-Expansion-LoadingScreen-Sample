[WorkbenchPluginAttribute("Deploy Mod", "Deploys the active loaded mod", "alt+1", "", {"ResourceManager", "ScriptEditor"})]
class ExpansionDeployModTool: DayZTool
{
	string BatchFile;

	void ExpansionDeployModTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\Deploy.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}