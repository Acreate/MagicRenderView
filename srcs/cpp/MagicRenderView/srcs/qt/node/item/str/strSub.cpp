#include "./strSub.h"

#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrSub, QObject::tr( "提取" ), QObject::tr( "字符" ) );

StrSub::StrSub( ) : NodeItem( ) {
}
bool StrSub::intPortItems( MainWidget *parent ) {

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
