/*
	EXAMPLE 06
		No Custom loading screen
		Custom loading messages mixed with the loading messages of Expansion
*/

const string LOADING_MESSAGES_PATH = "DayZ-Expansion-LoadingScreen-Sample/LoadingScreen/Data/messages.json";
 
modded class LoadingScreen 
{
	protected autoptr array< ref ExpansionLoadingScreenMessageData > m_MessageJson;

	void LoadingScreen(DayZGame game)
	{
		JsonFileLoader< ref array< ref ExpansionLoadingScreenMessageData > >.JsonLoadFile( LOADING_MESSAGES_PATH, m_MessageJson );
	};

	override void Show()
	{
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

		super.Show();
	};
};