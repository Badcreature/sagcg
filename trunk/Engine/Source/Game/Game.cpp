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
// Game
//
//		This object with the initialization of the various engines
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Game.h"
#ifdef _IRR_COMPILE_WITH_FBX_LOADER_
#include "Game/tool/CFBXMeshFileLoader.h"
#endif //_IRR_COMPILE_WITH_FBX_LOADER_
#ifdef _IRR_COMPILE_WITH_UNREAL_LOADER_
#include "Game/tool/CUnrealMeshFileLoader.h"
#endif //_IRR_COMPILE_WITH_UNREAL_LOADER_

#ifdef WIN32
#	include <GL/gl.h>
#endif // WIN32

#ifndef WIN32
extern "C++" IrrlichtDevice *getGlobalIrrlichtDevice();
extern "C++" int getDeviceWidth();
extern "C++" int getDeviceHeight();
#else
int	g_DeviceWidth	=	1024;
int	g_DeviceHeight	=	768;
/*int	g_DeviceWidth	=	960;
int	g_DeviceHeight	=	640;*/
int getDeviceWidth()
{
	return g_DeviceWidth;
}
int getDeviceHeight()
{
	return g_DeviceHeight;
}
IrrlichtDevice *getGlobalIrrlichtDevice()
{
	return 0;
}
#endif

Game *Game ::m_Game=NULL;
Game::Game()
{
	m_language=0;
	m_isGameRun=false;
	m_DrawNumToUpdate=DRAW_TO_UPDATE;
	m_IrrlichtDevice=NULL;
	m_SceneManager=NULL;
	m_VideoDriver=NULL;
	m_GUIEnvironment=NULL;
	m_lastFPS = -1;
	m_font = 0;
	m_UIManager=NULL;
	m_MouseButtonDown=0;
	m_MouseX=0;
	m_MouseY=0;
	m_MouseCount=0;
#ifdef BOX2D
	m_my2DPhysicsWorld=NULL;
#endif
#ifdef IRRBULLET
	m_IrrBulletPhysicsWorld=NULL;
#endif

	if ( Init() )
	{
		Logs::error ( "Error init \"Game::Game()\" \n" );
	}
}

////////////////////////////////////////
IrrlichtDevice *Game::getIrrlichtDevice()
{
	return m_IrrlichtDevice;
}
IVideoDriver *Game::getVideoDriver()
{
	return m_VideoDriver;
}
ISceneManager *Game::getSceneManager()
{
	return m_SceneManager;
}
IGUIEnvironment	*Game::getGUIEnvironment()
{
	return m_GUIEnvironment;
}


cUIManager	*Game::getUIManager()
{
	return m_UIManager;
}

#ifdef BOX2D
b2World	*Game::get2DPhysicsWorld()
{
	return m_my2DPhysicsWorld;
}
#endif

#ifdef IRRBULLET
irrBulletWorld *Game::IrrBulletPhysicsWorld()
{
	return m_IrrBulletPhysicsWorld;
}
#endif

////////////////////////////////////////

bool Game::Init()
{
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );
	////////////////////////////////////////
	// Irrlicht engines
	////////////////////////////////////////

	if ( getGlobalIrrlichtDevice() )
	{
		m_IrrlichtDevice=getGlobalIrrlichtDevice();
		m_IrrlichtDevice->getVideoDriver()->setViewPort ( core::rect<s32> ( 0,0,getDeviceWidth(),getDeviceHeight() ) );
		m_IrrlichtDevice->setEventReceiver ( this );
	}

	else
	{
		m_IrrlichtDevice=createDevice ( video::EDT_OPENGL, dimension2d< u32 > ( getDeviceWidth(), getDeviceHeight() ), 16,false, false, false, this );
	}

	if ( !m_IrrlichtDevice )
	{
		return 1;
	}

	// Init mouse
	m_MouseButtonDown=new bool[irr::NUMBER_OF_MULTI_TOUCHES];
	m_MouseX=new int[irr::NUMBER_OF_MULTI_TOUCHES];
	m_MouseY=new int[irr::NUMBER_OF_MULTI_TOUCHES];
#ifdef WIN32
	m_MouseCount=1;
#else
	m_MouseCount=irr::NUMBER_OF_MULTI_TOUCHES;
#endif
	// ///
	m_IrrlichtDevice->setWindowCaption ( L"Game Engine Window" );
	m_VideoDriver = m_IrrlichtDevice->getVideoDriver();
	m_SceneManager = m_IrrlichtDevice->getSceneManager();
	m_GUIEnvironment = m_IrrlichtDevice->getGUIEnvironment();
#ifdef _IRR_COMPILE_WITH_FBX_LOADER_
	CFBXMeshFileLoader *fbx_loader = new scene::CFBXMeshFileLoader ( m_SceneManager );
	m_SceneManager->addExternalMeshLoader ( fbx_loader );
	fbx_loader->drop();
#endif
#ifdef _IRR_COMPILE_WITH_UNREAL_LOADER_
	CPSKMeshFileLoader *psk_loader = new CPSKMeshFileLoader ( m_SceneManager, m_IrrlichtDevice->getLogger() );
	CPSAMeshFileLoader *psa_loader = new CPSAMeshFileLoader ( m_SceneManager, m_IrrlichtDevice->getLogger() );
	m_SceneManager->addExternalMeshLoader ( psk_loader );
	m_SceneManager->addExternalMeshLoader ( psa_loader );
	psk_loader->drop( );
	psa_loader->drop( );
#endif
	m_UIManager = new cUIManager;

	if ( m_IrrlichtDevice->getFileSystem()->addFolderFileArchive ( "data/" ) )
	{
		//	Logs::error ( "addFolderFileArchive\n" );
	}

	m_font = m_GUIEnvironment->getBuiltInFont();
	////////////////////////////////////////
	// Box2d engine
	////////////////////////////////////////
#ifdef BOX2D
	b2Vec2 gravity ( 0.0f, -GRAVITY );
	bool doSleep = PHYSICS_2D_DO_SLEEP;
	m_my2DPhysicsWorld = new b2World ( gravity, doSleep );
#endif
#ifdef IRRBULLET
	////////////////////////////
	// Create irrBullet World //
	////////////////////////////
	m_IrrBulletPhysicsWorld = createIrrBulletWorld ( m_IrrlichtDevice, false, IRRBULLET_SHOW_DEBUG );

	if ( IRRBULLET_SHOW_DEBUG )
	{
		m_IrrBulletPhysicsWorld->setDebugMode ( EPDM_DrawAabb |EPDM_DrawContactPoints );
	}

	m_IrrBulletPhysicsWorld->setGravity ( vector3df ( 0,-GRAVITY,0 ) );
#endif
	////////////////////////////////////////
	m_isGameRun=true;
	return 0;
}

bool Game::Run()
{
	if ( m_IrrlichtDevice->run() )
	{
#ifdef WIN32
		UIManagerUpdate ( false );
#endif

		for ( m_DrawNumToUpdate=DRAW_TO_UPDATE;	m_DrawNumToUpdate!=0;	m_DrawNumToUpdate-- )
		{
			m_VideoDriver->beginScene ( true, true, SColor ( 255,0,0,0 ) );
			//
			m_isStateMachine->draw();
			m_SceneManager->drawAll();
			//
			m_isStateMachine->draw2d();
#ifdef PRINT_FPS_CONSOLE
			int fps = m_IrrlichtDevice->getVideoDriver()->getFPS();

			if ( m_lastFPS != fps )
			{
				printf ( "\t- FPS: %d -\n",fps );
			}

			m_lastFPS = fps;
#endif
			m_GUIEnvironment->drawAll();
			//
			m_UIManager->Render ( getDeviceWidth(), getDeviceHeight(), false );
			m_VideoDriver->endScene();
		}

		return 0;
	}

	else
	{
		return 1;
	}
}

void Game::UIManagerUpdate ( float deltatime )
{
#ifdef WIN32
	m_UIManager->UpdateMouseState ( m_MouseX, m_MouseY,m_MouseCount, m_MouseButtonDown );
#endif // WIN32
	m_UIManager->Update ( deltatime ,false );
}


void Game::Quit()
{
	m_IrrlichtDevice->drop();
#ifdef BOX2D

	if ( m_my2DPhysicsWorld )
	{
		delete m_my2DPhysicsWorld;
	}

#endif
}

void	Game::setLanguage ( int language )
{
	if ( LANGUAGE_UNKNOWN<language && LANGUAGE_COUNTER>language )
	{
		m_language=language;
	}

	else
	{
		m_language=LANGUAGE_EN;
	}
}
int		Game::getLanguage()
{
	return m_language;
}

void Game::GameSWFEvent ( const char *command, const char *args )
{
	printf ( "DispatchCommand %s   args %s\n",command,args );
	EventManager::getInstance().raise ( EvGameSWFEvent ( command, args ) );
}

bool Game::OnEvent ( const irr::SEvent &IrrlichtEvent )
{
	EventManager::getInstance().raise ( EvIrrlichtEvents ( IrrlichtEvent ) );
#ifdef WIN32

	if ( IrrlichtEvent.EventType == irr::EET_MOUSE_INPUT_EVENT )
	{
		switch ( IrrlichtEvent.MouseInput.Event )
		{
			case EMIE_LMOUSE_PRESSED_DOWN:
				m_MouseButtonDown[0] = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				m_MouseButtonDown[0] = false;
				break;

			case EMIE_RMOUSE_PRESSED_DOWN:
				m_MouseButtonDown[0] = true;
				break;

			case EMIE_RMOUSE_LEFT_UP:
				m_MouseButtonDown[0] = false;
				break;

			case EMIE_MOUSE_MOVED:
				m_MouseX[0] = IrrlichtEvent.MouseInput.X;
				m_MouseY[0] = IrrlichtEvent.MouseInput.Y;
				m_UIManager->UpdateMouseState ( m_MouseX, m_MouseY, m_MouseCount, m_MouseButtonDown );
				break;

			default:
				// We won't use the wheel
				break;
		}
	}

#else

	if ( IrrlichtEvent.EventType == irr::EET_MULTI_TOUCH_EVENT )
	{
		u32 cnt = IrrlichtEvent.MultiTouchInput.touchedCount();

		for ( int i=0; i<cnt; i++ )
		{
			if ( IrrlichtEvent.MultiTouchInput.Event==EMTIE_PRESSED_DOWN || IrrlichtEvent.MultiTouchInput.Event==EMTIE_MOVED )
			{
				m_MouseX[i]=IrrlichtEvent.MultiTouchInput.X[i];
				m_MouseY[i]=IrrlichtEvent.MultiTouchInput.Y[i];
				m_MouseCount=cnt;
				m_MouseButtonDown[i]=true;
			}

			else
			{
				m_MouseX[i]=IrrlichtEvent.MultiTouchInput.X[i];
				m_MouseY[i]=IrrlichtEvent.MultiTouchInput.Y[i];
				m_MouseCount=cnt;
				m_MouseButtonDown[i]=false;
			}

			m_UIManager->UpdateMouseState ( m_MouseX, m_MouseY, m_MouseCount, m_MouseButtonDown );
		}
	}

#endif // WIN32
	return false;
};