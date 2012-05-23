//// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  This source code has been donated to the Public Domain.  Do
//  whatever you want with it.
//
//// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StateBase
//
//		State to be used with the StateMachine
//
//	Notes:
//		- Methods are virtual, but not pure. That way, a child class can decide to not implement some methods.
//		- Also, only update() receive a non-const StateMachine, which means States should not be calling switch/push/pop
//		  methods while in another callback.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef STATEMACHINE_STATEBASE_H
#define STATEMACHINE_STATEBASE_H



// ** Forward Declarations
// ////////////////////////////////////////////////////////
class StateMachine;



// ** Main Class
// ////////////////////////////////////////////////////////
class StateBase
{
		// ** Friendships
		// ////////////////////////////////////////////////////////
		friend			class StateMachine;


		// ** Ctors / Dtor
		// ////////////////////////////////////////////////////////
	protected:
		StateBase()								{};
	public:
		virtual			~StateBase()							{};


		// ** Members
		// ////////////////////////////////////////////////////////
	protected:

		// ** Methods
		// ////////////////////////////////////////////////////////
	public:
		// Internal callbacks (done by the StateMachine itself)
		virtual void	ctor ( const StateMachine *sm )	{};	// when added to the StateMachine stack
		virtual void	dtor ( const StateMachine *sm )	{};	// when removed from the StateMachine stack
		virtual void	pause ( const StateMachine *sm )	{};	// when a new state is added atop
		virtual void	resume ( const StateMachine *sm )	{};	// when the state above is removed


		// External callbacks
		virtual void	update ( StateMachine *sm )		{};	// game update: update
		virtual void	draw ( const StateMachine *sm )	{};	// game update: draw
		virtual void	draw2d ( const StateMachine *sm ) {}; // draw 2d elements in front
		virtual void	sleep ( const StateMachine *sm )	{};	// application is interrupted
		virtual void	wakeup ( const StateMachine *sm )	{};	// application is resumed

		// ** Configuration of the state
		// ////////////////////////////////////////////////////////

		virtual bool	isWorkingInParallel()	//If this option is true the state Update and Draw(draw2d) regardless of pause
		{
			return false;
		};

		virtual bool	isLoadingDisable()	//If this option is true the state Loding screen Disable.
		{
			return false;
		};


};



#endif