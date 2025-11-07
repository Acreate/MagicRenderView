#include "./strSplit.h"

#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrSplit, QObject::tr( "切分" ), QObject::tr( "字符" ) );

StrSplit::StrSplit( ) {
}
bool StrSplit::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< StringInputPort >( "原始字符串", false );
			addInputProt< StringInputPort >( "切分字符串", false );

			addOutputProt< StringOutputPort >( "结果" );
			return true;
		} );
}
