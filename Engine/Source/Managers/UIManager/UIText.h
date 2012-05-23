//
//  Filename:	UIText.h
//	Created:	27:8:2011   13:04
//
//  This source code has been donated to the Public Domain.  Do
//  whatever you want with it.
//
#ifndef		__UIText_H__
#define		__UIText_H__

/*
=========================================================================================

			HEADERS & DEFS

=========================================================================================
*/

#include	"UIObject.h"

/*
=========================================================================================

			CODE

=========================================================================================
*/

// ** class cUIText
class cUIText : public cUIObject
{
	public:

		cUIText ( tSwfPlayer player, tSwfCharacter character );

		void			SetText ( const wchar_t *text );
		const char		*GetText ( void ) const;
};

#endif	/*	!__UIText_H__	*/
