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

#pragma once
#ifndef _STDAFX_H__
#define _STDAFX_H__

#pragma warning(disable: 4018) //'<' : signed/unsigned mismatch
#pragma warning(disable: 4244) //'argument' : conversion from 'int' to 'float', possible loss of data
#pragma warning(disable: 4101) //'' : unreferenced local variable

// Fedaultd and Setting
#include "Commons.h"

#ifdef WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "Box2D.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gameswf.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") // Console output OFF
#endif

#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <math.h>

// ** GameSWF
#include	<gameswf/gameswf.h>
#include	<gameswf/gameswf_player.h>
#include	<gameswf/gameswf_root.h>
#include	<gameswf/gameswf_text.h>
#include	<gameswf/gameswf_dlist.h>
#include	<base/tu_file.h>

// ** Flash UI
class cUIManager;
class cUIObject;
class cUIText;

typedef gameswf::gc_ptr<gameswf::root>		tSwfRoot;
typedef gameswf::gc_ptr<gameswf::player>	tSwfPlayer;
typedef gameswf::render_handler			*tSwfRenderer;
typedef gameswf::character					*tSwfCharacter;
typedef tu_file							*tSwfFile;

typedef std::list< cUIObject * >			tUIObjectList;


// Other include
#include "Logs.h"
#include "TimeManager.h"
#include "Application.h"
#include "StateMachine.h"
#include "StateBase.h"
#include "EEventReceiver.h"
#include "EEvent.h"
#include "EventManager.h"
#include "StringManager.h"
#include "Managers/UIManager/UIManager.h"
#include "Managers/GameObjectsManager/GameObjectsManager.h"
#include "Managers/GameObjectsManager/BaseGameObjects.h"

//
#include "Game/Loading.h"
#include "Game/GameEvents/EvIrrlichtEvents.h"
#include "Game/GameEvents/EvGameSWFEvent.h"
//
#include "irrlicht.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//
#ifdef BOX2D
#include "Box2D.h"
#endif
#ifdef IRRBULLET
#include <irrbullet.h>
#ifdef WIN32
#pragma comment(lib, "IrrBullet.lib")
#endif
#endif


#endif