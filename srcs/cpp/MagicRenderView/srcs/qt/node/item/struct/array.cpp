#include "array.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( Array, QObject::tr( "Array" ), QObject::tr( "struct" ) );
Array::Array( ) {
}
bool Array::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< AnyInputPort >( "原始字符串" );
			addOutputProt< AnyOutputPort >( "元素值" );
			addOutputProt< UIntOutputPort >( "下标" );
			addOutputProt< UIntOutputPort >( "数据量" );
			return true;
		} );
}
