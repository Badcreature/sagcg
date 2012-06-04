#include "StdAfx.h"
#include "GOCharacter.h"
#include "Game/tool/CUnrealMeshFileLoader.h"
#include "Game/Game.h"
#include "Game/GameEvents/EvGameCharacterEvent.h"
class StateMachine;
class EventManager;

GOCharacter::GOCharacter()
{
	//ctor
	//
	//GameObjectName
	m_GameObjectName="GOCharacter";
	// clear link
	m_CharacterMesh=0;
	m_CharacterNode=0;
	m_CharacterAnimation=0;
	m_CharacterTexture0=0;
	m_CharacterTexture1=0;
	m_CharacterTexture2=0;
	//Globals
	m_isGame = Game::getInstance();
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );
	//
	m_CharacterMesh = m_isGame->getSceneManager()->getMesh ( "data/models/UnrealMesh/char_betty.PSK" );
	m_CharacterAnimation = m_isGame->getSceneManager()->getMesh ( "data/models/UnrealMesh/char_betty_anim.PSA" );
	m_CharacterTexture0=m_isGame->getVideoDriver()->getTexture ( "data/models/UnrealMesh/char_betty_tex.tga" );
	m_CharacterTexture1=m_isGame->getVideoDriver()->getTexture ( "data/models/UnrealMesh/char_betty_tex.tga" );
	m_CharacterTexture2=m_isGame->getVideoDriver()->getTexture ( "data/models/UnrealMesh/char_betty_tex.tga" );
	//
	LoadingMesh();
	m_isEventManager->attach ( Events::CHARACTER_EVENT, this );
}

GOCharacter::~GOCharacter()
{
	m_isEventManager->detach ( Events::CHARACTER_EVENT, this );
	//dtor
}


void GOCharacter::LoadingMesh()
{
	m_CharacterNode = m_isGame->getSceneManager()->addAnimatedMeshSceneNode ( m_CharacterMesh );

	if ( m_CharacterNode )
	{
		m_CharacterNode->getMaterial ( 0 ).setTexture ( 0,  m_CharacterTexture0 );
		m_CharacterNode->getMaterial ( 1 ).setTexture ( 0,  m_CharacterTexture1 );
		m_CharacterNode->getMaterial ( 2 ).setTexture ( 0,  m_CharacterTexture2 );
		m_CharacterNode->setMaterialFlag ( EMF_LIGHTING, false );
		s32 begin=0, end=0;
		f32 speed=24;
		//test
		//idle
		//jump
		//run
		//walk
		core::stringc SelectAnimation="idle";
		( ( SSkinnedMesh * ) m_CharacterAnimation )->getFrameLoop ( SelectAnimation , begin, end, speed );
		( ( ISkinnedMesh * ) m_CharacterMesh )->useAnimationFrom ( ( ( ISkinnedMesh * ) m_CharacterAnimation ) );
		m_CharacterNode->setFrameLoop ( begin, end );
		m_CharacterNode->setAnimationSpeed ( speed );
		m_CharacterNode->setLoopMode ( true );
		m_CharacterNode->setPosition ( core::vector3df ( 0,300,-400 ) );
		m_CharacterNode->setRotation ( core::vector3df ( -90,0,0 ) );
	}
}

void	GOCharacter::onEvent ( const EEvent *ev, const EventManager *evMgr )
{
	if ( ev->getEventID() != Events::CHARACTER_EVENT )
	{
		return;
	}

	if ( strcmp ( static_cast< const EvGameCharacterEvent *> ( ev )->name, m_GameObjectName ) !=0 )
	{
		return;
	}
	printf("EVENT!!!!");
	if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.Jump )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.MovementForward )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.MovementBack )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.MovementLeft )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.MovementRight )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.Action0 )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.Action1 )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.Action2 )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.Action3 )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.Action4 )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.Action5 )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.Action6 )
	{
	}
	else if ( static_cast< const EvGameCharacterEvent *> ( ev )->data.Action7 )
	{
	}
}
