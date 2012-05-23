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
#include "Loading.h"
#include "Game/Game.h"
Loading *Loading ::m_Loading=NULL;
Loading::Loading()
{
	m_visibleLoading=false;
	m_loadingIGUIImage=false;
	isLoadingInit=false;
}


void Loading::Init()
{
	m_isGame = Game::getInstance();

	if ( !m_isGame )
	{
		return;
	}

	video::ITexture *image=m_isGame->getVideoDriver()->getTexture ( "data/loading.png" );
	m_loadingIGUIImage = m_isGame->getGUIEnvironment()->addImage ( image,
	                     core::position2d<s32> ( 10, 10 ) );
	// lock the logo's edges to the bottom left corner of the screen
	m_loadingIGUIImage->setAlignment ( EGUIA_UPPERLEFT, EGUIA_UPPERLEFT,
	                                   EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT );
	isLoadingInit=true;
}
void Loading::Run()
{
	if ( !isLoadingInit )
	{
		return;
	}

	m_isGame = Game::getInstance();

	if ( !m_isGame )
	{
		return;
	}

	/*	m_isGame->getIrrlichtDevice()->getCursorControl()->setVisible ( !m_visibleLoading );*/
	m_isGame->getVideoDriver()->beginScene ( true, true, SColor ( 255,0,0,0 ) );

	if ( m_loadingIGUIImage )
	{
		m_loadingIGUIImage->setVisible ( m_visibleLoading );
	}

	m_isGame->getGUIEnvironment()->drawAll();
	m_isGame->getSceneManager()->drawAll();
	m_isGame->getVideoDriver()->endScene();
}

void Loading::LoadingOn()
{
	if ( m_visibleLoading )
	{
		return;
	}

	m_visibleLoading=true;

	if ( !isLoadingInit )
	{
		Init();
	}

	Run();
}

void Loading::LoadingOff()
{
	if ( !m_visibleLoading )
	{
		return;
	}

	m_visibleLoading=false;
	Run();
}

