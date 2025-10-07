#include "./readFile.h"

#include "../../../widgets/nodeItemInfoScrollAreaWidget.h"

#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/bin/binOutputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( ReadFile, QObject::tr( "ReadFile" ), QObject::tr( "disk" ) );
ReadFile::ReadFile( ) : NodeItem( ) {

}
bool ReadFile::intPortItems( MainWidget *parent ) {
	if( NodeItem::intPortItems( parent ) == false )
		return false;
	// 初始化节点名称
	setNodeTitleName( getMetaObjectName( ) );
	// 初始化输入端口
	addInputProt< StringInputPort >( "文件路径" );
	// 初始化输出端口
	addOutputProt< BinOutputPort >( "二进制" );
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
