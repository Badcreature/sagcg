//
//  Filename:	UIText.cpp
//	Created:	27:8:2011   13:21
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
#include	"UIText.h"

/*
=========================================================================================

			CODE

=========================================================================================
*/

// ** cUIText::cUIText
cUIText::cUIText ( tSwfPlayer player, tSwfCharacter character ) : cUIObject ( player, character )
{
}

// ** cUIText::SetText
void cUIText::SetText ( const wchar_t *text )
{
	gameswf::edit_text_character *txt = ( gameswf::edit_text_character * ) movie;
	tu_string::encode_utf8_from_wchar ( &txt->m_text, ( uint16 * ) text );
	txt->format_text();
}

// ** cUIText::GetText
const char *cUIText::GetText ( void ) const
{
	return NULL;
}

#endif //#ifdef GAMESWF