#include "genFloatTypes.h"

#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
Imp_StaticMetaInfo( GenFloatTypes, QObject::tr( "GenFloatTypes" ), QObject::tr( "generate" ) );

GenFloatTypes::GenFloatTypes( ) : NodeItem( ) {
}
bool GenFloatTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addOutputProt< FloatOutputPort >( "列表" );
			return true;
		} );
}
