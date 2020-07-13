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


  File:		YCPMenuItemParser.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YCPMenuItemParser_h
#define YCPMenuItemParser_h

#include <ycp/YCPTerm.h>
#include "YCPMenuItem.h"


/**
 * Parser for menu item lists
 **/
class YCPMenuItemParser
{
public:

    /**
     * Parse a menu item list:
     *
     *     [
     *         `item(`id( `myID1 ), "Label1" ),
     *         `item(`id( `myID2 ), `icon( "icon2.png"), "Label2", ),
     *         `menu(`id( `myID3 ), `icon( "icon3.png"), "Label3", [ subMenuList ] ),
     *         `item(`id( `myID3 ), `icon( "icon3.png"), "Label3", [ subMenuList ] ),
     *     ]
     *
     * Return a list of newly created YItem-derived objects.
     *
     * This function throws exceptions if there are syntax errors.
     **/
    static YItemCollection parseMenuItemList( const YCPList & ycpItemList );


    /**
     * Parse one item and create a YCPMenuItem from it.
     *
     * This function throws exceptions if there are syntax errors.
     **/
    static YCPMenuItem * parseMenuItem( YCPMenuItem * parent, const YCPValue & item );

protected:

    /**
     * Parse an item term:
     *
     *         `item(`id( `myID1 ), "Label1" )
     *         `item(`id( `myID2 ), `icon( "icon2.png"), "Label2", )
     *         `menu(`id( `myID3 ), `icon( "icon3.png"), "Label3", [ subMenuList ] )
     *         `item(`id( `myID3 ), `icon( "icon3.png"), "Label3", [ subMenuList ] )
     *
     * Everything but the label is optional. If no ID is specified, the label
     * will be used as ID, which might not be very useful if labels are translated.
     *
     * This function throws exceptions if there are syntax errors.
     **/
    static YCPMenuItem * parseMenuItem( YCPMenuItem * parent, const YCPTerm & itemTerm );

    /**
     * Return 'true' if 'str' starts with 'word'. This is case insensitive.
     **/
    static bool startsWith( const string & str, const char * word );

};


#endif // YCPMenuItemParser_h
