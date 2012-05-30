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
#include "GSTested_State.h"
#include "Game/tool/CUnrealMeshFileLoader.h"
//#include "Game/tool/OpenOfficeContextLoader.h"
//#include "IReadFile.h"
//class SSkinnedMesh;
/*
class Shader1 : public video::IShaderConstantSetCallBack
{
	public:
		IrrlichtDevice			*IrrlichtDevice;	// Irrlicht Device
		ISceneManager			*SceneManager;	// Scene Manager
		IVideoDriver			*VideoDriver;		// Video Driver

		virtual void OnSetConstants ( video::IMaterialRendererServices *services, s32 userData )
		{
			video::IVideoDriver *driver = services->getVideoDriver();
			core::matrix4 invWorld = driver->getTransform ( video::ETS_WORLD );
			invWorld.makeInverse();
			services->setVertexShaderConstant ( "mInvWorld", invWorld.pointer(), 16 );
			core::matrix4 worldViewProj;
			worldViewProj = driver->getTransform ( video::ETS_PROJECTION );
			worldViewProj *= driver->getTransform ( video::ETS_VIEW );
			worldViewProj *= driver->getTransform ( video::ETS_WORLD );
			services->setVertexShaderConstant ( "mWorldViewProj", worldViewProj.pointer(), 16 );
			core::vector3df pos = SceneManager->getActiveCamera()->getAbsolutePosition();
			services->setVertexShaderConstant ( "mLightPos", reinterpret_cast< f32 * > ( &pos ), 3 );
			video::SColorf col ( 0.0f,1.0f,1.0f,0.0f );
			services->setVertexShaderConstant ( "mLightColor", reinterpret_cast< f32 * > ( &col ), 4 );
			core::matrix4 world = driver->getTransform ( video::ETS_WORLD );
			world = world.getTransposed();
			services->setVertexShaderConstant ( "mTransWorld", world.pointer(), 16 );
		}
};
*/
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StateName
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *GSTested_State::getStateName() const
{
	return "GSTested_State";
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSTested_State::GSTested_State()
{
	Logs::info ( "GSTested_State\n" );
	m_isGame = Game::getInstance();
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );
	m_UIObject=0;
	cameraFPS=0;
	m_gamepad.isPresend=false;
	m_gamepad.isRoll=false;
	m_gamepad.x_mouse=0;
	m_gamepad.y_mouse=0;
	isCameraFRS=false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSTested_State::~GSTested_State()
{
	Logs::info ( "~GSTested_State\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State CTOR (when added to the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTested_State::ctor	( const StateMachine *sm )
{
	Logs::info ( "State GSTested_State::ctor\n" );
	m_isEventManager->attach ( Events::IRRLICHT_EVENT, this );
	m_isEventManager->attach ( Events::GAME_SWF_EVENT, this );
	video::IGPUProgrammingServices *gpu = m_isGame->getVideoDriver()->getGPUProgrammingServices();
	/*
		Shader1 *mcShader1 = new Shader1();
		mcShader1->VideoDriver=m_isGame->getVideoDriver();
		mcShader1->SceneManager=m_isGame->getSceneManager();
		mcShader1->IrrlichtDevice=m_isGame->getIrrlichtDevice();


		s32 shadersMaterial1 = gpu->addHighLevelShaderMaterialFromFiles (
		                           "data/shaders/Test_V.glsl","vertexMain",
		                           EVST_VS_1_1,
		                           "data/shaders/Test_P.glsl","pixelMain",
		                           EPST_PS_1_1,
		                           mcShader1,
		                           //video::EMT_TRANSPARENT_ADD_COLOR);
		                           video::EMT_SOLID );
	*/
	m_UIObject=m_isGame->getUIManager()->CreateUIObject ( "data/swf/GSTested_State.swf" );
	cameraFPS =m_isGame->getSceneManager()->addCameraSceneNodeFPS();
	camera =m_isGame->getSceneManager()->addCameraSceneNode();
	camera->setPosition ( core::vector3df ( 0,400,0 ) );
	camera->setTarget ( core::vector3df ( 0,400,-1 ) );
	camera->setFarValue ( 42000.0f );
	cameraFPS->setFarValue ( 42000.0f );
	/*
		m_isGame->getIrrlichtDevice()->getFileSystem()->addZipFileArchive ( "data/maps/level1.pxd" );
		scene::IAnimatedMesh *mesh = m_isGame->getSceneManager()->getMesh ( "level1.3ds" );
		mesh->setMaterialFlag ( EMF_LIGHTING, false );
		//m_isGame->getSceneManager()->getRootSceneNode()->setMaterialType( ( video::E_MATERIAL_TYPE ) shadersMaterial1 );
		scene::ISceneNode *node = 0;

		if ( mesh )
		{
			node = m_isGame->getSceneManager()->addOctreeSceneNode ( mesh->getMesh ( 0 ), 0, -1, 1024 );
		}

		if ( node )
		{
			node->setPosition ( core::vector3df ( 0,0,0 ) );
		}
	*/
	////////////////////////////////////////
	ISceneNode *Node = m_isGame->getSceneManager()->addCubeSceneNode ( 1.0 );
	Node->setScale ( vector3df ( 8400,3,8400 ) ); // 400, 3, 400
	Node->setPosition ( vector3df ( 0,150,-400 ) );
	//Unrealnode->setPosition ( core::vector3df ( 0,300,-400 ) );
	Node->setMaterialFlag ( video::EMF_LIGHTING, false );
	Node->setMaterialTexture ( 0, m_isGame->getVideoDriver()->getTexture ( "data/crazysky/blue.jpg" ) );
	ICollisionShape *shape = new IBoxShape ( Node, 0, false );
	IRigidBody *body;
	body = m_isGame->IrrBulletPhysicsWorld()->addRigidBody ( shape );
	irr::u32 rows=100;
	irr::u32 columns=10;
	ITexture *text1=m_isGame->getVideoDriver()->getTexture ( "data/crazysky/granitestone.jpg" );
	ITexture *text2=m_isGame->getVideoDriver()->getTexture ( "data/crazysky/crazy1.jpg" );
	ITexture *text3=m_isGame->getVideoDriver()->getTexture ( "data/crazysky/blue.jpg" );

	for ( u32 j=0; j < columns; j++ )
	{
		for ( u32 i=0; i < rows; i++ )
		{
			irr::scene::ISceneNode *Node = m_isGame->getSceneManager()->addCubeSceneNode ( 1.0f );
			Node->setScale ( vector3df ( 20,20,20 ) );
			Node->setPosition ( vector3df ( 30*j, 150+30*i+3, -300+rand() %200 ) );
			Node->setMaterialFlag ( irr::video::EMF_LIGHTING, false );

			switch ( rand() %3 )
			{
				case 0:
					Node->setMaterialTexture ( 0, text1 );
					break;

				case 1:
					Node->setMaterialTexture ( 0, text2 );
					break;

				case 2:
					Node->setMaterialTexture ( 0, text3 );
					break;
			}

			ICollisionShape *shape = new IBoxShape ( Node, 300 );
			IRigidBody *body;
			body = m_isGame->IrrBulletPhysicsWorld()->addRigidBody ( shape );
		}
	}

	//m_isGame->IrrBulletPhysicsWorld()->setGravity ( vector3df ( 0,-GRAVITY*3,0 ) );
	//////////////////////////////////////////////
	renderSkyTexture=m_isGame->getVideoDriver()->addRenderTargetTexture ( core::dimension2d< u32 > ( 512,512 ), "RTT1" );
	scene::ISceneNode *skySceneNode=m_isGame->getSceneManager()->addSkyBoxSceneNode (
	                                    m_isGame->getVideoDriver()->getTexture ( "data/loading.png" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/loading.png" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/loading.png" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/loading.png" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/loading.png" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/loading.png" ),
	                                    cameraFPS );

	for ( int i=0; i<6; i++ )
	{
		skyMaterial[i]=&skySceneNode->getMaterial ( i );
	}

	scene::IAnimatedMeshSceneNode *crazyskymesh = m_isGame->getSceneManager()->addAnimatedMeshSceneNode ( m_isGame->getSceneManager()->getMesh ( "data/crazysky/sky3.x" ) );
	crazyskymesh->setMaterialFlag ( EMF_LIGHTING, false );
	crazyskymesh->getMaterial ( 0 ).Shininess = 20.0f;
	crazyskymesh->getMaterial ( 0 ).SpecularColor.set ( 255,255,255,255 );
	crazyskymesh->getMaterial ( 0 ).AmbientColor.set ( 255,255,255,255 );
	crazyskymesh->getMaterial ( 0 ).DiffuseColor.set ( 255,255,255,255 );
	crazyskymesh->getMaterial ( 0 ).EmissiveColor.set ( 0,0,0,0 );
	ILightSceneNode *SkyLight = m_isGame->getSceneManager()->addLightSceneNode ( 0, core::vector3df ( 0,-50000,0 ), video::SColorf ( 1.0f,1.0f,1.0f ), 10.0f, 1 );
	crazyskymesh->setPosition ( core::vector3df ( 0,-50000,0 ) );
	crazyskymesh->setAnimationSpeed ( 0.7f );
	//IAnimatedMesh* crazyskymesh = m_isGame->getSceneManager()->getMesh("data/crazysky/sky.x");
	SkyCameraBone=0;
	cameraSky=m_isGame->getSceneManager()->addCameraSceneNode();
	SkyCameraBone=crazyskymesh->getJointNode ( "CameraBone" );

	if ( SkyCameraBone )
	{
		//SkyCameraBone->addChild(SkyLight);
		Logs::info ( " JointNode Bip01_Spine \n" );
	}

	/////////////////////////
	//m_isGame->getSceneManager()->addExternalMeshLoader(new scene::CFBXMeshFileLoader(m_isGame->getSceneManager()));
	/*	scene::IAnimatedMesh *FBXmesh = m_isGame->getSceneManager()->getMesh ( "data/models/fbx/datgirl.FBX" );

		if ( !FBXmesh )
		{
			std::cout << "Unable to load mesh: " << std::endl;
			return;
		}

		else
		{
			scene::ISceneNode *FBXnode = m_isGame->getSceneManager()->addAnimatedMeshSceneNode ( FBXmesh );

			if ( !FBXnode )
			{
				std::cout << "Unable to create node with mesh: " << std::endl;
				return;
			}

			FBXnode->setMaterialFlag ( EMF_LIGHTING, false );
			FBXnode->setDebugDataVisible ( scene::EDS_FULL&~scene::EDS_NORMALS );
			FBXnode->setDebugDataVisible ( scene::EDS_HALF_TRANSPARENCY );
			FBXnode->setDebugDataVisible ( scene::EDS_SKELETON );
			FBXnode->setMaterialFlag ( video::EMF_LIGHTING, false );
			//FBXnode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
		}
	*/
	////////////////////
	IAnimatedMesh *Unrealmesh = m_isGame->getSceneManager()->getMesh ( "data/models/UnrealMesh/char_betty.PSK" );
	IAnimatedMeshSceneNode *Unrealnode = m_isGame->getSceneManager()->addAnimatedMeshSceneNode ( Unrealmesh );

	if ( Unrealnode )
	{
		Unrealnode->setRotation ( vector3df ( -90,180,0 ) );
		Unrealnode->getMaterial ( 0 ).setTexture ( 0, m_isGame->getVideoDriver()->getTexture ( "data/models/UnrealMesh/char_betty_tex.tga" ) );
		Unrealnode->getMaterial ( 1 ).setTexture ( 0, m_isGame->getVideoDriver()->getTexture ( "data/models/UnrealMesh/char_betty_tex.tga" ) );
		Unrealnode->getMaterial ( 2 ).setTexture ( 0, m_isGame->getVideoDriver()->getTexture ( "data/models/UnrealMesh/char_betty_tex.tga" ) );
		Unrealnode->setMaterialFlag ( EMF_LIGHTING, false );
		IAnimatedMesh *Unrealanimation = m_isGame->getSceneManager()->getMesh ( "data/models/UnrealMesh/char_betty_anim.PSA" );
		s32 begin=0, end=550;
		f32 speed=24;
		/*
		test
		idle
		jump
		run
		walk
		*/
		core::stringc SelectAnimation="jump";
		( ( SSkinnedMesh * ) Unrealanimation )->getFrameLoop ( SelectAnimation , begin, end, speed );
		//((SSkinnedMesh*)Unrealanimation)->getFrameLoop( core::stringc("idle") , begin, end, speed );
		//((SSkinnedMesh*)Unrealanimation)->getFrameLoop( core::stringc("jump") , begin, end, speed );
		//((SSkinnedMesh*)Unrealanimation)->getFrameLoop( core::stringc("run") , begin, end, speed );
		( ( ISkinnedMesh * ) Unrealmesh )->useAnimationFrom ( ( ( ISkinnedMesh * ) Unrealanimation ) );
		Unrealnode->setFrameLoop ( begin, end );
		Unrealnode->setAnimationSpeed ( speed );
		Unrealnode->setLoopMode ( true );
		Unrealnode->setPosition ( core::vector3df ( 0,300,-400 ) );
		Unrealnode->setRotation ( core::vector3df ( -90,0,0 ) );
	}

	////////////////////
	m_isGame->getSceneManager()->setActiveCamera ( camera );
	////////////////////////////////
	/*
	m_isGame->getIrrlichtDevice()->getFileSystem()->addZipFileArchive ( "data/text/localization.ods" );
	io::IReadFile* file = m_isGame->getIrrlichtDevice()->getFileSystem()->createAndOpenFile("content.xml");
	if (!file)
	{
	printf("Could not load content.xml");
	}
	else
	{
		wchar_t *filebuffer = (wchar_t*) malloc (sizeof(wchar_t)*file->getSize());
		memset(filebuffer,' ',(sizeof(wchar_t)*file->getSize()));
		file->seek(0);
		file->read(filebuffer, 1+file->getSize());

		FILE * pFile;
		pFile = fopen ( "myfile.bin" , "wb" );
		fwrite (filebuffer , 1 , 1+file->getSize() , pFile );

	}
	*/
	/*
	OpenOfficeContextLoader *odsfile = new OpenOfficeContextLoader ( m_isGame->getIrrlichtDevice(),"data/text/localization.ods","content.xml" );
	odsfile->writeOpenOfficeDocumentTextToFile ( "data/text/test.xml" );
	wchar_t *filebuffer = odsfile->getOpenOfficeDocumentText();
	FILE *pFile;
	pFile = fopen ( "data/text/myfile.bin" , "wb" );
	fwrite ( filebuffer , 1 , 1+odsfile->getFileSizeOpenOfficeDocumentText() , pFile );
	fclose ( pFile );
	*/
	////////////////////////////////
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State DTOR (when removed from the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTested_State::dtor	( const StateMachine *sm )
{
	Logs::info ( "State GSTested_State::dtor\n" );
	m_isEventManager->detach ( Events::IRRLICHT_EVENT, this );
	m_isEventManager->detach ( Events::GAME_SWF_EVENT, this );

	if ( m_UIObject )
	{
		m_isGame->getUIManager()->ReleaseUIObject ( m_UIObject );
		m_UIObject=0;
	}
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State update (game update: update)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTested_State::update ( StateMachine *sm )
{
	Logs::debug ( "State GSTested_State::update\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State pause (when a new state is added atop)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTested_State::pause	( const StateMachine *sm )
{
	Logs::info ( "State GSTested_State::pause\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State resume (when the state above is removed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTested_State::resume	( const StateMachine *sm )
{
	Logs::info ( "State GSTested_State::resume\n" );
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw (game update: draw)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTested_State::draw	( const StateMachine *sm )
{
	Logs::debug ( "State GSTested_State::draw\n" );

	if ( m_gamepad.isPresend && m_gamepad.isRoll && m_UIObject )
	{
		char tempmousexy[4];
		sprintf ( tempmousexy,"%d",m_gamepad.x_mouse );
		// m_UIObject->SetValue ( "_root.gamepad_center._x",tempmousexy );
		//printf("m_gamepad.x_mouse - %d\n",m_gamepad.x_mouse);
		sprintf ( tempmousexy,"%d",m_gamepad.y_mouse );
		// m_UIObject->SetValue ( "_root.gamepad_center._y",tempmousexy );
		//printf("m_gamepad.y_mouse - %d\n",m_gamepad.y_mouse);
		//moveTo
		//m_UIObject->s
		//m_UIObject->SetBoolean("_root.gamepad_center._x",44);
		//m_UIObject->SetBoolean("_root.gamepad_center._y",44);
	}

	if ( renderSkyTexture )
	{
		m_isGame->getVideoDriver()->setRenderTarget ( renderSkyTexture, true, true, video::SColor ( 0,0,0,255 ) );
		m_isGame->getSceneManager()->setActiveCamera ( cameraSky );

		if ( isCameraFRS )
		{
			cameraSky->setTarget ( core::vector3df
			                       (
			                           cameraSky->getPosition().X+ ( cameraFPS->getPosition().X-cameraFPS->getTarget().X ),
			                           cameraSky->getPosition().Y- ( cameraFPS->getPosition().Y-cameraFPS->getTarget().Y ),
			                           cameraSky->getPosition().Z+ ( cameraFPS->getPosition().Z-cameraFPS->getTarget().Z )
			                       ) );
		}

		else
		{
			cameraSky->setTarget ( core::vector3df
			                       (
			                           cameraSky->getPosition().X+ ( camera->getPosition().X-camera->getTarget().X ),
			                           cameraSky->getPosition().Y- ( camera->getPosition().Y-camera->getTarget().Y ),
			                           cameraSky->getPosition().Z+ ( camera->getPosition().Z-camera->getTarget().Z )
			                       ) );
		}

		cameraSky->setPosition ( SkyCameraBone->getAbsolutePosition() );
		//						cameraSky->setTarget(camera->getRotation());
		//						printf("%f %f %f \n"camera->getRotation().X,camera->getRotation().Y,camera->getRotation().Z);
		m_isGame->getSceneManager()->drawAll();
		m_isGame->getVideoDriver()->setRenderTarget ( 0, true, true, 0 );

		if ( isCameraFRS )
		{
			m_isGame->getSceneManager()->setActiveCamera ( cameraFPS );
			//cameraSky->setParent(cameraFPS);
		}

		else
		{
			m_isGame->getSceneManager()->setActiveCamera ( camera );
			//cameraSky->setParent(camera);
		}

		for ( int i=0; i<6; i++ )
		{
			skyMaterial[i]->setTexture ( 0,renderSkyTexture );
		}
	}
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw2d (draw 2d elements in front)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTested_State::draw2d	( const StateMachine *sm )
{
	Logs::debug ( "State GSTested_State::draw2d\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State sleep (application is interrupted)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTested_State::sleep	( const StateMachine *sm )
{
	Logs::info ( "State GSTested_State::sleep\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State wakeup (application is resumed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTested_State::wakeup	( const StateMachine *sm )
{
	Logs::info ( "State GSTested_State::wakeup\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Update and Draw(draw2d) regardless of pause)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSTested_State::isWorkingInParallel()
{
return true;
}
*/

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Loding screen Disable. )
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSTested_State::isLoadingDisable()
{
return true;
}
*/


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EReceiver
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	GSTested_State::onEvent ( const EEvent *ev, const EventManager *evMgr )
{
	Logs::debug ( "State GSTested_State onEvent\n" );

	switch ( ev->getEventID() )
	{
		case Events::IRRLICHT_EVENT:
			{
				Logs::debug ( "IRRLICHT_EVENT onEvent\n" );
				irr::SEvent IrrlichtEvent = static_cast<const EvIrrlichtEvents *> ( ev )->irr_event;

				if ( IrrlichtEvent.EventType == irr::EET_MOUSE_INPUT_EVENT && IrrlichtEvent.MouseInput.Event == irr::EMIE_MOUSE_MOVED )
				{
					m_gamepad.x_mouse = IrrlichtEvent.MouseInput.X;
					m_gamepad.y_mouse = IrrlichtEvent.MouseInput.Y;
				}
			}
			break;

		case Events::GAME_SWF_EVENT:
			Logs::info ( "GAME_SWF_EVENT onEvent\n" );
			const char *CommandSWF=static_cast<const EvGameSWFEvent *> ( ev )->command;
			const char *ArgsSWF=static_cast<const EvGameSWFEvent *> ( ev )->args;

			/*
			gamepad
			gamepad_center
			gamemenu
			button_action1
			button_action2
			//////
			rollOver
			rollOut
			press
			release
			dragOut
			dragOver
			*/
			if ( strcmp ( "gamepad", CommandSWF ) ==0 )
			{
				if ( strcmp ( "rollOver", ArgsSWF ) ==0 )
				{
					m_gamepad.isRoll=true;
				}

				else if ( strcmp ( "rollOut", ArgsSWF ) ==0 )
				{
					m_gamepad.isRoll=false;
				}

				else if ( strcmp ( "dragOut", ArgsSWF ) ==0 )
				{
					m_gamepad.isRoll=false;
				}

				else if ( strcmp ( "dragOver", ArgsSWF ) ==0 )
				{
					m_gamepad.isRoll=true;
				}

				else if ( strcmp ( "press", ArgsSWF ) ==0 )
				{
					m_gamepad.isPresend=true;
				}

				else if ( strcmp ( "release", ArgsSWF ) ==0 )
				{
					m_gamepad.isPresend=false;
				}
			}

			else if ( strcmp ( "button_action1", CommandSWF ) ==0 )
			{
				if ( strcmp ( "release", ArgsSWF ) ==0 )
				{
					isCameraFRS=!isCameraFRS;
				}
			}

			break;
	}
}



