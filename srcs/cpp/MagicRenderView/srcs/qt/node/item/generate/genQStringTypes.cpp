#include "genQStringTypes.h"

#include <QScrollArea>

#include "../../../widgets/generateListWidget/generateListScrollArea.h"

#include "../../nodeInfoWidget/generateQStringNodeInfoWidget/generateQStringWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"
Imp_StaticMetaInfo( GenQStringTypes, QObject::tr( "字符" ), QObject::tr( "生成" ) );

GenQStringTypes::GenQStringTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {

	generateQStringWidget = new GenerateQStringWidget( this );
	nodeInfoScrollArea->setWidget( generateQStringWidget );
}
bool GenQStringTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< StringOutputPort >( "列表" );
			return true;
		} );
}
