#include "array.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/inputProt/inpInputPort/int/uIntInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/any/anyOutputPort.h"
#include "../../../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"

Imp_StaticMetaInfo( Array, QObject::tr( "数组" ), QObject::tr( "结构体" ) );
Array::Array( ) {
}
bool Array::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< AnyInputPort >( "索引节点值" );
			addInputProt< UIntInputPort >( "下标" );
			addOutputProt< AnyOutputPort >( "元素值" );
			addOutputProt< UIntOutputPort >( "数据量" );
			return true;
		} );
}
