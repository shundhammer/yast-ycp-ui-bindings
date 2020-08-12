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

  File:		YCPItemParser.h

  Author:	Stefan Hundhammer <shundhammer@suse.de>

/-*/

#ifndef YCPItemParser_h
#define YCPItemParser_h

#include <ycp/YCPTerm.h>
#include "YCPItem.h"


/**
 * Parser for SelectionBox, ComboBox, MultiSelectionBox item lists
 **/
class YCPItemParser
{
public:

    /**
     * Parse an item list:
     *
     *	   [
     *	       `item(`id( `myID1 ), "Label1" ),
     *	       `item(`id( `myID2 ), `icon( "icon2.png"), "Label2", true ),
     *	       "Label3"
     *	   ]
     *
     * If 'allowDescription' is true, also accept (in addition to above):
     *
     *	   [
     *	       `item(`id( `myID1 ), "Label1", "Description1" ),
     *	       `item(`id( `myID2 ), `icon( "icon2.png"), "Label2", "Description2", true ),
     *	   ]
     *
     * Return a list of newly created YItem-derived objects.
     *
     * This function throws exceptions if there are syntax errors.
     **/
    static YItemCollection parseItemList( const YCPList & ycpItemList );

    /**
     * Parse an item list with (optional) descriptions for each item:
     *
     *	   [
     *	       `item(`id( `myID1 ), "Label1", "Description1" ),
     *	       `item(`id( `myID2 ), `icon( "icon2.png"), "Label2", "Description2", true ),
     *	       `item(`id( `myID3 ), `icon( "icon3.png"), "Label3" ),
     *	       "Label4"
     *	   ]
     *
     * Return a list of newly created YItem-derived objects.
     *
     * This function throws exceptions if there are syntax errors.
     **/
    static YItemCollection parseDescribedItemList( const YCPList & ycpItemList );


protected:


    /**
     * Internal version of the item parser that supports plain YItems and YDescribedItems.
     **/
    static YItemCollection parseItemListInternal( const YCPList & ycpItemList,
                                                  bool		  allowDescription = false );

    /**
     * Parse an item term:
     *
     *	       `item(`id( `myID1 ), "Label1" )
     *	       `item(`id( `myID2 ), `icon( "icon2.png"), "Label2", true )
     *
     * Everything except the label is optional.
     *
     * This function throws exceptions if there are syntax errors.
     **/
    static YCPItem *    parseItem( const YCPTerm &      itemTerm,
                                   bool                 allowDescription );

    /**
     * Parse one item and create a YCPItem from it.
     *
     * This function throws exceptions if there are syntax errors.
     **/
    static YCPItem *    parseItem( const YCPValue &	item,
                                   bool			allowDescription );

};


#endif // YCPItemParser_h
