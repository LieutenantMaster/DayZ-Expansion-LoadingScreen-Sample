/*
	EXAMPLE 02
		Custom loading screen with also the loading screen of Expansion Enabled
*/

const string LOADING_SCREENS_PATH = "DayZ-Expansion-LoadingScreen-Sample/LoadingScreen/Data/loading";
const int LOADING_SCREENS_COUNT = 3; //! The amount of pictures for the loading screen starting from 1

modded class LoadingScreen 
{
	override void Show()
	{
		for (int i = 1; i <= LOADING_SCREENS_COUNT; i++) {
			m_Backgrounds.Insert(new ExpansionLoadingScreenBackground(LOADING_SCREENS_PATH + i + ".edds"));
		}

		super.Show();
	};
};
 
modded class LoginQueueBase 
{
	void LoginQueueBase()
	{
		for (int i = 1; i <= LOADING_SCREENS_COUNT; i++) {
			m_Backgrounds.Insert(new ExpansionLoadingScreenBackground(LOADING_SCREENS_PATH + i + ".edds"));
		}
	};
};
 
modded class LoginTimeBase 
{
	void LoginTimeBase()
	{
		for (int i = 1; i <= LOADING_SCREENS_COUNT; i++) {
			m_Backgrounds.Insert(new ExpansionLoadingScreenBackground(LOADING_SCREENS_PATH + i + ".edds"));
		}
	};
};