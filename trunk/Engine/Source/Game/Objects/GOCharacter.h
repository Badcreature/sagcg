#ifndef GAME_OBJECTS_GOCharacter_H
#define GAME_OBJECTS_GOCharacter_H

class StateMachine;
class EventManager;

class GOCharacter : public  BaseGameObjects,  public EEventReceiver
{
	public:
		/** Default constructor */
		GOCharacter();
		/** Default destructor */
		virtual ~GOCharacter();
	protected:
	private:
		// External callbacks
		virtual void	LoadingMesh();
		virtual void	update ( float dt )		{};	// game update: update


		char *m_GameObjectName;
		virtual const char *getGameObjectName() const
		{
			return m_GameObjectName;
		}

		// EReceiver
		virtual void	onEvent ( const EEvent *ev, const EventManager *evMgr );

		// Glodal
		StateMachine 		*m_isStateMachine;
		EventManager 		*m_isEventManager;
		Game 				*m_isGame;


		//Model
		IAnimatedMesh *m_CharacterMesh;
		IAnimatedMeshSceneNode *m_CharacterNode;
		IAnimatedMesh *m_CharacterAnimation;
		ITexture *m_CharacterTexture0;
		ITexture *m_CharacterTexture1;
		ITexture *m_CharacterTexture2;

		vector3df m_CharacterRotation;
		vector3df m_CharacterPosition;


};

#endif // GAME_OBJECTS_GOCharacter_H
