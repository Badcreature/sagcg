// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Created by Joint authors Vitatiy Paravishnik, Andrey Sidorov and other.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								  License.
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace TimeManager
//
//		This namespace contains additional handlers for the time
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "TimeManager.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <string.h>

#if defined WIN32
#include <windows.h>
#include <direct.h>
#elif defined OS_MACOSX || defined _LINUX
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>

#ifndef MAX_PATH
#define MAX_PATH PATH_MAX
#endif
#endif

namespace TimeManager
{
	unsigned long g_last_time = get_time_ms(); // ms
	unsigned long g_last_steptime = 0; // ms

	unsigned long get_time_ms() // ms
	{
#if defined WIN32
		return ( unsigned long ) timeGetTime();
#else
		struct timeval tv;
		struct timezone tz;
		gettimeofday ( &tv, &tz );
		unsigned long time_ms = ( tv.tv_sec * 1000 ) + ( tv.tv_usec / 1000 );
		return time_ms;
#endif
	}

	void update_steptime()
	{
		unsigned long new_time = get_time_ms();
		g_last_steptime = ( new_time > g_last_time ) ? ( new_time - g_last_time ) : 0;
		g_last_time = new_time;
	}

	void sleep ( unsigned long sleep_time )
	{
#if defined WIN32
		::Sleep ( sleep_time );
#else
		::usleep ( ( useconds_t ) ( sleep_time * 1000 ) );
#endif
	}
}

clock_t TimeManager::clock()
{
	return ::clock();
}
