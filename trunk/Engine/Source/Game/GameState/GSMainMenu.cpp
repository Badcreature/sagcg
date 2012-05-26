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
#include "GSMainMenu.h"
#include "GSTested_State.h"
#include "StringManager.h"
#include "GSNewGame.h"
#include "GSLoadGame.h"
#include "GSAbout.h"
#include "GSSelectlanguage.h"

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StateName
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *GSMainMenu::getStateName() const
{
	return "GSMainMenu";
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSMainMenu::GSMainMenu()
{
	Logs::info ( "GSMainMenu\n" );
	m_isGame = Game::getInstance();
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );
	m_UIObject=0;
	m_exitState=0;
	m_nextState=0;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSMainMenu::~GSMainMenu()
{
	Logs::info ( "~GSMainMenu\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State CTOR (when added to the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMainMenu::ctor	( const StateMachine *sm )
{
	Logs::info ( "State GSMainMenu::ctor\n" );
	m_isEventManager->attach ( Events::IRRLICHT_EVENT, this );
	m_isEventManager->attach ( Events::GAME_SWF_EVENT, this );
	m_UIObject=m_isGame->getUIManager()->CreateUIObject ( "data/swf/GSMainMenu.swf" );
	m_UIObject->SetString ( "_root.textbutton1.text", StringManager::getInstance()->getTextByID ( L"NEW_GAME" ) );
	m_UIObject->SetString ( "_root.textbutton2.text", StringManager::getInstance()->getTextByID ( L"LOADING" ) );
	m_UIObject->SetString ( "_root.textbutton3.text", StringManager::getInstance()->getTextByID ( L"CREDITS" ) );
	m_UIObject->SetString ( "_root.textbutton4.text", StringManager::getInstance()->getTextByID ( L"GAME_INFOS" ) );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State DTOR (when removed from the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMainMenu::dtor	( const StateMachine *sm )
{
	Logs::info ( "State GSMainMenu::dtor\n" );
	m_isEventManager->detach ( Events::IRRLICHT_EVENT, this );
	m_isEventManager->detach ( Events::GAME_SWF_EVENT, this );

	if ( m_UIObject )
	{
		m_isGame->getUIManager()->ReleaseUIObject ( m_UIObject );
		m_UIObject=0;
	}

	if ( m_nextState==SELECT_ABOUTGAME )
	{
		m_isStateMachine->loadState<GSLoadGame>();
	}

	else if ( m_nextState==SELECT_LOADGAME )
	{
		m_isStateMachine->loadState<GSAbout>();
	}

	else if ( m_nextState==SELECT_NEWGAME )
	{
		m_isStateMachine->loadState<GSNewGame>();
	}

	else if ( m_nextState==SELECT_BACK )
	{
		m_isStateMachine->loadState<GSSelectlanguage>();
	}
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State update (game update: update)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMainMenu::update ( StateMachine *sm )
{
	Logs::debug ( "State GSMainMenu::update\n" );

	if ( m_exitState )
	{
		m_isStateMachine->popState();
	}
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State pause (when a new state is added atop)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMainMenu::pause	( const StateMachine *sm )
{
	Logs::info ( "State GSMainMenu::pause\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State resume (when the state above is removed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMainMenu::resume	( const StateMachine *sm )
{
	Logs::info ( "State GSMainMenu::resume\n" );
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw (game update: draw)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMainMenu::draw	( const StateMachine *sm )
{
	Logs::debug ( "State GSMainMenu::draw\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw2d (draw 2d elements in front)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMainMenu::draw2d	( const StateMachine *sm )
{
	Logs::debug ( "State GSMainMenu::draw2d\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State sleep (application is interrupted)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMainMenu::sleep	( const StateMachine *sm )
{
	Logs::info ( "State GSMainMenu::sleep\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State wakeup (application is resumed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMainMenu::wakeup	( const StateMachine *sm )
{
	Logs::info ( "State GSMainMenu::wakeup\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Update and Draw(draw2d) regardless of pause)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSMainMenu::isWorkingInParallel()
{
return true;
}
*/

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Loding screen Disable. )
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSMainMenu::isLoadingDisable()
{
return true;
}
*/


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EReceiver
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	GSMainMenu::onEvent ( const EEvent *ev, const EventManager *evMgr )
{
	Logs::debug ( "State GSMainMenu onEvent\n" );

	switch ( ev->getEventID() )
	{
		case Events::IRRLICHT_EVENT:
			Logs::debug ( "IRRLICHT_EVENT onEvent\n" );
			break;

		case Events::GAME_SWF_EVENT:
			Logs::info ( "GAME_SWF_EVENT onEvent\n" );
			const char *CommandSWF=static_cast<const EvGameSWFEvent *> ( ev )->command;
			const char *ArgsSWF=static_cast<const EvGameSWFEvent *> ( ev )->args;

			if ( strcmp ( "button2", CommandSWF ) ==0 )
			{
				if ( strcmp ( "release", ArgsSWF ) ==0 )
				{
					m_nextState=SELECT_LOADGAME;
					m_exitState=true;
				}
			}

			else if ( strcmp ( "button4", CommandSWF ) ==0 )
			{
				if ( strcmp ( "release", ArgsSWF ) ==0 )
				{
					m_nextState=SELECT_ABOUTGAME;
					m_exitState=true;
				}
			}

			else if ( strcmp ( "button1", CommandSWF ) ==0 )
			{
				if ( strcmp ( "release", ArgsSWF ) ==0 )
				{
					m_nextState=SELECT_NEWGAME;
					m_exitState=true;
				}
			}

			else if ( strcmp ( "buttonback", CommandSWF ) ==0 )
			{
				if ( strcmp ( "release", ArgsSWF ) ==0 )
				{
					m_nextState=SELECT_BACK;
					m_exitState=true;
				}
			}

			else if ( strcmp ( "button3", CommandSWF ) ==0 )
			{
				if ( strcmp ( "release", ArgsSWF ) ==0 )
				{
					m_nextState=SELECT_BACK;
					m_exitState=true;
				}
			}

			break;
	}
}





