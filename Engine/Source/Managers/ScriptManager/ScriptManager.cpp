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
// ScriptManager
//
//
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ScriptManager.h"
#include "../../Game/Game.h"

#include "Game/GameEvents/EvGameCharacterEvent.h"


ScriptManager *ScriptManager :: m_ScriptManager=NULL;
ScriptManager::ScriptManager()
{
	//	m_isGame = Game::getInstance();
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );

	for ( int i=Events::EVENT_NULL+1; i<Events::EVENT_COUNT; i++ )
	{
		m_isEventManager->attach ( i, this );
	}
}
ScriptManager::~ScriptManager()
{
	for ( int i=Events::EVENT_NULL+1; i<Events::EVENT_COUNT; i++ )
	{
		m_isEventManager->detach ( i, this );
	}
}



void ScriptManager::Update ( unsigned long dt )
{
}


void	ScriptManager::onEvent ( const EEvent *ev, const EventManager *evMgr )
{
	EvGameCharacterEvent::CHARACTER_DATA_EVENT Characterdata;

	switch ( ev->getEventID() )
	{
		case Events::IRRLICHT_EVENT:
			{
				irr::SEvent IrrlichtEvent = static_cast<const EvIrrlichtEvents *> ( ev )->irr_event;

				if ( IrrlichtEvent.EventType == irr::EET_MOUSE_INPUT_EVENT && IrrlichtEvent.MouseInput.Event == irr::EMIE_MOUSE_MOVED )
				{
				}

				if ( IrrlichtEvent.EventType == irr::EET_KEY_INPUT_EVENT )
				{
					if ( IrrlichtEvent.KeyInput.Key==KEY_KEY_W )
					{
						Characterdata.MovementForward=IrrlichtEvent.KeyInput.PressedDown;
					}

					if ( IrrlichtEvent.KeyInput.Key==KEY_KEY_S )
					{
						Characterdata.MovementBack=IrrlichtEvent.KeyInput.PressedDown;
					}

					if ( IrrlichtEvent.KeyInput.Key==KEY_KEY_A )
					{
						Characterdata.MovementLeft=IrrlichtEvent.KeyInput.PressedDown;
					}

					if ( IrrlichtEvent.KeyInput.Key==KEY_KEY_D )
					{
						Characterdata.MovementRight=IrrlichtEvent.KeyInput.PressedDown;
					}

					if ( IrrlichtEvent.KeyInput.Key==KEY_SPACE )
					{
						Characterdata.Jump=IrrlichtEvent.KeyInput.PressedDown;
					}

					m_isEventManager->raise ( EvGameCharacterEvent ( Characterdata , "GOCharacter" ) );
				}
			}
			break;

		case Events::CHARACTER_EVENT:
			{
				//				EvGameCharacterEvent * CharacterEvent= static_cast< EvGameCharacterEvent *> (ev) ;
			}
			break;

		case Events::GAME_SWF_EVENT:
			{
				/*
				Logs::info ( "GAME_SWF_EVENT onEvent\n" );
				const char *CommandSWF=static_cast<const EvGameSWFEvent *> ( ev )->command;
				const char *ArgsSWF=static_cast<const EvGameSWFEvent *> ( ev )->args;

				if ( strcmp ( "button_action1", CommandSWF ) ==0 )
				{
					if ( strcmp ( "release", ArgsSWF ) ==0 )
					{
					}
				}*/
			}
			break;
	}
}
//