//// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  This source code has been donated to the Public Domain.  Do
//  whatever you want with it.
//
//// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Logs
//
//		Handles the different type of logging, and pick the proper output for each one of them
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CORE_LOGS_H
#define CORE_LOGS_H



class Logs
{
		// ** Static Members
		// ////////////////////////////////////////////////////////
	private:
		// TODO add an "InGame console", ".log file handle", etc.
		static bool		s_newSession;


		// ** Static Methods
		// ////////////////////////////////////////////////////////
	public:
		static void		error ( const char *msg );
		static void		warning ( const char *msg );
		static void		info ( const char *msg );
		static void		debug ( const char *msg );
		static void		trace ( const char *header, const char *msg );

		static void		newPointer ( void *ptr, const char *clsname, const char *filename, int lineNumber );
};



#endif