// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Created by Andrey Sidorov.
//	Copyright (C) 2012 Andrey Sidorov.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								  License.
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
//  Please note that the SaGCG (simple-and-good-core-games) Engine is based in part on the work of the
//  Independent JPEG Group, zlib,libPng, Box2D, freetype, bullet, OpenAL, gameswf This means that if you use
//  the SaGCG (simple-and-good-core-games) Engine in your product, you must acknowledge somewhere in your
//  documentation that you've used the IJG code. It would also be nice to mention
//  that you use the SaGCG (simple-and-good-core-games)Engine, Irrlicht Engine, zlib, libPng, Box2D, freetype,
//  bullet, OpenAL, gameswf. See the README files in the jpeglib, zlib, libPng, Box2D, freetype, bullet, OpenAL,
//  gameswf for further informations.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		EvGameCharacterEvent events
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef GAME_EVENTS_EvGameCharacterEvent_H
#define GAME_EVENTS_EvGameCharacterEvent_H
#include "StdAfx.h"
#include "EEventReceiver.h"
#include "EEvent.h"
#include "EventManager.h"


// ** Main Class
// ////////////////////////////////////////////////////////
class EvGameCharacterEvent : public EEvent
{
		// ** Structs
		// ////////////////////////////////////////////////////////
	public:
		struct CharacterData
		{
			bool	 MovementForward;
			bool	 MovementBack;
			bool	 MovementLeft;
			bool	 MovementRight;
			bool	 Jump;
			bool	 Action0;
			bool	 Action1;
			bool	 Action2;
			bool	 Action3;
			bool	 Action4;
			bool	 Action5;
			bool	 Action6;
			bool	 Action7;
			CharacterData ()
			{
				MovementForward=false;
				MovementBack=false;
				MovementLeft=false;
				MovementRight=false;
				Jump=false;
				Action0=false;
				Action2=false;
				Action3=false;
				Action4=false;
				Action5=false;
				Action6=false;
				Action7=false;
			}
		};

		// ** Typedefs
		// ////////////////////////////////////////////////////////
	public:
		typedef CharacterData			CHARACTER_DATA_EVENT;
		typedef const char				CHARACTER_NAME_EVENT;
		// ** Members
		// ////////////////////////////////////////////////////////
	public:
		CHARACTER_DATA_EVENT		data;
		CHARACTER_NAME_EVENT		*name;

		// ** Ctors / Dtor
		// ////////////////////////////////////////////////////////
	public:
		EvGameCharacterEvent ( CHARACTER_DATA_EVENT _data , CHARACTER_NAME_EVENT *_name ) :
			EEvent ( Events::CHARACTER_EVENT ),
			data ( _data ),
			name ( _name )
		{};

		virtual	~EvGameCharacterEvent() {};

};


#endif //GAME_EVENTS_EvGameCharacterEvent_H