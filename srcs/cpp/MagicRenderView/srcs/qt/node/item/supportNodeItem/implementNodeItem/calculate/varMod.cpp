#include "./varMod.h"

#include "../../../../prot/inputProt/inpInputPort/float/floatInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/float/floatOutputPort.h"

Imp_StaticMetaInfo( VarMod, QObject::tr( "余" ), QObject::tr( "计算" ) );

VarMod::VarMod( ) {
}
bool VarMod::intPortItems( MainWidget *parent ) {

	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< FloatInputPort >( "被除数", false );
		addInputProt< FloatInputPort >( "除数", false );
		addOutputProt< FloatOutputPort >( "结果" );
		return true;
	} );

}
