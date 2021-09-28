const string MUSIC_SOUNDSET 	= "MyMod_Music_1_SoundSet";

const bool UseCustomMusic = true;

modded class MissionMainMenu
{
	override void PlayMusic()
	{
        if ( UseCustomMusic )
        {
            if ( !m_MenuMusic )
            {
                SoundParams soundParams			= new SoundParams( MUSIC_SOUNDSET );
                SoundObjectBuilder soundBuilder	= new SoundObjectBuilder( soundParams );
                SoundObject soundObject			= soundBuilder.BuildSoundObject();
                soundObject.SetKind( WaveKind.WAVEMUSIC );
                m_MenuMusic = GetGame().GetSoundScene().Play2D(soundObject, soundBuilder);
                m_MenuMusic.Loop( true );
                m_MenuMusic.Play();
            }
        } else {
		    super.PlayMusic();
        }
	}
};