// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EEvent_H
#define EEvent_H


class EEvent
{

	public:
		typedef int					ID;

	protected:
		ID							m_id;

	protected:
		EEvent ( ID id ) : m_id ( id )	{};

	public:
		virtual						~EEvent() {};

	public:
		virtual ID					getEventID() const
		{
			return m_id;
		};

};


#endif // EEvent_H
