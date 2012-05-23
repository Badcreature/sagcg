//
//  Filename:	UIObject.cpp
//	Created:	23:8:2011   15:39
//
//  This source code has been donated to the Public Domain.  Do
//  whatever you want with it.
//

/*
=========================================================================================

			HEADERS & DEFS

=========================================================================================
*/

#include	"StdAfx.h"
#ifdef GAMESWF
#include	"UIObject.h"
#include	"UIText.h"
#include	"../../Game/Game.h"
class Game;

/*
=========================================================================================

			CODE

=========================================================================================
*/

// ** cUIObject::cUIObject
cUIObject::cUIObject ( void )
{
	player		= new gameswf::player;
	root		= NULL;
	movie		= NULL;
	isVisible	= true;
}

cUIObject::cUIObject ( tSwfPlayer _player, tSwfCharacter _character )
{
	player		= _player;
	movie		= _character;
	root		= NULL;
	isVisible	= true;
}

cUIObject::~cUIObject ( void )
{
	/*	if ( root )  // ** Was loaded
		{
			delete player;
		}

		delete root;*/
}

// ** cUIObject::Load
bool cUIObject::Load ( const char *identifier )
{
	if ( root = player->load_file ( identifier ) )
	{
		movie = root->get_root_movie();
		root->set_userdata ( this );
		return true;
	}

	return false;
}

// ** cUIObject::SetMouseState
void cUIObject::SetMouseState ( int x, int y, bool pressed )
{
	if ( root )
	{
		root->notify_mouse_state ( x, y, pressed ? 1 : 0 );
	}
}

// ** cUIObject::Update
void cUIObject::Update ( float deltaTime, bool forceRealtimeFramerate )
{
	if ( deltaTime<=30.0f || deltaTime>119.9f )
	{
		deltaTime=33.0f;
	}

	if ( isVisible && root )
	{
		player->set_force_realtime_framerate ( forceRealtimeFramerate );
		root->advance ( ( 1.0f / root->get_frame_rate() ) + ( 1/ ( 100- ( 30-deltaTime ) ) ) );
	}
}

// ** cUIObject::Render
void cUIObject::Render ( int width, int height, bool background )
{
	if ( isVisible && root )
	{
		root->set_display_viewport ( 0, 0, width, height );
		root->set_background_alpha ( background ? 1.0f : 0.0f );
		root->display();
	}
}

// ** cUIObject::GetWidth
int cUIObject::GetWidth ( void ) const
{
	return root ? root->get_movie_width() : movie->get_movie_width();
}

// ** cUIObject::GetHeight
int cUIObject::GetHeight ( void ) const
{
	return root ? root->get_movie_height() : movie->get_movie_height();
}

// ** cUIObject::GetBackgroundColor
SColor cUIObject::GetBackgroundColor ( void ) const
{
	if ( !root )
	{
		return SColor ( 255, 0, 0, 0 );
	}

	const gameswf::rgba &color = root->get_background_color();
	return SColor ( color.m_a, color.m_r, color.m_g, color.m_b );
}

// ** cUIObject::GetFrameRate
float cUIObject::GetFrameRate ( void ) const
{
	return movie->get_movie_fps();
}

// ** cUIObject::GetBoolean
bool cUIObject::GetBoolean ( const char *path ) const
{
	const char *var = root->get_variable ( path );
	return !strcmp ( var, "false" ) ? false : true;
}

// ** cUIObject::GetVariableNumber
float cUIObject::GetNumber ( const char *path ) const
{
	return atof ( root->get_variable ( path ) );
}

// ** cUIObject::GetString
const char *cUIObject::GetString ( const char *path ) const
{
	return movie->get_variable ( path );
}

// ** cUIObject::SetValue
void cUIObject::SetValue ( const char *path, const char *value )
{
	movie->set_variable ( path, value );
}

// ** cUIObject::SetBoolean
void cUIObject::SetBoolean ( const char *path, bool value )
{
	movie->set_variable ( path, value ? "true" : "false" );
}

// ** cUIObject::SetNumber
void cUIObject::SetNumber ( const char *path, float value )
{
	static char buffer[33];
	snprintf ( buffer, 32, "%f", value );
	movie->set_variable ( path, buffer );
}

// ** cUIObject::SetString
void cUIObject::SetString ( const char *path, const wchar_t *value )
{
	movie->set_variable ( path, value );
}

// ** cUIObject::Play
void cUIObject::Play ( const char *clip )
{
	tSwfCharacter ch = movie;

	if ( clip )
	{
		if ( ( ch = FindCharacter ( clip ) ) == NULL )
		{
			printf ( "cUIObject::Play : no such clip %s\n", clip );
			return;
		}
	}

	ch->set_play_state ( gameswf::character::PLAY );
}

// ** cUIObject::Stop
void cUIObject::Stop ( const char *clip )
{
	tSwfCharacter ch = movie;

	if ( clip )
	{
		if ( ( ch = FindCharacter ( clip ) ) == NULL )
		{
			printf ( "cUIObject::Stop : no such clip %s\n", clip );
			return;
		}
	}

	ch->set_play_state ( gameswf::character::STOP );
}

// ** cUIObject::GotoAndPlay
bool cUIObject::GotoAndPlay ( const char *label, const char *clip )
{
	tSwfCharacter ch = movie;

	if ( clip )
	{
		if ( ( ch = FindCharacter ( clip ) ) == NULL )
		{
			printf ( "cUIObject::GotoAndPlay : no such clip %s\n", clip );
			return false;
		}
	}

	bool result = ch->goto_labeled_frame ( label );

	if ( result )
	{
		ch->set_play_state ( gameswf::character::PLAY );
	}

	return result;
}

// ** cUIObject::GotoAndStop
bool cUIObject::GotoAndStop ( const char *label, const char *clip )
{
	tSwfCharacter ch = movie;

	if ( clip )
	{
		if ( ( ch = FindCharacter ( clip ) ) == NULL )
		{
			printf ( "cUIObject::GotoAndStop : no such clip %s\n", clip );
			return false;
		}
	}

	bool result = ch->goto_labeled_frame ( label );

	if ( result )
	{
		ch->set_play_state ( gameswf::character::STOP );
	}

	return result;
}

// ** cUIObject::GotoAndPlay
void cUIObject::GotoAndPlay ( int frame, const char *clip )
{
	tSwfCharacter ch = movie;

	if ( clip )
	{
		if ( ( ch = FindCharacter ( clip ) ) == NULL )
		{
			printf ( "cUIObject::GotoAndPlay : no such clip %s\n", clip );
			return;
		}
	}

	ch->goto_frame ( frame );
	ch->set_play_state ( gameswf::character::PLAY );
}

// ** cUIObject::GotoAndStop
void cUIObject::GotoAndStop ( int frame, const char *clip )
{
	tSwfCharacter ch = movie;

	if ( clip )
	{
		if ( ( ch = FindCharacter ( clip ) ) == NULL )
		{
			printf ( "cUIObject::GotoAndStop : no such clip %s\n", clip );
			return;
		}
	}

	ch->goto_frame ( frame );
	ch->set_play_state ( gameswf::character::STOP );
}

// ** cUIObject::FindCharacter
tSwfCharacter cUIObject::FindCharacter ( const char *name )
{
	if ( gameswf::display_list *dl = movie->get_display_list() )
	{
		return dl->get_character_by_name ( name );
	}

	return NULL;
}

// ** cUIObject::FindTextByCaption
tSwfCharacter cUIObject::FindTextByCaption ( tSwfCharacter root, const char *caption )
{
	gameswf::display_list *dl = root->get_display_list();

	if ( !dl )
	{
		return NULL;
	}

	for ( int i = 0, n = dl->size(); i < n; i++ )
	{
		gameswf::character *ch = dl->get_character ( i );

		if ( ch->is ( gameswf::AS_EDIT_TEXT ) )
		{
			gameswf::edit_text_character *text = ( gameswf::edit_text_character * ) ch;
			const char *str = text->m_text.c_str();
			const char *cmpString = str;
			int cmpCount = strlen ( str );

			if ( const char *substring = strstr ( str, "</font>" ) )
			{
				cmpString = substring;
				cmpCount  = 0;

				// ** Search for <font ...>
				while ( *cmpString != '>' )
				{
					cmpString--;
					cmpCount++;
				}

				// ** Remove >
				cmpCount--;
				cmpString++;
			}

			char buf[256];
			strncpy ( buf, cmpString, cmpCount );

			if ( !strncmp ( cmpString, caption, cmpCount ) )
			{
				return ch;
			}
		}

		if ( ch = FindTextByCaption ( ch, caption ) )
		{
			return ch;
		}
	}

	return NULL;
}

// ** cUIObject::GetTextByCaption
cUIText *cUIObject::GetTextByCaption ( const char *caption )
{
	if ( tSwfCharacter text = FindTextByCaption ( movie, caption ) )
	{
		return new cUIText ( player, text );
	}

	return NULL;
}

// ** cUIObject::DispatchCommand
void cUIObject::DispatchCommand ( const char *command, const char *args )
{
	Game::getInstance()->GameSWFEvent ( command,args );
}

// ** cUIObject::SetVisible
void cUIObject::SetVisible ( bool visible )
{
	isVisible = visible;
}

// ** cUIObject::IsVisible
bool cUIObject::IsVisible ( void ) const
{
	return isVisible;
}
#endif //#ifdef GAMESWF
