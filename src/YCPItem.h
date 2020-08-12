/****************************************************************************

Copyright (c) 2000 - 2010 Novell, Inc.
All Rights Reserved.

This program is free software; you can redistribute it and/or
modify it under the terms of version 2 of the GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, contact Novell, Inc.

To contact Novell about this file by physical or electronic mail,
you may find current contact information at www.novell.com

****************************************************************************

  File:		YCPItem.h

  Author:	Stefan Hundhammer <shundhammer@suse.de>

/-*/

#ifndef YCPItem_h
#define YCPItem_h

#include <ycp/YCPValue.h>
#include <ycp/YCPString.h>
#include <yui/YDescribedItem.h>


/**
 * Item class with YCPValue IDs
 **/
class YCPItem: public YDescribedItem
{
public:

    /**
     * Constructors
     **/
    YCPItem( const YCPString &	label )
	: YDescribedItem( label->value() )
	, _id( label )
	{}

    YCPItem( const YCPValue  & 	id,
             const YCPString &	label,
             const YCPString &  description,
	     const YCPString & 	iconName,
	     bool  		selected = false )
	: YDescribedItem( label->value(),
                          description->value(),
                          iconName->value(),
                          selected )
	, _id( id )
	{}

    /**
     * Destructor.
     **/
    virtual ~YCPItem()
	{}

    /**
     * Return 'true' if this item has an ID.
     **/
    bool hasId() const { return ! _id.isNull() && ! _id->isVoid(); }

    /**
     * Return this item's ID.
     **/
    YCPValue id() const { return _id; }

    /**
     * Set a new ID.
     **/
    void setId( const YCPValue & newId ) { _id = newId; }

    /**
     * Return this item's label as a YCPString.
     **/
    YCPString label() const { return YCPString( YDescribedItem::label() ); }

    /**
     * Set this item's label with a YCPString.
     **/
    void setLabel( const YCPString & newLabel )
	{ YItem::setLabel( newLabel->value() ); }

    /**
     * Return this item's description as a YCPString.
     **/
    YCPString description() const { return YCPString( YDescribedItem::description() ); }

    /**
     * Set this item's description with a YCPString.
     **/
    void setDescription( const YCPString & newDescription )
        { YDescribedItem::setDescription( newDescription->value() ); }

    /**
     * Return this item's icon name as a YCPString.
     **/
    YCPString iconName() const { return YCPString( YDescribedItem::iconName() ); }

    /**
     * Set this item's icon name with a YCPString.
     **/
    void setIconName( const YCPString & newIconName )
	{ YDescribedItem::setIconName( newIconName->value() ); }


private:
    YCPValue _id;
};


#endif // YCPItem_h
