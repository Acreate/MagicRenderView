#include "./writeFile.h"

#include "../../prot/inputProt/inpInputPort/bin/binInputPort.h"
#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"

Imp_StaticMetaInfo( WriteFile, QObject::tr( "WriteFile" ), QObject::tr( "disk" ) );
WriteFile::WriteFile( ) : NodeItem( ) {
}
bool WriteFile::intPortItems( MainWidget *parent ) {
	if( NodeItem::intPortItems( parent ) == false )
		return false;

	// 初始化节点名称
	setNodeTitleName( getMetaObjectName( ) );
	// 初始化输入端口
	addInputProt< StringInputPort >( "文件路径" );
	addInputProt< BinInputPort >( "二进制" );
	// 更新标题渲染布局
	updateTitleLayout( );
	// 更新输入渲染布局
	updateInputLayout( );
	// 更新输出渲染布局
	//updateOutputLayout( );
	// 更新整体渲染布局
	integrateLayout( );
	return true;
}
