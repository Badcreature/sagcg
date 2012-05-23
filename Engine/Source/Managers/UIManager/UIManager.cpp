//
//  Filename:	UIManager.cpp
//	Created:	23:8:2011   15:27
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

#include	"UIManager.h"
#include	"UIObject.h"

/*
=========================================================================================

			CODE

=========================================================================================
*/

// ** cUIManager::cUIManager
cUIManager::cUIManager ( void )
{
#ifdef WIN32
	renderer = gameswf::create_render_handler_ogl();
#else
	renderer = gameswf::create_render_handler_ogles();
#endif
	player_null		= new gameswf::player;
	gameswf::register_file_opener_callback ( FileOpener );
	gameswf::register_fscommand_callback ( FsCallback );
	gameswf::set_render_handler ( renderer );
	gameswf::set_glyph_provider ( gameswf::create_glyph_provider_freetype() );
	renderer->open();
}

cUIManager::~cUIManager ( void )
{
}

// ** cUIManager::CreateUIObject
cUIObject *cUIManager::CreateUIObject ( const char *identifier )
{
	cUIObject *uiObject = new cUIObject;

	if ( !uiObject->Load ( identifier ) )
	{
		delete uiObject;
		uiObject = NULL;
	}

	else
	{
		uiObjects.push_back ( uiObject );
	}

	return uiObject;
}

// ** cUIManager::Update
void cUIManager::Update ( float deltaTime, bool forceRealtimeFramerate )
{
	for ( tUIObjectList::iterator i = uiObjects.begin(), end = uiObjects.end(); i != end; i++ )
	{
		( *i )->Update ( deltaTime, forceRealtimeFramerate );
	}
}

void cUIManager::UpdateMouseState ( int cursorX, int cursorY, bool mousePressed )
{
	for ( tUIObjectList::iterator i = uiObjects.begin(), end = uiObjects.end(); i != end; i++ )
	{
		( *i )->SetMouseState ( cursorX, cursorY, mousePressed );
	}
}

// ** cUIManager::Render
void cUIManager::Render ( int width, int height, bool background )
{
	for ( tUIObjectList::iterator i = uiObjects.begin(), end = uiObjects.end(); i != end; i++ )
	{
		( *i )->Render ( width, height, background );
	}
}

// ** cUIManager::ReleaseUIObject
void cUIManager::ReleaseUIObject ( cUIObject *uiObject )
{
	tUIObjectList::iterator i = std::find ( uiObjects.begin(), uiObjects.end(), uiObject );

	if ( i != uiObjects.end() )
	{
		delete *i;
		uiObjects.erase ( i );
	}
}

// ** cUIManager::FileOpener
tSwfFile cUIManager::FileOpener ( const char *identifier )
{
	return new tu_file ( identifier, "rb" );
}

// ** cUIManager::FsCallback
void cUIManager::FsCallback ( tSwfCharacter movie, const char *command, const char *args )
{
	if ( cUIObject *uiObject = ( cUIObject * ) movie->get_root()->get_userdata() )
	{
		uiObject->DispatchCommand ( command, args );
	}
}

// ** cUIManager::LogCallback
void cUIManager::LogCallback ( bool error, const char *message )
{
	if ( gameswf::get_verbose_parse() )
	{
		static FILE *file = NULL;

		if ( !file )
		{
			file = fopen ( "swf_parse.txt", "wt" );
		}

		fputs ( message, file );
		fflush ( file );
		printf ( message );
	}

	if ( gameswf::get_verbose_action() )
	{
		static FILE *file = NULL;

		if ( !file )
		{
			file = fopen ( "swf_action.txt", "wt" );
		}

		fputs ( message, file );
		fflush ( file );
		printf ( message );
	}
}

