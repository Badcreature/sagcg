// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef EventManager_H
#define EventManager_H

#include <map>
#include <list>
#include "EEventReceiver.h"
#include "EEvent.h"
#include "EventManager.h"
using namespace std;

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The structure of our Events ID
struct Events
{
	enum
	{
	    EVENT_NULL= 0,			// Null event
	    IRRLICHT_EVENT,			// EvIrrlichtEvents
	    GAME_SWF_EVENT,			// GameSWF Events
	    CHARACTER_EVENT,		// Event for GAME OBJECTS GOCharacter
	    // Other Event
	    EVENT_COUNT,			// Event Count
	};
};
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class EventManager
{
	private:
		static const bool			SHOW_TRACE = false;

	private:
		typedef std::list<EEventReceiver *>			ReceiverList;
		typedef ReceiverList::iterator				ReceiverListIter;
		typedef ReceiverList::const_iterator		ReceiverListConstIter;

		typedef std::map<EEvent::ID, ReceiverList>	EventList;		// event -> list of subscribers
		typedef EventList::iterator					EventListIter;
		typedef EventList::const_iterator			EventListConstIter;

		typedef std::list<const EEvent *>			DelayedEventQueue;
		typedef DelayedEventQueue::iterator			DelayedEventQueueIter;
		typedef DelayedEventQueue::const_iterator	DelayedEventQueueConstIter;

		typedef struct EventAssociation
		{
			EEvent::ID eId;
			EEventReceiver *receiver;
			bool attach;
		};

		typedef std::list<EventAssociation> AssocList;
		typedef AssocList::iterator			AssocListIter;

		// Members

	private:
		EventList					m_events;
		mutable DelayedEventQueue	m_eventQueue;

		AssocList					m_listEdits;
		int							m_raisingEvent;
		static EventManager			&s_eventManager;


		// Ctors / Dtor
	public:
		EventManager();
		virtual						~EventManager();

	private:
		void						_trace ( const char *msg ) const;
		bool						_attach ( EEvent::ID eventID, EEventReceiver *eventReceiver );
		bool						_detach ( EEvent::ID eventID, EEventReceiver *eventReceiver );
		static EventManager &setup();

		// Forbidden.
		EventManager ( const EventManager & );

	public:
		bool						attach ( EEvent::ID eventID, EEventReceiver *eventReceiver );
		bool						detach ( EEvent::ID eventID, EEventReceiver *eventReceiver );

		void						raise ( const EEvent &ev );
		void						raise ( const EEvent *ev );

		void						raiseAsync ( const EEvent *ev )	const;

		void						refresh();

		// ** IUpdatable impl.
		void						Update ( double timestamp );

		inline static EventManager &getInstance();
};

EventManager &EventManager::getInstance()
{
	return s_eventManager;
}

#endif // EventManager_H
