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

#ifndef Game_H
#define Game_H

namespace irr
{
	struct SEvent;
}

class StateMachine;
class EventManager;

enum LANGUAGE
{
    LANGUAGE_UNKNOWN = -1,
    LANGUAGE_EN = 0,
    LANGUAGE_FR = 1,
    LANGUAGE_DE = 2,
    LANGUAGE_SP = 3,
    LANGUAGE_IT = 4,
    LANGUAGE_JP = 5,
    LANGUAGE_RU = 6,
    LANGUAGE_KO = 7,
    LANGUAGE_CN = 8,
    LANGUAGE_BR = 9,
    LANGUAGE_COUNTER = 10
};

class Game:public IEventReceiver
{
	protected:
		static Game		*m_Game;
		Game();
		bool m_isGameRun;
		int					m_DrawNumToUpdate;
		StateMachine 		*m_isStateMachine;
		EventManager 		*m_isEventManager;
		////////////////////////////////////////
		IrrlichtDevice			*m_IrrlichtDevice;	// Irrlicht Device
		ISceneManager			*m_SceneManager;	// Scene Manager
		IVideoDriver			*m_VideoDriver;		// Video Driver
		IGUIEnvironment			*m_GUIEnvironment;  // Menu
		int						 m_lastFPS;
		gui::IGUIFont			*m_font;
		int						 m_language;
		cUIManager				*m_UIManager;
#ifdef BOX2D
		b2World					*m_my2DPhysicsWorld;// Box2d PhysicsWorld
#endif

#ifdef IRRBULLET
		irrBulletWorld					*m_IrrBulletPhysicsWorld;
#endif

	public:
		static  Game *getInstance()
		{
			if ( !m_Game )
			{
				m_Game = new Game();
			}

			return m_Game;
		}
		bool OnEvent ( const irr::SEvent &IrrlichtEvent );
		void GameSWFEvent ( const char *command, const char *args );
		bool Run();
		bool Init();
		void Quit();
		void UIManagerUpdate ( float deltatime );
		IrrlichtDevice *getIrrlichtDevice();
		IVideoDriver *getVideoDriver();
		ISceneManager *getSceneManager();
		IGUIEnvironment	*getGUIEnvironment();
		cUIManager *getUIManager();
		bool m_MouseButton;
		int m_MouseInputX;
		int m_MouseInputY;
#ifdef BOX2D
		b2World	*get2DPhysicsWorld();
#endif
#ifdef IRRBULLET
		irrBulletWorld	*IrrBulletPhysicsWorld();
#endif
		void	setLanguage ( int language );
		int		getLanguage();
		bool	getGameIsRun()
		{
			return m_isGameRun;
		}

};

#endif // Game_H
