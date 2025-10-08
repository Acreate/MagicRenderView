#include "./varAdd.h"

#include "../../prot/inputProt/inpInputPort/float/floatInputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"
Imp_StaticMetaInfo( VarAdd, QObject::tr( "VarAdd" ), QObject::tr( "calculate" ) );

VarAdd::VarAdd( ) : NodeItem( ) {
}
bool VarAdd::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< FloatInputPort >( "被加数" );
		addInputProt< FloatInputPort >( "加数" );
		addOutputProt< FloatOutputPort >( "结果" );
		return true;
	} );
}
