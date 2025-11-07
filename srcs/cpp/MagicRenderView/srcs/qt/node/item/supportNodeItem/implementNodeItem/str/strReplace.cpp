#include "./strReplace.h"

#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrReplace, QObject::tr( "替换" ), QObject::tr( "字符" ) );

StrReplace::StrReplace( ){
}
bool StrReplace::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< StringInputPort >( "原始字符串" );
			addInputProt< StringInputPort >( "匹配目标字符串" );
			addInputProt< StringInputPort >( "替换目标字符串" );
			
			addOutputProt<StringOutputPort>( "结果" );
			return true;
		} );
}
