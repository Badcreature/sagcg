#ifndef BaseGameObjects_BaseGameObjects_H
#define BaseGameObjects_BaseGameObjects_H

// ** Forward Declarations
// ////////////////////////////////////////////////////////
class GameObjectsManager;

// ** Main Class
// ////////////////////////////////////////////////////////
class BaseGameObjects
{
		// ** Friendships
		// ////////////////////////////////////////////////////////
		friend			class GameObjectsManager;

		// ** Ctors / Dtor
		// ////////////////////////////////////////////////////////
	protected:
		BaseGameObjects()
		{
			GameObjectsManager::getInstance()->addGameObject ( this );
		};
	public:
		virtual			~BaseGameObjects()
		{
			GameObjectsManager::getInstance()->deleteGameObject ( this );
		};


		// ** Members
		// ////////////////////////////////////////////////////////
	protected:

		// ** Methods
		// ////////////////////////////////////////////////////////
	public:
		// External callbacks
		virtual void	update ( float dt )		{};	// game update: update
		virtual const char *getGameObjectName() const
		{
			return "BaseGameObject";
		}
		


};



#endif