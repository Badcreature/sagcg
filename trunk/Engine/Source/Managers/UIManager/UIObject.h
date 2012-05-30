//
//  Filename:	UIObject.h
//	Created:	23:8:2011   15:31
//
//  This source code has been donated to the Public Domain.  Do
//  whatever you want with it.
//

#ifndef		__UIObject_H__
#define		__UIObject_H__

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

// ** class cUIObject
class cUIObject
{
		friend class cUIManager;
	protected:

		tSwfPlayer			player;
		tSwfRoot			root;
		tSwfCharacter		movie;
		bool				isVisible;

	private:

		tSwfCharacter		FindCharacter ( const char *name );
		tSwfCharacter		FindTextByCaption ( tSwfCharacter root, const char *caption );
		void				DispatchCommand ( const char *command, const char *args );

	public:

		cUIObject ( void );
		cUIObject ( tSwfPlayer player, tSwfCharacter character );
		virtual				~cUIObject ( void );

		bool				Load ( const char *identifier );
		void				Update ( float deltaTime, bool forceRealtimeFramerate );
		void				Render ( int width, int height, bool background );
		void				Play ( const char *clip = NULL );
		void				Stop ( const char *clip = NULL );
		bool				GotoAndPlay ( const char *label, const char *clip = NULL );
		bool				GotoAndStop ( const char *label, const char *clip = NULL );
		void				GotoAndPlay ( int frame, const char *clip = NULL );
		void				GotoAndStop ( int frame, const char *clip = NULL );
		void				SetMouseState ( int *x, int *y, int countXY , bool *pressed );

		void				SetVisible ( bool visible );
		bool				IsVisible ( void ) const;
		int					GetWidth ( void ) const;
		int					GetHeight ( void ) const;
		SColor				GetBackgroundColor ( void ) const;
		float				GetFrameRate ( void ) const;
		cUIText				*GetTextByCaption ( const char *caption );
		bool				IsAVM2 ( void ) const;

		// ** C++/Flash Interop
		bool				GetBoolean ( const char *path ) const;
		float				GetNumber ( const char *path ) const;
		const char			*GetString ( const char *path ) const;
		void				SetBoolean ( const char *path, bool value );
		void				SetValue ( const char *path, const char *value );
		void				SetNumber ( const char *path, float value );
		void				SetString ( const char *path, const wchar_t *value );
};

#endif	/*	!__UIObject_H__	*/
