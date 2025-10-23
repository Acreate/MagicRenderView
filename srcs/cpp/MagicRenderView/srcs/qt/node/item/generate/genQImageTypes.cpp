#include "genQImageTypes.h"

#include <QScrollArea>

#include "../../../widgets/generateListWidget/generateListScrollArea.h"

#include "../../nodeInfoWidget/generateQImageNodeInfoWidget/generateQImageWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"
#include "../../prot/outputProt/impOutputPort/image/qImageOutputPort.h"
Imp_StaticMetaInfo( GenQImageTypes, QObject::tr( "qt图像" ), QObject::tr( "生成" ) );

GenQImageTypes::GenQImageTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {

	generateQImageWidget = new GenerateQImageWidget( this );
	nodeInfoScrollArea->setWidget( generateQImageWidget );
}
bool GenQImageTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< QImageOutputPort >( "列表" );
			return true;
		} );
}
