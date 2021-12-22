/**
 * config.cpp
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

/*

This file is only required if you want a custom music in the main menu
If you do not want custom music, delete this file

*/

class CfgPatches
{
	class ModName_ExpansionCustomMusic
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
        {
            "DZ_Sounds_Effects"
        };
	};
};

class CfgSoundShaders
{
	class MyMod_Music_1_SoundShader
	{
        // music from https://freesound.org/people/InspectorJ/sounds/369147/
		samples[] = {{"MyMod\CustomMusic\mymusic",1}};
		volume=0.70794576;
	};
};

class CfgSoundSets
{	
	class MyMod_Music_1_SoundSet
	{
		soundShaders[]=
		{
			"MyMod_Music_1_SoundShader"
		};
		volumeFactor=1;
		frequencyFactor=1;
		spatial=0;
	};
};