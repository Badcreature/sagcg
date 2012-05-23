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
#ifndef _SYS_H_
#define _SYS_H_

#include <time.h>

namespace TimeManager
{
	extern unsigned long g_last_steptime;

	unsigned long get_time_ms(); // ms
	void update_steptime();
	inline unsigned long get_steptime_ms()
	{
		return g_last_steptime;   // ms
	}
	inline float get_steptime_s()
	{
		return ( ( float ) get_steptime_ms() / 1000.0 );   // s
	}

	void sleep ( unsigned long sleep_time ); // ms

	clock_t clock();
}

#endif // _SYS_H_
