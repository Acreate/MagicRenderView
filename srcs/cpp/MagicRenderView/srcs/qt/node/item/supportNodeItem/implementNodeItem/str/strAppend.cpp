#include "./strAppend.h"

#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrAppend, QObject::tr( "追加" ), QObject::tr( "字符" ) );

StrAppend::StrAppend( )  {
}
bool StrAppend::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt<StringInputPort>( "拼接字符串" );
			addOutputProt<StringOutputPort>( "结果" );
			return true;
		} );
}
