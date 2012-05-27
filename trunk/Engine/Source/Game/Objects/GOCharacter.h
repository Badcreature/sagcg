#ifndef GAME_OBJECTS_GOCharacter_H
#define GAME_OBJECTS_GOCharacter_H


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
		virtual void	update ( float dt )		{};	// game update: update
		virtual const char *getGameObjectName() const
		{
			return "GOCharacter";
		}
		
		// EReceiver
		virtual void	onEvent ( const EEvent *ev, const EventManager *evMgr ){};

};

#endif // GAME_OBJECTS_GOCharacter_H
