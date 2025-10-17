#include "./readImage.h"

#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/color/imagaRGBAColorOutPutPort.h"
#include "../../prot/outputProt/impOutputPort/int/intOutputPort.h"

Imp_StaticMetaInfo( ReadImage, QObject::tr( "读图像" ), QObject::tr( "磁盘" ) );

ReadImage::ReadImage( ) : NodeItem( ) {
}
bool ReadImage::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {

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
			return true;
		} );
}
