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
#ifndef GAME_SpreadSheetsCell_H
#define GAME_SpreadSheetsCell_H

class SpreadSheetsCell
{
	public:
		/** Default constructor */
		SpreadSheetsCell ( long line, long column, wchar_t *data=0, bool isHash=false );
		void setData ( wchar_t *data=0 );
		wchar_t *getData();
		wchar_t *getHash();
		long getLine();
		long getColumn();
		void setLine ( long line );
		void setColumn ( long column );
		bool getIsHash();
		void setIsHash ( bool isHash );

		/** Default destructor */
		virtual ~SpreadSheetsCell();
	protected:
	private:
		void UpdateHash();
		bool m_isHash;
		long m_line;
		long m_column;
		wchar_t *m_data;
		wchar_t *m_dataHash;
};

#endif // GAME_SpreadSheetsCell_H
