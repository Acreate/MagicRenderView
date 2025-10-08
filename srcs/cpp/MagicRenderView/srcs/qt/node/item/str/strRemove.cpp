#include "./strRemove.h"

#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrRemove, QObject::tr( "StrRemove" ), QObject::tr( "str" ) );

StrRemove::StrRemove( )
	: NodeItem( ) {
}
bool StrRemove::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< StringInputPort >( "原始字符串" );
			addInputProt< StringInputPort >( "删除字符串" );
			
			addOutputProt<StringOutputPort>( "结果" );
			return true;
		} );
}
