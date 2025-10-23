#include "./writeImage.h"

#include "../../prot/inputProt/inpInputPort/bin/binInputPort.h"
#include "../../prot/inputProt/inpInputPort/color/qColorInputPort.h"
#include "../../prot/inputProt/inpInputPort/image/qImageInputPort.h"
#include "../../prot/inputProt/inpInputPort/int/uIntInputPort.h"
#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"
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
			addInputProt< QImageInputPort >( "图像" );
			addOutputProt< AnyOutputPort >( "下一步" );
			return true;
		} );
}
