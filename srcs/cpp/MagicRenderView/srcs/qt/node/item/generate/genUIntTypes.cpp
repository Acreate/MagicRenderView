#include "genUIntTypes.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
Imp_StaticMetaInfo( GenUIntTypes, QObject::tr( "GenUIntTypes" ), QObject::tr( "generate" ) );

GenUIntTypes::GenUIntTypes( ) : NodeItem( ) {
}
bool GenUIntTypes::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "运行机制" );
			addOutputProt< UIntOutputPort >( "列表" );
			return true;
		} );
}
