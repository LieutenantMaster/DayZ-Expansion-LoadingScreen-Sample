/*
	EXAMPLE 05
		No Custom loading screen
		Custom loading messages without the loading messages of Expansion
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
			m_MessageRest = m_MessageJson.GetRandomElement();

			m_LoadingMessage.SetText( m_MessageRest.message );
			m_LoadingMessageAuthor.SetText( "#STR_EXPANSION_LOADING_MSG_SUBMITTEDBY" + " " + m_MessageRest.submitter );
		}

		super.Show();
	};
};