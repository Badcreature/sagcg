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
#include "StdAfx.h"
#include "Game/Game.h"
#include "GSBaseState.h"
#include "GSSelectlanguage.h"
#include "GSTested_State.h"
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StateName
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *GSBaseState::getStateName() const
{
	return "GSBaseState";
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSBaseState::GSBaseState()
{
	Logs::debug ( "GSBaseState\n" );
	m_isGame = Game::getInstance();
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );
	m_isGameStarted=false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSBaseState::~GSBaseState()
{
	Logs::debug ( "~GSBaseState\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State CTOR (when added to the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSBaseState::ctor	( const StateMachine *sm )
{
	Logs::debug ( "State GSBaseState::ctor\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State DTOR (when removed from the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSBaseState::dtor	( const StateMachine *sm )
{
	Logs::debug ( "State GSBaseState::dtor\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State update (game update: update)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSBaseState::update ( StateMachine *sm )
{
	Logs::debug ( "State GSBaseState::update\n" );

	if ( m_isGame->getGameIsRun() )
	{
		if ( !m_isGameStarted )
		{
			//m_isStateMachine->pushState<GSTested_State>();
			m_isStateMachine->pushState<GSSelectlanguage>();
			m_isGameStarted=true;
		}
	}
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State pause (when a new state is added atop)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSBaseState::pause	( const StateMachine *sm )
{
	Logs::debug ( "State GSBaseState::pause\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State resume (when the state above is removed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSBaseState::resume	( const StateMachine *sm )
{
	Logs::debug ( "State GSBaseState::resume\n" );
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw (game update: draw)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSBaseState::draw	( const StateMachine *sm )
{
	Logs::debug ( "State GSBaseState::draw\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw2d (draw 2d elements in front)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSBaseState::draw2d	( const StateMachine *sm )
{
	Logs::debug ( "State GSBaseState::draw2d\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State sleep (application is interrupted)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSBaseState::sleep	( const StateMachine *sm )
{
	Logs::debug ( "State GSBaseState::sleep\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State wakeup (application is resumed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSBaseState::wakeup	( const StateMachine *sm )
{
	Logs::debug ( "State GSBaseState::wakeup\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Update and Draw(draw2d) regardless of pause)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSBaseState::isWorkingInParallel()
{
return true;
}
*/

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Loding screen Disable. )
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSBaseState::isLoadingDisable()
{
return true;
}
*/


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EReceiver
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	GSBaseState::onEvent ( const EEvent *ev, const EventManager *evMgr )
{
	Logs::debug ( "State GSBaseState onEvent\n" );
}


