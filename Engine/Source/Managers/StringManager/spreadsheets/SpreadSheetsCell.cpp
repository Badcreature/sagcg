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
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "SpreadSheetsCell.h"

SpreadSheetsCell::SpreadSheetsCell ( long line, long column, wchar_t *data, bool isHash )
{
	//ctor
	m_isHash=isHash;
	m_line=line;
	m_column=column;
	m_data=0;

	if ( data )
	{
		setData ( data );
	}

	m_dataHash=0;

	if ( m_isHash && m_data )
	{
		UpdateHash();
	}
}

void SpreadSheetsCell::setData ( wchar_t *data )
{
	if ( m_data )
	{
		free ( m_data );
		m_data=0;
	}

	m_data= ( wchar_t * ) malloc ( sizeof ( &data ) );
	memset ( m_data,0,sizeof ( &data ) );
	memcpy ( m_data,data,sizeof ( &data ) );
}

wchar_t *SpreadSheetsCell::getData()
{
	return m_data;
}

long SpreadSheetsCell::getLine()
{
	return m_line;
}
long SpreadSheetsCell::getColumn()
{
	return m_column;
}
void SpreadSheetsCell::setLine ( long line )
{
	m_line=line;
}
void SpreadSheetsCell::setColumn ( long column )
{
	m_column=column;
}

//Hash
bool SpreadSheetsCell::getIsHash()
{
	return m_isHash;
}
void SpreadSheetsCell::setIsHash ( bool isHash )
{
	m_isHash=isHash;

	if ( m_isHash && m_data )
	{
		UpdateHash();
	}

	else if ( !m_isHash && m_dataHash )
	{
		free ( m_dataHash );
		m_dataHash=0;
	}
}
wchar_t *SpreadSheetsCell::getHash()
{
	return 0;
}

void SpreadSheetsCell::UpdateHash()
{
}
//////
SpreadSheetsCell::~SpreadSheetsCell()
{
	if ( m_data )
	{
		free ( m_data );
		m_data=0;
	}

	if ( m_dataHash )
	{
		free ( m_dataHash );
		m_dataHash=0;
	}

	//dtor
}
