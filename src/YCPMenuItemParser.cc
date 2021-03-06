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

  Author:	Stefan Hundhammer <shundhammer@suse.de>

/-*/


#include <ycp/YCPTerm.h>
#include <ycp/YCPBoolean.h>

#define y2log_component "ui"
#include <ycp/y2log.h>

#include "YCPMenuItemParser.h"
#include "YCP_UI_Exception.h"
#include <yui/YUISymbols.h>
#include <yui/YShortcut.h>

#define VERBOSE_PARSER	0


YItemCollection
YCPMenuItemParser::parseMenuItemList( const YCPList & itemList )
{
    YItemCollection itemCollection;
    itemCollection.reserve( itemList.size() );

    try
    {
	for ( int i=0; i < itemList->size(); i++ )
	{
	    YCPMenuItem * item = parseMenuItem( 0, // parent item
						itemList->value(i) );
	    itemCollection.push_back( item );
	}
    }
    catch ( YUIException & exception )
    {
	YItemIterator it = itemCollection.begin();

	while ( it != itemCollection.end() )
	{
	    // Delete all items created so far

	    YItem * item = *it;
	    ++it;
	    delete item;
	}

	throw;
    }

#if VERBOSE_PARSER
    y2debug( "%d items", itemCollection.size() );
#endif

    return itemCollection;
}



YCPMenuItem *
YCPMenuItemParser::parseMenuItem( YCPMenuItem * parent, const YCPValue & rawItem )
{
    YCPMenuItem * item = 0;

#if VERBOSE_PARSER
    y2debug( "Parsing: %s", rawItem->toString().c_str() );
#endif

    if ( rawItem->isTerm() &&
	 ( rawItem->asTerm()->name() == YUISymbol_item  ||	// `item(...)
	   rawItem->asTerm()->name() == YUISymbol_menu )   ) 	// `menu(...)
    {
	item = parseMenuItem( parent, rawItem->asTerm() );
    }
    else	// No term or neither `item(...) nor `menu(...)
    {
	YUI_THROW( YCPDialogSyntaxErrorException( "Expected `item(...)", rawItem ) );
    }

    return item;
}


YCPMenuItem *
YCPMenuItemParser::parseMenuItem( YCPMenuItem * parent, const YCPTerm & itemTerm )
{
    YCPValue	id	 	= YCPNull();
    YCPString	iconName 	= YCPNull();
    YCPString	label	 	= YCPNull();
    YCPList	subItemList	= YCPNull();

    const char * usage =
	"Expected: `item(`id(`myID), `icon(\"MyIcon.png\"), \"MyItemText\", list subItemList )";

#if VERBOSE_PARSER
    y2debug( "Parsing: %s", itemTerm->toString().c_str() );
#endif

    for ( int i=0; i < itemTerm->size(); i++ )
    {
	YCPValue arg = itemTerm->value(i);

#if VERBOSE_PARSER
	y2debug( "Parsing term arg #%d: %s", i, arg->toString().c_str() );
#endif

	if ( arg->isTerm() )	// `id(), `icon()
	{
	    YCPTerm term = arg->asTerm();

	    if ( term->size() != 1 )		// Both `id() and `icon() have 1 argument
		YUI_THROW( YCPDialogSyntaxErrorException( usage, itemTerm ) );

	    if ( term->name() == YUISymbol_id		// `id(...)
		 && id.isNull() )			// and don't have an ID yet
	    {
		id = term->value(0);
	    }
	    else if ( term->name() == YUISymbol_icon	// `icon(...)
		      && term->value(0)->isString()	// with a string argument
		      && iconName.isNull() )		// and don't have an icon name yet
	    {
		iconName = term->value(0)->asString();
	    }
	    else
	    {
		YUI_THROW( YCPDialogSyntaxErrorException( usage, itemTerm ) );
	    }
	}
	else if ( arg->isString()		// label (the user-visible text)
		  && label.isNull() )		// and don't have a label yet
	{
	    label = arg->asString();
	}
	else if( arg->isList()			// sub item list
		 && subItemList.isNull() )	// and don't have a sub item list yet
	{
	    subItemList = arg->asList();
	}
	else
	{
	    YUI_THROW( YCPDialogSyntaxErrorException( usage, itemTerm ) );
	}
    }

    if ( label.isNull() )		// the label is required
	YUI_THROW( YCPDialogSyntaxErrorException( usage, itemTerm ) );

    if ( iconName.isNull() )
	iconName = YCPString( "" );

    if ( startsWith( label->value(), "---" ) )   // separator item?
        label = YCPString( "" );

    if ( id.isNull() && ! label.isEmpty() ) // no `id() ?
	id = YCPString( YShortcut::cleanShortcutString( label->value() ) ); // use the label instead

    YCPMenuItem * item = new YCPMenuItem( parent, label, id, iconName );
    YUI_CHECK_NEW( item );

    if ( ! subItemList.isNull() )
    {
	for ( int i=0; i < subItemList->size(); i++ )
	{
	    parseMenuItem( item, subItemList->value(i) );
	}
    }

    return item;
}


bool YCPMenuItemParser::startsWith( const string & str, const char * word )
{
    return strncasecmp( str.c_str(), word, strlen( word ) )== 0;
}

