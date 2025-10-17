#include "./writeImage.h"

#include "../../prot/inputProt/inpInputPort/bin/binInputPort.h"
#include "../../prot/inputProt/inpInputPort/color/imagaRGBAColorInPutPort.h"
#include "../../prot/inputProt/inpInputPort/int/uIntInputPort.h"
#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"

Imp_StaticMetaInfo( WriteImage, QObject::tr( "写图像" ), QObject::tr( "磁盘" ) );

WriteImage::WriteImage( )
	: NodeItem( ) {
}
bool WriteImage::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< StringInputPort >( "文件路径" );
			addInputProt< ImagaRGBAColorInPutPort >( "rgba" );
			addInputProt< UIntInputPort >( "红" );
			addInputProt< UIntInputPort >( "绿" );
			addInputProt< UIntInputPort >( "蓝" );
			addInputProt< UIntInputPort >( "透" );
			addInputProt< UIntInputPort >( "宽" );
			addInputProt< UIntInputPort >( "高" );
			return true;
		} );
}
