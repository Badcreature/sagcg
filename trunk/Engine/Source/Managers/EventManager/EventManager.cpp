// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include <map>
#include <list>
#include "EEventReceiver.h"
#include "EEvent.h"
#include "EventManager.h"

EventManager &EventManager::s_eventManager = setup();

// Ctors / Dtor
EventManager::EventManager()
{
	m_raisingEvent=0;
}

EventManager::~EventManager()
{
	m_eventQueue.clear();
}

// Methods
EventManager &EventManager::setup()
{
	static EventManager e;
	return e;
}

void EventManager::_trace ( const char *msg ) const
{
	if ( SHOW_TRACE )
	{
		//	Logs::trace("EventManager", msg);
	}
}

bool EventManager::_attach ( EEvent::ID eventID, EEventReceiver *eventReceiver )
{
	EventListIter eIter = m_events.find ( eventID );

	if ( eIter == m_events.end() )
	{
		m_events[eventID].push_back ( eventReceiver );
	}

	else
	{
		for ( ReceiverListIter rIter = eIter->second.begin(); rIter != eIter->second.end(); ++rIter )
		{
			if ( ( *rIter ) == eventReceiver )
			{
				return false;
			}
		}

		eIter->second.push_back ( eventReceiver );
	}

	return true;
}

bool EventManager::_detach ( EEvent::ID eventID, EEventReceiver *eventReceiver )
{
	EventListIter eIter = m_events.find ( eventID );

	if ( eIter == m_events.end() )
	{
		return false;
	}

	for ( ReceiverListIter rIter = eIter->second.begin(); rIter != eIter->second.end(); ++rIter )
	{
		if ( ( *rIter ) == eventReceiver )
		{
			eIter->second.erase ( rIter );

			if ( eIter->second.empty() )
			{
				m_events.erase ( eventID );
			}

			return true;
		}
	}

	return false;
}

bool EventManager::attach ( EEvent::ID eventID, EEventReceiver *eventReceiver )
{
	EventAssociation evAssoc = {eventID, eventReceiver, true};
	m_listEdits.push_back ( evAssoc );
	return true;
}

bool EventManager::detach ( EEvent::ID eventID, EEventReceiver *eventReceiver )
{
	EventAssociation evAssoc = {eventID, eventReceiver, false};
	m_listEdits.push_back ( evAssoc );
	return true;
}

void EventManager::raise ( const EEvent &ev )
{
	refresh();
	++m_raisingEvent;
	EventListConstIter eIter = m_events.find ( ev.getEventID() );

	if ( eIter != m_events.end() )
	{
		const ReceiverList		&rList = eIter->second;
		ReceiverListConstIter	rIter = rList.begin();
		EEventReceiver *receiver = NULL;

		for ( ; rIter != rList.end(); ++rIter )
		{
			receiver = *rIter;
			receiver->onEvent ( &ev, this );
		}
	}

	--m_raisingEvent;
}

void EventManager::raise ( const EEvent *ev )
{
	raise ( *ev );
}


void EventManager::raiseAsync ( const EEvent *ev ) const
{
	m_eventQueue.push_back ( ev );
}

void EventManager::refresh()
{
	if ( m_raisingEvent > 0 )
	{
		// do not alter listing if events are being raised
		return;
	}

	// process attach/detach requests
	AssocListIter alIter = m_listEdits.begin();

	for ( ; alIter != m_listEdits.end(); ++alIter )
	{
		if ( alIter->attach == true )
		{
			_attach ( alIter->eId, alIter->receiver );
		}

		else
		{
			_detach ( alIter->eId, alIter->receiver );
		}
	}

	m_listEdits.clear();
}


// Methods (Updatable)

void EventManager::Update ( double timestamp )
{
	while ( m_eventQueue.size() > 0 )
	{
		const EEvent *ev = m_eventQueue.front();
		raise ( ev );
		delete ev;
		m_eventQueue.pop_front();
	}
}

