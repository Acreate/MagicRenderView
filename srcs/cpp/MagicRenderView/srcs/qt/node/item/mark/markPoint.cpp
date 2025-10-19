#include "markPoint.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/inputProt/inpInputPort/bool/boolInputPort.h"
#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( MarkPoint, QObject::tr( "点" ), QObject::tr( "坐标" ) );

MarkPoint::MarkPoint( ) : NodeItem( ) {
}
bool MarkPoint::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< AnyInputPort >( "继续" );
			addOutputProt< AnyOutputPort >( "继续" );
			return true;
		} );
}
