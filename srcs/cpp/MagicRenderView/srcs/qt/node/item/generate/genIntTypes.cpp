#include "genIntTypes.h"

#include "../../prot/outputProt/impOutputPort/int/intOutputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
Imp_StaticMetaInfo( GenIntTypes, QObject::tr( "GenIntTypes" ), QObject::tr( "generate" ) );

GenIntTypes::GenIntTypes( ) : NodeItem( ) {
}
bool GenIntTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addOutputProt< IntOutputPort >( "列表" );
			return true;
		} );
}
