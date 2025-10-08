#include "./varMod.h"

#include "../../prot/inputProt/inpInputPort/float/floatInputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"

Imp_StaticMetaInfo( VarMod, QObject::tr( "VarMod" ), QObject::tr( "calculate" ) );

VarMod::VarMod( ) : NodeItem( ) {
}
bool VarMod::intPortItems( MainWidget *parent ) {

	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
		addInputProt< FloatInputPort >( "被除数" );
		addInputProt< FloatInputPort >( "除数" );
		addOutputProt< FloatOutputPort >( "结果" );
		return true;
	} );

}
