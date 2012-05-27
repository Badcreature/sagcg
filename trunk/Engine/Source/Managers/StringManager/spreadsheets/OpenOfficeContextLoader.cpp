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
#include "OpenOfficeContextLoader.h"
#include "IReadFile.h"

OpenOfficeContextLoader::OpenOfficeContextLoader ( IrrlichtDevice *irrlichtdevice, const c8 *OpenOfficeDocument, const c8 *contextfile )
{
	//ctor
	m_file = 0;
	m_filebuffer = 0;
	m_Filesize=0;
	m_Buffersize=0;
	irrlichtdevice->getFileSystem()->addZipFileArchive ( OpenOfficeDocument );

	if ( contextfile )
	{
		m_file = irrlichtdevice->getFileSystem()->createAndOpenFile ( contextfile );
	}

	else
	{
		m_file = irrlichtdevice->getFileSystem()->createAndOpenFile ( "content.xml" );
	}

	if ( !m_file )
	{
		printf ( "Could not load file" );
	}

	else
	{
		m_Buffersize= ( sizeof ( wchar_t ) *m_file->getSize() );
		m_Filesize=m_file->getSize();
		m_filebuffer = ( wchar_t * ) malloc ( m_Buffersize );
		memset ( m_filebuffer,' ',m_Buffersize );
		m_file->seek ( 0 );
		m_file->read ( m_filebuffer, 1+m_Filesize );
		m_file->drop();
		m_file=0;
		// test write file
	}
}

bool  OpenOfficeContextLoader::writeOpenOfficeDocumentTextToFile ( const char *newOpenOfficeDocumentFile )
{
	FILE *pFile=0;

	if ( m_filebuffer )
	{
		pFile = fopen ( newOpenOfficeDocumentFile , "wb" );
		fwrite ( m_filebuffer , 1 , 1+m_Filesize , pFile );
		fclose ( pFile );
		return 1;
	}

	else
	{
		printf ( "buffer OpenOfficeDocument is free" );
		return 0;
	}
}

OpenOfficeContextLoader::~OpenOfficeContextLoader()
{
	//dtor
	if ( m_filebuffer )
	{
		free ( m_filebuffer );
	}
}
