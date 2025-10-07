#include "./readImage.h"

#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/color/imagaRGBAColorOutPutPort.h"
#include "../../prot/outputProt/impOutputPort/int/intOutputPort.h"

Imp_StaticMetaInfo( ReadImage, QObject::tr( "ReadImage" ), QObject::tr( "disk" ) );

ReadImage::ReadImage( ) : NodeItem( ) {
}
bool ReadImage::intPortItems( MainWidget *parent ) {
	if( NodeItem::intPortItems( parent ) == false )
		return false;

	// 初始化节点名称
	setNodeTitleName( getMetaObjectName( ) );
	// 初始化输入端口
	addInputProt< StringInputPort >( "文件路径" );
	// 初始化输出端口
	addOutputProt< ImagaRGBAColorOutPutPort >( "红绿蓝透" );
	addOutputProt< IntOutputPort >( "红" );
	addOutputProt< IntOutputPort >( "绿" );
	addOutputProt< IntOutputPort >( "蓝" );
	addOutputProt< IntOutputPort >( "透" );
	addOutputProt< IntOutputPort >( "宽" );
	addOutputProt< IntOutputPort >( "高" );
	// 更新标题渲染布局
	updateTitleLayout( );
	// 更新输入渲染布局
	updateInputLayout( );
	// 更新输出渲染布局
	updateOutputLayout( );
	// 更新整体渲染布局
	integrateLayout( );
	return true;
}
