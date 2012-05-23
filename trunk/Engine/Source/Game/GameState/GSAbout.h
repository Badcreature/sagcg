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
#ifndef GAME_STATES_GSAbout_H
#define GAME_STATES_GSAbout_H

#include "StateBase.h"
#include "EEventReceiver.h"

class StateMachine;
class EventManager;
class Game;
class cUIObject;
class GSAbout
	: public StateBase, public EEventReceiver
{

		friend class	StateMachine;

	private:

		GSAbout();

	public:

		virtual			~GSAbout();
		const char 	*getStateName() const;		// Return StateName
		void	ctor		( const StateMachine *sm );	// when added to the StateMachine stack
		void	dtor		( const StateMachine *sm );	// when removed from the StateMachine stack

		void	update		( StateMachine *sm );

		void	pause		( const StateMachine *sm );	// when a new state is added atop
		void	resume		( const StateMachine *sm );	// when the state above is removed

		// External callbacks

		void	draw		( const StateMachine *sm );	// game update: draw
		void	draw2d		( const StateMachine *sm );	// draw 2d elements in front
		void	sleep		( const StateMachine *sm );	// application is interrupted
		void	wakeup		( const StateMachine *sm );	// application is resumed

		// Configuration state
		/*
				bool	isWorkingInParallel(); //If this option is true the state Update and Draw(draw2d) regardless of pause
		*/

		/*
				bool	isLoadingDisable(); //If this option is true the state Loding screen Disable.
		*/

		// EReceiver
		virtual void	onEvent ( const EEvent *ev, const EventManager *evMgr );


	private:

		StateMachine 		*m_isStateMachine;
		EventManager 		*m_isEventManager;
		Game 				*m_isGame;
	public:
		cUIObject			*m_UIObject;
};

#endif // GAME_STATES_GSAbout_H
