#include "genStringTypes.h"

#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"
Imp_StaticMetaInfo( GenStringTypes, QObject::tr( "GenStringTypes" ), QObject::tr( "generate" ) );

GenStringTypes::GenStringTypes( ) : NodeItem( ) {
}
bool GenStringTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addOutputProt< StringOutputPort >( "列表" );
			return true;
		} );
}
