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
// Application
//
//		The main (common) class handling the application/game
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Application.h"
#include "Game/GameState/GSBaseState.h"
#include "Game/Game.h"


Application *Application :: m_Application=NULL;
Application::Application()
{
	m_dt=0;
	m_minDeltaTime=1000/MAX_FPS;
	m_isStateMachine = & ( StateMachine::getInstance() );
	m_isEventManager = & ( EventManager::getInstance() );
	m_isGame = Game::getInstance();
}


void Application::Run()
{
	m_isStateMachine->pushState<GSBaseState>();
#ifdef WIN32

	while ( Update() )
	{
	}

	Quit();
#endif
}

bool Application::Update()
{
	if ( m_isGame->Run() !=1 )
	{
		//////////////////////////////////////
		//Update Deltatime and set Max FPS
		//////////////////////////////////////
		TimeManager::update_steptime();
		m_dt = TimeManager::get_steptime_ms();
#ifdef WIN32

		if ( m_dt<m_minDeltaTime )
		{
			TimeManager::sleep ( m_minDeltaTime-m_dt );
			m_dt=m_minDeltaTime;
		}

#endif
		//////////////////////////////////////
		//////////////////////////////////////
#ifdef IRRBULLET

		if ( m_isGame->IrrBulletPhysicsWorld() )
		{
			m_isGame->IrrBulletPhysicsWorld()->stepSimulation ( m_dt, 1, 1.0f/30.f );
		}

#endif
		m_isStateMachine->update ( m_dt );
		m_isEventManager->Update ( ( double ) m_dt );
		m_isGame->UIManagerUpdate ( ( float ) m_dt );
		return 1;
	}

	else
	{
		return 0;
	}
}


void Application::Quit()
{
	if ( m_isStateMachine )
	{
		while ( m_isStateMachine->stackSize() > 0 )
		{
			m_isStateMachine->popState();
		}
	}

	m_isGame->Quit();
	delete m_Application;
}