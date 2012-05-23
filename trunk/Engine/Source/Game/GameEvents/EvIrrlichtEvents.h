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
// EvKeyboard
//
//		Keyboard events
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef GAME_EVENTS_EVIrrlichtEvents_H
#define GAME_EVENTS_EVIrrlichtEvents_H
#include "StdAfx.h"
#include "EEventReceiver.h"
#include "EEvent.h"
#include "EventManager.h"
#include "irrlicht.h"


// ** Main Class
// ////////////////////////////////////////////////////////
class EvIrrlichtEvents : public EEvent
{
		// ** Structs
		// ////////////////////////////////////////////////////////

		// ** Typedefs
		// ////////////////////////////////////////////////////////
	private:
		typedef irr::SEvent		IRRLICHT_EVENT;
		//typedef int		IRRLICHT_EVENT;
		// ** Members
		// ////////////////////////////////////////////////////////
	public:
		IRRLICHT_EVENT		irr_event;

		// ** Ctors / Dtor
		// ////////////////////////////////////////////////////////
	public:
		EvIrrlichtEvents ( IRRLICHT_EVENT _irr_event ) :
			EEvent ( Events::IRRLICHT_EVENT ),
			irr_event ( _irr_event )
		{};

		virtual	~EvIrrlichtEvents() {};

};


#endif