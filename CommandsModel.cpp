/*
    Copyright (C) 2010 Casey Link <unnamedrambler@gmail.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 3 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "CommandsModel.h"

#include "ViewMonitor.h"

#include <QDebug>

/*
the commands based on the color changes:

   Commands
                            Lightness change
   Hue change      None    1 Darker   2 Darker

        None                  push        pop
     1 Step        add    subtract   multiply
     2 Steps    divide         mod        not
     3 Steps   greater     pointer     switch
     4 Steps duplicate        roll in(number)
     5 Steps  in(char) out(number)  out(char)
*/
CommandsModel::CommandsModel( ViewMonitor* monitor, QObject* parent ): QAbstractTableModel( parent ), mMonitor( monitor )
{
    mCommands.insert( 0, Command( "nop", "Null" ) );
    mCommands.insert( 1, Command( "add", "" ) );
    mCommands.insert( 2, Command( "divide", "" ) );
    mCommands.insert( 3, Command( "greater", "" ) );
    mCommands.insert( 4, Command( "duplicate", "" ) );
    mCommands.insert( 5, Command( "in(char)", "" ) );

    mCommands.insert( 6, Command( "push", "" ) );
    mCommands.insert( 7, Command( "subtract", "" ) );
    mCommands.insert( 8, Command( "mod", "" ) );
    mCommands.insert( 9, Command( "pointer", "" ) );
    mCommands.insert( 10, Command( "roll", "" ) );
    mCommands.insert( 11, Command( "out(number)", "" ) );

    mCommands.insert( 12, Command( "pop", "" ) );
    mCommands.insert( 13, Command( "multiply", "" ) );
    mCommands.insert( 14, Command( "not", "" ) );
    mCommands.insert( 15, Command( "switch", "" ) );
    mCommands.insert( 16, Command( "in(number)", "" ) );
    mCommands.insert( 17, Command( "out(char)", "" ) );

}

QVariant CommandsModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
        return QVariant();

    Q_ASSERT( index.row() < 7 && index.column() < 4 );

    switch ( role ) {
    case Qt::DisplayRole:
        return mCommands.at( index.row() + index.column() * 6 ).name;
    case Qt::BackgroundRole:
        return mMonitor->colorForIndex( colorIndex( index ) );
    case CommandsModel::ColorIndexRole:
        return colorIndex( index );
    case CommandsModel::CommandRole: {
        Command command = mCommands.at( index.row() + index.column() * 6 );
        command.index = colorIndex( index );
        command.color = mMonitor->colorForIndex( colorIndex( index ) );
        return QVariant::fromValue<Command>( command );
    }
    default:
        return QVariant();
    }
}

int CommandsModel::colorIndex( const QModelIndex& index ) const
{
    int cmdIdx = index.row() + index.column() * 6;
    int cmdHue = cmdIdx % 6;
    int cmdLight = ( ( cmdIdx / 6 ) + 3 ) % 3;

    int curColorIdx = mMonitor->currentColorIndex();
    int newColorY = ( ( curColorIdx / 3 ) + cmdHue ) % 6;
    int newColorX = ( ( curColorIdx % 3 ) + cmdLight ) % 3;
    int newColorIdx = ( newColorX ) + ( newColorY * 3 );
//     if( mCommands.at( index.row() + index.column() * 6 ).name == "add" ) {
//          qDebug()  << curColorIdx<< "(" << newColorX << "," << newColorY << ")" << newColorIdx;
//     }
    return newColorIdx;
}


int CommandsModel::rowCount( const QModelIndex& /* parent */) const
{
    return 6;
}

int CommandsModel::columnCount( const QModelIndex& /* parent */) const
{
    return 3;
}


