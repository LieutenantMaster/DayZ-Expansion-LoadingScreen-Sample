/*
	Advanced Example 02
		Custom Logo
		Custom Loading Bar color
		Custom loading screen based on the map without the loading screen of Expansion
		Custom loading messages mixed with the loading messages of Expansion


	Each edds files will need to be named :
		loading_mapnamenumber.edds

	example:
		loading_chernarusplus1.edds
		loading_chernarusplus2.edds
		loading_chernarusplus3.edds
		loading_enoch1.edds
		loading_enoch2.edds
		loading_enoch3.edds
		loading_deerisle1.edds
		loading_deerisle2.edds
		loading_deerisle3.edds

	You will need the same amount of pictures for every maps you will be using

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
		
		//! My logo here
		m_ImageLogoMid.LoadImageFile( 0, "set:expansion_iconset image:logo_expansion_white" );
		m_ImageLogoCorner.LoadImageFile( 0, "set:expansion_iconset image:logo_expansion_white" );

		//! My colored progress bar
		m_ProgressLoading.SetColor( ARGB( 255, 0, 0, 255 ) );
	};

	override void Show()
	{
		string world_name = "empty";
		GetGame().GetWorldName(world_name);
		world_name.ToLower();

		m_Backgrounds.Clear(); //! Remove me if you also want to see the expansion loading screens
		for (int i = 1; i <= LOADING_SCREENS_COUNT; i++) {
			m_Backgrounds.Insert(new ExpansionLoadingScreenBackground(LOADING_SCREENS_PATH + "_" + world_name + i + ".edds"));
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
		string world_name = "empty";
		GetGame().GetWorldName(world_name);
		world_name.ToLower();

		m_Backgrounds.Clear(); //! Remove me if you also want to see the expansion loading screens
		for (int i = 1; i <= LOADING_SCREENS_COUNT; i++) {
			m_Backgrounds.Insert(new ExpansionLoadingScreenBackground(LOADING_SCREENS_PATH + "_" + world_name + i + ".edds"));
		}
	};
};
 
modded class LoginTimeBase 
{
	void LoginTimeBase()
	{
		string world_name = "empty";
		GetGame().GetWorldName(world_name);
		world_name.ToLower();

		m_Backgrounds.Clear(); //! Remove me if you also want to see the expansion loading screens
		for (int i = 1; i <= LOADING_SCREENS_COUNT; i++) {
			m_Backgrounds.Insert(new ExpansionLoadingScreenBackground(LOADING_SCREENS_PATH + "_" + world_name + i + ".edds"));
		}
	};
};