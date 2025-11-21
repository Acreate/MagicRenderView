#include <QNetworkInterface>
#include <qfile.h>

#include "qt/application/application.h"
#include "qt/tools/tools.h"
#include "qt/windows/mainWindow.h"

int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false ) {
		tools::debug::printError( "程序初始化失败" );
		return -1;
	}
	QList< QNetworkInterface > networkInterfaces = QNetworkInterface::allInterfaces( );
	for( auto &interface : networkInterfaces ) {
		auto targetFlags = QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::IsPointToPoint;
		QNetworkInterface::InterfaceFlags interfaceFlags = interface.flags( );
		qDebug( ) << interfaceFlags;
		if( interfaceFlags & targetFlags ) {
			qDebug( ) << interface;
			continue;
			QList< QNetworkAddressEntry > addressEntries = interface.addressEntries( );
			for( QNetworkAddressEntry &entry : addressEntries ) {
				qDebug( ) << entry;

				//QHostAddress address = entry.ip( );

				//auto networkLayerProtocol = address.protocol( );
				//if( networkLayerProtocol == QAbstractSocket::IPv6Protocol ) {
				//	qDebug( ) << "Interface:" << interface.name( ) << "IPv6 Address:" << address.toString( ) << "\n";
				//} else if( networkLayerProtocol == QAbstractSocket::IPv4Protocol ) {
				//	qDebug( ) << "Interface:" << interface.name( ) << "IPv4 Address:" << address.toString( );
				//}
			}
		}
	}
	return 0;
	MainWindow mainwidget;
	mainwidget.show( );

	return app.exec( );
}
