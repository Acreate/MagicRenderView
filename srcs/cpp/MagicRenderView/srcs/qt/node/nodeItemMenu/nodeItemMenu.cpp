#include "nodeItemMenu.h"

#include "../../tools/tools.h"
NodeItemMenu::NodeItemMenu( const QString &title, QWidget *parent ) : QMenu( title, parent ) {
	//quint64 quint64 = ( qulonglong ) ( this );
	//QString msg = QString( "构造了 -> %1" );
	//msg = msg.arg( quint64, 0, 16 );
	//tools::debug::printError( msg );
}
NodeItemMenu::~NodeItemMenu( ) {
	/*quint64 quint64 = ( qulonglong ) ( this );
	QString msg = QString( "析构了 -> %1" );
	msg = msg.arg( quint64, 0, 16 );
	tools::debug::printError( msg );*/
}
