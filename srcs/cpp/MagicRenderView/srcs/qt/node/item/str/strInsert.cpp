#include "./strInsert.h"

#include "../../prot/inputProt/inpInputPort/int/uIntInputPort.h"
#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrInsert, QObject::tr( "StrInsert" ), QObject::tr( "str" ) );

StrInsert::StrInsert( )
	: NodeItem( ) {
}
bool StrInsert::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< StringInputPort >( "原始字符串" );
			addInputProt< UIntInputPort >( "插入位置" );
			addInputProt< StringInputPort >( "插入字符串" );
			addOutputProt<StringOutputPort>( "结果" );
			return true;
		} );
}
