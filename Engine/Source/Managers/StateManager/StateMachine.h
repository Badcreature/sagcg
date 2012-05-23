//// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  This source code has been donated to the Public Domain.  Do
//  whatever you want with it.
//
//// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StateMachine
//
//		State machine to help with the handling of the game logics
//
//	Notes
//		- sleep()/wakeup() warn _every_ States on the stack, not just the top-most one.
//		  (sleep() starts with the Last In, while wakeup() starts with the First In)
//		- When the StateMachine is deallocated, the remaining states have their dtor() called, followed by the real dtor
//
//	Warnings:
//		- StateMachine handles the NEW and the DELETE on the states. switchState and pushState returns the created
//		- Your state's dtor() or pause() are called as soon as you switch or push a state, even if your update() isn't done yet
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef STATEMACHINE_STATEMACHINE_H
#define STATEMACHINE_STATEMACHINE_H

#include <vector>



// ** Forward Declarations
// ////////////////////////////////////////////////////////
class StateBase;



// ** Main Class
// ////////////////////////////////////////////////////////
class StateMachine
{
		// ** Constants
		// ////////////////////////////////////////////////////////
	private:
		static const bool	SHOW_TRACE = false;
		static const uint	INVALID_IDX = ( uint )-1;


		// ** Typedefs
		// ////////////////////////////////////////////////////////
	private:
		typedef std::vector<StateBase *>	StateList;
		typedef StateList::iterator			StateListIter;
		typedef StateList::const_iterator	StateListConstIter;
		typedef StateList::reverse_iterator	StateListRevIter;


		// ** Members
		// ////////////////////////////////////////////////////////
	private:
		StateList			m_stateList;
		int					m_timestamp;
		mutable uint		m_stackIdx;
		mutable bool		m_isInDrawCallback;


		// ** Ctors / Dtor
		// ////////////////////////////////////////////////////////
	private:
		StateMachine();
	public:
		virtual				~StateMachine();


		// ** Methods
		// ////////////////////////////////////////////////////////
	protected:
		void				_trace ( const char *msg ) const;
		void				_switchState ( StateBase *state );
		void				_pushState ( StateBase *state );
		void				_loadState ( StateBase *state );


	public:
		// Info
		inline static		StateMachine &getInstance();
		int					stackSize()			const
		{
			return m_stateList.size();
		};


		// API
		template <typename T>
		T *switchState()
		{
			T *t = new T();
			_switchState ( t );
			return t;
		}

		template <typename T>
		T					*pushState()
		{
			T *t = new T();
			_pushState ( t );
			return t;
		};

		template <typename T>
		T					*loadState()
		{
			T *t = new T();
			_loadState ( t );
			return t;
		};

		void				popState();

		int					getTimeStamp() const;

		// Special - To call the state beneath, so it can draw itself as well
		void				recurseDraw()		const;


		// ** IUpdatable impl.
		void				update ( int timestamp );

		// ** IDrawable impl.
		void				draw()				const;
		void				draw2d()			const;
		int					getDrawingLayer()	const;

		// ** ISleepable impl.
		void				sleep();
		void				wakeup();

		inline StateBase *getState() const
		{
			return m_stateList.back();
		};

};

StateMachine &
StateMachine::getInstance()
{
	static StateMachine sm;
	return sm;
}

#endif