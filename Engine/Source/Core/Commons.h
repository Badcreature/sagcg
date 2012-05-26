// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Created by Andrey Sidorov.
//	Copyright (C) 2012 Andrey Sidorov.
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
//  Please note that the SaGCG (simple-and-good-core-games) Engine is based in part on the work of the
//  Independent JPEG Group, zlib,libPng, Box2D, freetype, bullet, OpenAL, gameswf This means that if you use
//  the SaGCG (simple-and-good-core-games) Engine in your product, you must acknowledge somewhere in your
//  documentation that you've used the IJG code. It would also be nice to mention
//  that you use the SaGCG (simple-and-good-core-games)Engine, Irrlicht Engine, zlib, libPng, Box2D, freetype,
//  bullet, OpenAL, gameswf. See the README files in the jpeglib, zlib, libPng, Box2D, freetype, bullet, OpenAL,
//  gameswf for further informations.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CORE_COMMONS_H
#define CORE_COMMONS_H

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declarations and Define
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// debug
#define DBG						printf
#define LOG_DEBUG				0

#ifndef WIN32
#define OS_MACOSX
#else
#endif

// Enable Box2d engine
//#define BOX2D

// Enable Bullet engine
#define IRRBULLET
#define IRRBULLET_SHOW_DEBUG false

// Enable GameSWF engine
#define GAMESWF

// Enable FBX Mesh Loader
#define _IRR_COMPILE_WITH_FBX_LOADER_
// Enable PSK Mesh loader
#define _IRR_COMPILE_WITH_UNREAL_LOADER_

// FPS
#define MAX_FPS					120

// DRAW_TO_UPDATE
#define	DRAW_TO_UPDATE			1					//The number of the render for the update

//PHYSICS_2D
#define	PHYSICS_2D_DO_SLEEP		1					//doSleep improve performance by not simulating inactive bodies.
/*The suggested iteration count for Box2D is 8 for velocity and 3 for position. You can tune this number to
your liking, just keep in mind that this has a trade-off between speed and accuracy. Using fewer
iterations increases performance but accuracy suffers. Likewise, using more iterations decreases
performance but improves the quality of your simulation. */
#define	PHYSICS_2D_VELOCITY_ITERATIONS 6
#define	PHYSICS_2D_POSITION_ITERATIONS 2
// For small Delta time
#define	PHYSICS_2D_MINIMUM_TIMESTEP 1.0f / 600.0f

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Platform specifics
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defines / Typedefs
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef NULL
#define NULL					0
#endif

#ifndef null
#define null					0
#endif

#ifndef pure
#define pure					=0
#endif

#ifndef ABSF
#define ABSF(a)					(a>0.f?a:-1.f*a)
#endif

#ifdef WIN32

#ifndef min
#define min(a, b)				((a)<(b)?(a):(b))
#endif

#ifndef max
#define max(a, b)				((a)>(b)?(a):(b))
#endif

#define cmp_i_str(a,b)			stricmp(a,b)

#else

#define cmp_i_str(a,b)			strcasecmp(a,b)

#endif

//Should normally be a define for the low poly city display,
// ended up commenting out all the ifdefs cause we didn't manage to activate it properly for mac

// Basic Types
typedef unsigned char			byte;
typedef unsigned char			uchar;
typedef unsigned char			uint8;
typedef signed char				int8;


typedef unsigned short			ushort;
typedef unsigned short			word;
typedef unsigned short			uint16;
typedef signed short			int16;

typedef unsigned int			uint;
typedef unsigned int			dword;
typedef unsigned int			uint32;
typedef signed int				int32;

// 64 bits types are defined

/*
typedef int8	JavaByte;
typedef int16	JavaShort;
typedef int32	JavaInt;
typedef int64	JavaLong;
*/

//array sizeof, get number of element in a static array
#define asizeof(x)				(sizeof(x) / sizeof(x[0]))
#define ASIZEOF(x)				(sizeof(x) / sizeof(x[0]))

#define SQUARE(x)				( (x) * (x) )

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Asserts
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Macros
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// flag operations
#define TEST_FLAG(var, flag)	((var & (flag)) == (flag))
#define SET_FLAG(var, flag)		(var |= (flag))
#define CLEAR_FLAG(var, flag)	(var &= ~(flag))

// constants
#define GRAVITY					9.80665f
#define KM_TO_M					1000.f
#define KM_TO_CM				100000.f
#define M_TO_CM					100.0f
#define HOUR_TO_SECOND			3600.f
#define MILLISEC_TO_SEC			1000.f
#define KMH_TO_MS				(HOUR_TO_SECOND / KM_TO_M)
#define MS_TO_KMH				(KM_TO_M / HOUR_TO_SECOND)

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hacks
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// quick hack to be able to compile archeos code.

#endif
