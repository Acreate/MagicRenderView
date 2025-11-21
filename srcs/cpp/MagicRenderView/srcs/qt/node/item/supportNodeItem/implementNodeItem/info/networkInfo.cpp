#include "networkInfo.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"
#include <QNetworkInterface>
#include <qdebug.h>
Imp_StaticMetaInfo( NetworkInfo, QObject::tr( "网络" ), QObject::tr( "信息" ) );

NetworkInfo::NetworkInfo( ) {
}
bool NetworkInfo::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意", true );
			addOutputProt< StringOutputPort >( "ipv4" );
			addOutputProt< StringOutputPort >( "ipv6" );
			addOutputProt< StringOutputPort >( "域名" );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				QList< QNetworkInterface > networkInterfaces = QNetworkInterface::allInterfaces( );
				for( auto &interface : networkInterfaces ) {
					if( interface.flags( ) & QNetworkInterface::IsUp && !( interface.flags( ) & QNetworkInterface::IsLoopBack ) ) {
						QList< QNetworkAddressEntry > addressEntries = interface.addressEntries( );
						for( auto &entry : addressEntries ) {
							QHostAddress address = entry.ip( );
							if( address.protocol( ) == QAbstractSocket::IPv6Protocol ) {
								qDebug( ) << "Interface:" << interface.name( ) << "IPv6 Address:" << address.toString( );
							} else if( address.protocol( ) == QAbstractSocket::IPv4Protocol ) {
								qDebug( ) << "Interface:" << interface.name( ) << "IPv4 Address:" << address.toString( );
							}
						}
					}
				}
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
