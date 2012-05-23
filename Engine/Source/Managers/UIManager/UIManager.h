//
//  Filename:	UIManager.h
//	Created:	23:8:2011   15:26
//
//  This source code has been donated to the Public Domain.  Do
//  whatever you want with it.
//

#ifndef		__UIManager_H__
#define		__UIManager_H__

/*
=========================================================================================

			HEADERS & DEFS

=========================================================================================
*/

#include	"../stdafx.h"

/*
=========================================================================================

			CODE

=========================================================================================
*/

// ** class cUIManager
class cUIManager
{
	private:

		tSwfRenderer	renderer;
		tUIObjectList	uiObjects;
		tSwfPlayer			player_null;

	private:

		tSwfPlayer		CreatePlayerInstance ( void );

		static tSwfFile	FileOpener ( const char *identifier );
		static void		FsCallback ( tSwfCharacter movie, const char *command, const char *args );
		static void		LogCallback ( bool error, const char *message );

	public:

		cUIManager ( void );
		virtual			~cUIManager ( void );

		cUIObject		*CreateUIObject ( const char *identifier );
		void			ReleaseUIObject ( cUIObject *uiObject );
		void			Update ( float deltaTime=60, bool forceRealtimeFramerate=true );
		void            UpdateMouseState ( int cursorX, int cursorY, bool mousePressed=false );
		void			Render ( int width, int height, bool background );
};

#endif	/*	!__UIManager_H__	*/
