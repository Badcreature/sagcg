// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Created by Andrey Sidorov.
//	Copyright (C) 2012 Andrey Sidorov.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  This source code has been donated to the Public Domain.  Do
//  whatever you want with it.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include	"StdAfx.h"

namespace gameswf
{
	int g_UIFontFile=0;

	bool UIFontFileSelector ( const char *font_name, tu_string &file_name, bool is_bold, bool is_italic )
	{
		if ( 1 )
		{
			file_name = tu_string ( "data/fonts/OFLArialUnicode.otf" );
			return true;
		}

		else
		{
			//Vitaly: I'm not sure that this code works on all versions of Windows
			tu_stringi fontname = font_name;

			if ( is_bold )
			{
				fontname += " Bold";
			}

			if ( is_italic )
			{
				fontname +=  " Italic";
			}

			fontname += " (TrueType)";
			HKEY hKey;
			// try WinNT
			DWORD retCode = RegOpenKeyEx ( HKEY_LOCAL_MACHINE,
			                               "Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts",
			                               0,
			                               KEY_ALL_ACCESS,
			                               &hKey );

			if ( retCode != ERROR_SUCCESS )
			{
				// try Windows
				retCode = RegOpenKeyEx ( HKEY_LOCAL_MACHINE,
				                         "Software\\Microsoft\\Windows\\CurrentVersion\\Fonts",
				                         0,
				                         KEY_ALL_ACCESS,
				                         &hKey );

				if ( retCode != ERROR_SUCCESS )
				{
					return false;
				}
			}

			// Get the value of the 'windir' environment variable.
			tu_string windir ( getenv ( "WINDIR" ) );
			// Get value count.
			DWORD    cValues;              // number of values for key
			retCode = RegQueryInfoKey (
			              hKey,	// key handle
			              NULL,	// buffer for class name
			              NULL,	// size of class string
			              NULL,	// reserved
			              NULL,	// number of subkeys
			              NULL,	// longest subkey size
			              NULL,	// longest class string
			              &cValues,	// number of values for this key
			              NULL,	// longest value name
			              NULL,	// longest value data
			              NULL,	// security descriptor
			              NULL );	// last write time
			// Enumerate the key values.
			BYTE szValueData[MAX_PATH];
			TCHAR  achValue[MAX_PATH];

			for ( DWORD i = 0, retCode = ERROR_SUCCESS; i < cValues; i++ )
			{
				DWORD cchValue = MAX_PATH;
				DWORD dwValueDataSize = sizeof ( szValueData ) - 1;
				achValue[0] = '\0';
				retCode = RegEnumValueA ( hKey, i,
				                          achValue,
				                          &cchValue,
				                          NULL,
				                          NULL,
				                          szValueData,
				                          &dwValueDataSize );

				if ( retCode == ERROR_SUCCESS )
				{
					if ( ( fontname == ( char * ) achValue ) || ( ( strstr ( achValue, font_name ) != NULL ) && !is_italic && !is_bold ) )
					{
						file_name = windir + tu_string ( "\\Fonts\\" ) + ( char * ) szValueData;
						RegCloseKey ( hKey );
						return true;
					}
				}
			}

			RegCloseKey ( hKey );
		}

		return false;
	}
}