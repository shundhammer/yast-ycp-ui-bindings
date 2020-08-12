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

  File:		YCPItemWriter.cc

  Author:	Stefan Hundhammer <shundhammer@suse.de>

/-*/

#include <ycp/YCPVoid.h>
#include <ycp/YCPBoolean.h>
#include "YCPItemWriter.h"
#include <yui/YUISymbols.h>


YCPList
YCPItemWriter::itemList( YItemConstIterator	begin,
                         YItemConstIterator	end )
{
    return itemListInternal( begin, end,
                             false ); // withDescription
}


YCPList
YCPItemWriter::describedItemList( YItemConstIterator	begin,
                                  YItemConstIterator	end )
{
    return itemListInternal( begin, end,
                             true ); // withDescription
}


YCPList
YCPItemWriter::itemListInternal( YItemConstIterator	begin,
                                 YItemConstIterator	end,
                                 bool			withDescription )
{
    YCPList itemList;

    for ( YItemConstIterator it = begin; it != end; ++it )
    {
	const YItem * item = dynamic_cast<const YItem *> (*it);

	if ( item )
	{
	    itemList->add( itemTerm( item, withDescription ) );
	}
    }

    return itemList;
}


YCPValue
YCPItemWriter::itemTerm( const YItem * item, bool withDescription )
{
    if ( ! item )
	return YCPVoid();

    YCPTerm itemTerm( YUISymbol_item );                 // `item()

    const YCPItem * ycpItem = dynamic_cast<const YCPItem *> (item);

    if ( ycpItem && ycpItem->hasId() )
    {
	YCPTerm idTerm( YUISymbol_id );                 // `id()
	idTerm->add( ycpItem->id() );
	itemTerm->add( idTerm );
    }

    if ( item->hasIconName() )
    {
	YCPTerm iconTerm( YUISymbol_icon );             // `icon()
	iconTerm->add( YCPString( item->iconName() ) );
	itemTerm->add( iconTerm );
    }

    itemTerm->add( YCPString( item->label() ) );        // label

    if ( withDescription )
    {
        string description;

        const YDescribedItem * describedItem = dynamic_cast<const YDescribedItem *>( item );

        if ( describedItem )
            description = describedItem->description();

        itemTerm->add( YCPString( description ) );      // description

    }

    if ( item->selected() )                             // isSelected
	itemTerm->add( YCPBoolean( item->selected() ) );

    return itemTerm;
}


