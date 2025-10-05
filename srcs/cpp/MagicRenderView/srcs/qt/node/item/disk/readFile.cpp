#include "./readFile.h"

#include <qt/node/prot/inputProt/inpInputPort/stringInputPort.h>
#include <qt/node/prot/outputProt/impOutputPort/stringOutputPort.h>

#include "../../../widgets/nodeItemInfoScrollAreaWidget.h"

Imp_StaticMetaInfo( ReadFile, QObject::tr( "ReadFile" ), QObject::tr( "disk" ) );
ReadFile::ReadFile( ) : NodeItem( ) {

}
bool ReadFile::intPortItems( MainWidget *parent ) {
	if( NodeItem::intPortItems( parent ) == false )
		return false;
	// 初始化节点名称
	setNodeTitleName( getMetaObjectName( ) );
	// 初始化输入端口
	StringInputPort *inputPort = new StringInputPort( this );
	inputPort->setTitle( "文件路径" );
	appendInputProt( inputPort );
	// 初始化输出端口
	StringOutputPort *outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件全路径" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件所在目录" );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件创建日期" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件更改日期" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件拥有者" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件基本全名称" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件基本名称" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件后缀名" );
	appendOutputProt( outputPort );
	// 更新标题渲染布局
	updateTitleLayout( );
	// 更新输入渲染布局
	updateInputLayout( );
	// 更新输出渲染布局
	updateOutputLayout( );
	// 更新整体渲染布局
	integrateLayout( );

	// 返回
	return true;
}
