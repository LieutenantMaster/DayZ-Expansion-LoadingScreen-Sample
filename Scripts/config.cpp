/**
 * config.cpp
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class CfgPatches
{
    class ModName_ExpansionLoadingScreen
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
		requiredAddons[]=
		{
			"DayZExpansion_Scripts"
		};
    };
};
///////////////////////////////////////////////
class CfgMods
{
	class DZ_ModName_ExpansionLoadingScreen
	{
	    dir = "DayZ-Expansion-LoadingScreen-Sample"; //! Name of the mod
		picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
		name = "DayZExpansion Sample LoadingScreen";
		credits = "DayZ Expansion";
	    author = "DayZ Expansion";
	    authorID = "";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

		dependencies[]= 
		{
			"Game"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"DayZ-Expansion-LoadingScreen-Sample/Scripts/3_Game"
					//! Mod name/Scripts/3_Game
				};
			};
		};
    };
};
