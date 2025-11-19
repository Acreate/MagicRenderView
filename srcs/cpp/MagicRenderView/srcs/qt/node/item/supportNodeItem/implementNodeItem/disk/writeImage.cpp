#include "./writeImage.h"

#include "../../../../prot/inputProt/inpInputPort/image/qImageInputPort.h"
#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( WriteImage, QObject::tr( "写图像" ), QObject::tr( "磁盘" ) );

WriteImage::WriteImage( ) {
}
bool WriteImage::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< StringInputPort >( "文件路径", false );
			addInputProt< QImageInputPort >( "图像", false );
			addOutputProt< AnyOutputPort >( "下一步" );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
