/*
	EXAMPLE 04
		Custom loading screen without the loading screen of Expansion
		Custom loading messages mixed with the loading messages of Expansion
*/

const string LOADING_SCREENS_PATH = "DayZ-Expansion-LoadingScreen-Sample/LoadingScreen/Data/loading";
const int LOADING_SCREENS_COUNT = 3; //! The amount of pictures for the loading screen starting from 1

//! Remove this code if you want to use the expansion loading messages and not your own messages
const string LOADING_MESSAGES_PATH = "DayZ-Expansion-LoadingScreen-Sample/LoadingScreen/Data/messages.json";
 
modded class LoadingScreen 
{
	//! Remove this code if you want to use the expansion loading messages and not your own messages
	protected autoptr array< ref ExpansionLoadingScreenMessageData > m_MessageJson;

	void LoadingScreen(DayZGame game)
	{
		//! Remove this code if you want to use the expansion loading messages and not your own messages
		JsonFileLoader< ref array< ref ExpansionLoadingScreenMessageData > >.JsonLoadFile( LOADING_MESSAGES_PATH, m_MessageJson );
	};

	override void Show()
	{
		m_Backgrounds.Clear(); //! Remove me if you also want to see the expansion loading screens
		for (int i = 1; i <= LOADING_SCREENS_COUNT; i++) {
			m_Backgrounds.Insert(new ExpansionLoadingScreenBackground(LOADING_SCREENS_PATH + i + ".edds"));
		}

		//! Remove this code if you want to use the expansion loading messages and not your own messages
		if ( m_MessageJson )
		{
			//! 60% chance of using the custom message instead of expansion message
			if ( Math.RandomFloat( 0, 1.0 ) > 0.6 )
			{
				m_MessageRest = m_MessageJson.GetRandomElement();

				m_LoadingMessage.SetText( m_MessageRest.message );
				m_LoadingMessageAuthor.SetText( "#STR_EXPANSION_LOADING_MSG_SUBMITTEDBY" + " " + m_MessageRest.submitter );
			}
		}
		//! Remove this code if you want to use the expansion loading messages and not your own messages
		
		super.Show();
	};
};
 
modded class LoginQueueBase 
{
	void LoginQueueBase()
	{
		m_Backgrounds.Clear(); //! Remove me if you also want to see the expansion loading screens
		for (int i = 1; i <= LOADING_SCREENS_COUNT; i++) {
			m_Backgrounds.Insert(new ExpansionLoadingScreenBackground(LOADING_SCREENS_PATH + i + ".edds"));
		}
	};
};
 
modded class LoginTimeBase 
{
	void LoginTimeBase()
	{
		m_Backgrounds.Clear(); //! Remove me if you also want to see the expansion loading screens
		for (int i = 1; i <= LOADING_SCREENS_COUNT; i++) {
			m_Backgrounds.Insert(new ExpansionLoadingScreenBackground(LOADING_SCREENS_PATH + i + ".edds"));
		}
	};
};