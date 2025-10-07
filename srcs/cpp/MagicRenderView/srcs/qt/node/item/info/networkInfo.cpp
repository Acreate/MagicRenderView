#include "networkInfo.h"

#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"
Imp_StaticMetaInfo( NetworkInfo, QObject::tr( "NetworkInfo" ), QObject::tr( "info" ) );

NetworkInfo::NetworkInfo( ) {
}
bool NetworkInfo::intPortItems( MainWidget *parent ) {
	if( NodeItem::intPortItems( parent ) == false )
		return false;
	// 初始化节点名称
	setNodeTitleName( getMetaObjectName( ) );
	// 初始化输入端口
	/*StringInputPort *inputPort = new StringInputPort( this );
	inputPort->setTitle( "文件路径" );
	appendInputProt( inputPort );*/
	// 初始化输出端口
	addOutputProt< StringOutputPort >( "ipv4" );
	addOutputProt< StringOutputPort >( "ipv6" );
	addOutputProt< StringOutputPort >( "域名" );

	// 更新标题渲染布局
	updateTitleLayout( );
	// 更新输入渲染布局
	//updateInputLayout( );
	// 更新输出渲染布局
	updateOutputLayout( );
	// 更新整体渲染布局
	integrateLayout( );

	// 返回
	return true;
}
