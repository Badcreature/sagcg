//// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  This source code has been donated to the Public Domain.  Do
//  whatever you want with it.
//
//// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "StateMachine.h"
#include "StateBase.h"
#include "Logs.h"

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ctors / Dtor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StateMachine::StateMachine() :
	m_stackIdx ( INVALID_IDX ),
	m_isInDrawCallback ( false ),
	m_timestamp ( 0.0 )
{
}

StateMachine::~StateMachine()
{
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods (Privates/Protected)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StateMachine::_trace ( const char *msg ) const
{
	if ( SHOW_TRACE )
	{
		Logs::trace ( "StateMachine", msg );
	}
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StateMachine::_switchState ( StateBase *state )
{
	while ( m_stateList.size() > 0 )
	{
		m_stateList.back()->dtor ( this );
		delete m_stateList.back();
		m_stateList.pop_back();
	}

	_pushState ( state );
}

void StateMachine::_pushState ( StateBase *state )
{
	if ( m_stateList.size() > 0 )
	{
		m_stateList.back()->pause ( this );
	}

	m_stateList.push_back ( state );

	//
	if ( !m_stateList.back()->isLoadingDisable() )
	{
		Loading::getInstance()->LoadingOn();
	}

	//
	m_stateList.back()->ctor ( this );
}
void StateMachine::_loadState ( StateBase *state )
{
	if ( m_stateList.size() > 0 )
	{
		if ( m_stateList.size() > 1 )
		{
			m_stateList.insert ( m_stateList.end()-1, state );
			m_stateList.at ( m_stateList.size()-2 )->ctor ( this );
			m_stateList.at ( m_stateList.size()-2 )->pause ( this );
		}

		else
		{
			m_stateList.insert ( m_stateList.begin(), state );
			m_stateList.front()->ctor ( this );
			m_stateList.front()->pause ( this );
		}
	}

	else
	{
		m_stateList.push_back ( state );
		m_stateList.back()->ctor ( this );
	}
}

void StateMachine::popState()
{
	if ( m_stateList.size() > 0 )
	{
		m_stateList.back()->dtor ( this );
		delete m_stateList.back();
		m_stateList.pop_back();

		if ( m_stateList.size() > 0 )
		{
			m_stateList.back()->resume ( this );
		}
	}
}

int StateMachine::getTimeStamp() const
{
	return m_timestamp;
}

void StateMachine::recurseDraw() const
{
	// Must be in the draw() callback
	if ( m_isInDrawCallback )
	{
		// Backup of the stack index
		uint previousIdx = m_stackIdx;

		// If the stack index is -1, it means we are pointing
		// on the last element (the one on top of the stack)
		if ( m_stackIdx == INVALID_IDX )
		{
			m_stackIdx = m_stateList.size() - 1;
		}

		// If the index isn't 0, it means there is a state
		// underneath the current one: we can recurse
		if ( m_stackIdx > 0 )
		{
			m_stateList[--m_stackIdx]->draw ( this );
		}

		// Restoration of the stack index
		m_stackIdx = previousIdx;
	}
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods (IUpdatable, IDrawable, ISleepable impl.)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StateMachine::update ( int timestamp )
{
	m_timestamp = timestamp;

	if ( m_stateList.size() > 0 )
	{
		for ( int i = 0; i < m_stateList.size(); i++ )
		{
			if ( m_stateList[i]->isWorkingInParallel() &&m_stateList[i]!=m_stateList.back() )
			{
				m_stateList[i]->update ( this );
			}
		}

		m_stateList.back()->update ( this );
	}
}

void StateMachine::draw() const
{
	//
	Loading::getInstance()->LoadingOff();

	//
	if ( m_stateList.size() > 0 )
	{
		m_isInDrawCallback = true;

		for ( int i = 0; i < m_stateList.size(); i++ )
		{
			if ( m_stateList[i]->isWorkingInParallel() &&m_stateList[i]!=m_stateList.back() )
			{
				m_stateList[i]->draw ( this );
			}
		}

		m_stateList.back()->draw ( this );
		m_isInDrawCallback = false;
	}
}

void StateMachine::draw2d() const
{
	if ( m_stateList.size() > 0 )
	{
		m_isInDrawCallback = true;

		for ( int i = 0; i < m_stateList.size(); i++ )
		{
			if ( m_stateList[i]->isWorkingInParallel() &&m_stateList[i]!=m_stateList.back() )
			{
				m_stateList[i]->draw2d ( this );
			}
		}

		m_stateList.back()->draw2d ( this );
		m_isInDrawCallback = false;
	}
}


void StateMachine::sleep()
{
	// We start with the Last In
	for ( StateListRevIter iter = m_stateList.rbegin(); iter != m_stateList.rend(); ++iter )
	{
		( *iter )->sleep ( this );
	}
}

void StateMachine::wakeup()
{
	// We start with the First In
	for ( StateListIter iter = m_stateList.begin(); iter != m_stateList.end(); ++iter )
	{
		( *iter )->wakeup ( this );
	}
}