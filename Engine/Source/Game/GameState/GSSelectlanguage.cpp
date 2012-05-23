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
#include "Managers/UIManager/UIObject.h"
#include "GSSelectlanguage.h"
#include "GSMainMenu.h"


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StateName
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *GSSelectlanguage::getStateName() const
{
	return "GSSelectlanguage";
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSSelectlanguage::GSSelectlanguage()
{
	Logs::info ( "GSSelectlanguage\n" );
	m_isGame = Game::getInstance();
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );
	m_UIObject=0;
	m_exitState=false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSSelectlanguage::~GSSelectlanguage()
{
	Logs::info ( "~GSSelectlanguage\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State CTOR (when added to the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSSelectlanguage::ctor	( const StateMachine *sm )
{
	Logs::info ( "State GSSelectlanguage::ctor\n" );
	m_isEventManager->attach ( Events::IRRLICHT_EVENT, this );
	m_isEventManager->attach ( Events::GAME_SWF_EVENT, this );
	m_UIObject=m_isGame->getUIManager()->CreateUIObject ( "data/swf/GSSelectlanguage.swf" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State DTOR (when removed from the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSSelectlanguage::dtor	( const StateMachine *sm )
{
	Logs::info ( "State GSSelectlanguage::dtor\n" );
	m_isEventManager->detach ( Events::IRRLICHT_EVENT, this );
	m_isEventManager->detach ( Events::GAME_SWF_EVENT, this );

	if ( m_UIObject )
	{
		m_isGame->getUIManager()->ReleaseUIObject ( m_UIObject );
		m_UIObject=0;
	}

	m_isStateMachine->loadState<GSMainMenu>();
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State update (game update: update)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSSelectlanguage::update ( StateMachine *sm )
{
	Logs::debug ( "State GSSelectlanguage::update\n" );

	if ( m_exitState )
	{
		m_isStateMachine->popState();
	}
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State pause (when a new state is added atop)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSSelectlanguage::pause	( const StateMachine *sm )
{
	Logs::info ( "State GSSelectlanguage::pause\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State resume (when the state above is removed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSSelectlanguage::resume	( const StateMachine *sm )
{
	Logs::info ( "State GSSelectlanguage::resume\n" );
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw (game update: draw)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSSelectlanguage::draw	( const StateMachine *sm )
{
	Logs::debug ( "State GSSelectlanguage::draw\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw2d (draw 2d elements in front)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSSelectlanguage::draw2d	( const StateMachine *sm )
{
	Logs::debug ( "State GSSelectlanguage::draw2d\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State sleep (application is interrupted)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSSelectlanguage::sleep	( const StateMachine *sm )
{
	Logs::info ( "State GSSelectlanguage::sleep\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State wakeup (application is resumed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSSelectlanguage::wakeup	( const StateMachine *sm )
{
	Logs::info ( "State GSSelectlanguage::wakeup\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Update and Draw(draw2d) regardless of pause)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSSelectlanguage::isWorkingInParallel()
{
return true;
}
*/

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Loding screen Disable. )
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSSelectlanguage::isLoadingDisable()
{
return true;
}
*/


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EReceiver
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	GSSelectlanguage::onEvent ( const EEvent *ev, const EventManager *evMgr )
{
	Logs::debug ( "State GSSelectlanguage onEvent\n" );

	switch ( ev->getEventID() )
	{
		case Events::IRRLICHT_EVENT:
			Logs::debug ( "IRRLICHT_EVENT onEvent\n" );
			break;

		case Events::GAME_SWF_EVENT:
			Logs::info ( "GAME_SWF_EVENT onEvent\n" );
			const char *CommandSWF=static_cast<const EvGameSWFEvent *> ( ev )->command;
			const char *ArgsSWF=static_cast<const EvGameSWFEvent *> ( ev )->args;

			if ( strcmp ( "LANG", CommandSWF ) ==0 )
			{
				if ( strcmp ( "EN", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_EN );//0
					Logs::info ( "setLanguage ( LANGUAGE_EN )\n" );
				}

				else if ( strcmp ( "FR", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_FR );//1
					Logs::info ( "setLanguage ( LANGUAGE_FR )\n" );
				}

				else if ( strcmp ( "DE", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_DE );//2
					Logs::info ( "setLanguage ( LANGUAGE_DE )\n" );
				}

				else if ( strcmp ( "SP", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_SP );//3
					Logs::info ( "setLanguage ( LANGUAGE_SP )\n" );
				}

				else if ( strcmp ( "IT", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_IT );//4
					Logs::info ( "setLanguage ( LANGUAGE_IT )\n" );
				}

				else if ( strcmp ( "JP", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_JP );//5
					Logs::info ( "setLanguage ( LANGUAGE_JP )\n" );
				}

				else if ( strcmp ( "RU", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_RU );//6
					Logs::info ( "setLanguage ( LANGUAGE_RU )\n" );
				}

				else if ( strcmp ( "KO", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_KO );//7
					Logs::info ( "setLanguage ( LANGUAGE_KO )\n" );
				}

				else if ( strcmp ( "CN", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_CN );//8
					Logs::info ( "setLanguage ( LANGUAGE_CN )\n" );
				}

				else if ( strcmp ( "BR", ArgsSWF ) ==0 )
				{
					m_isGame->setLanguage ( LANGUAGE_BR );//9
					Logs::info ( "setLanguage ( LANGUAGE_BR )\n" );
				}

				else
				{
					m_isGame->setLanguage ( LANGUAGE_EN );//0
					Logs::info ( "setLanguage ( LANGUAGE_UNKNOWN )\n" );
				}

				m_exitState=true;
			}

			break;
	}
}



