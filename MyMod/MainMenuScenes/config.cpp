/**
 * config.cpp
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class CfgPatches
{
    class ModName_ExpansionMainMenuScenes
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]= 
        { 
            "DayZExpansion_Worlds_IntroScenes"
        };
    };
};

class cfgExpansionCharacterScenes
{
    class ChernarusPlus // The name of the map
    {
        class MySceneName // The name of your scene
        {
            CameraPosition[]={3709.27,403.95,5969.98};      // Where the camera should be in your scene
            CameraOrientation[]={8.0,0.0,0.0};              // And where the camera should look at
            PlayerPosition[]={3709.31, 402.012, 5972.07};   // Where your character will be displayed
            PlayerOrientation[]={33.0, 0, -0};              // And where it will look at
            fov=0.8;        // fov of the camera
            date[]=         // year, month, day, hour, minute
            {
                2021,
                7,
                4,
                9,
                0
            };
            overcast=0.8;   // How much overcast (clouds) it will have
            rain=0.7;       // How much rain it will have
            fog=0.6;        // How much fog it will have
            windspeed=0.6;  // Speed of the wind
            MappingFiles[]=
            {
                "MyMod/MainMenuScenes/MyMapFile" // The path to your .map file, it allows you to load a custom mapping to your scene
            };
            CustomPose=-1;  // if you want a custom animation, you need to enter the animation ID instead of "-1"
            HandItem="";    // should the player hold a specific item in his hands, if yes, add the classname in this line
            CanRotate=1;    // Can the player rotate his character ?
        };     
    };
};