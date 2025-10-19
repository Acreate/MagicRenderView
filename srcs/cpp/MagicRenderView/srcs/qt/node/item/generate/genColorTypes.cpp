#include "genColorTypes.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/color/imagaRGBAColorOutPutPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
Imp_StaticMetaInfo( GenColorTypes, QObject::tr( "颜色" ), QObject::tr( "生成" ) );

GenColorTypes::GenColorTypes( ) : NodeItem( ) {
}
bool GenColorTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< ImagaRGBAColorOutPutPort >( "列表" );
			return true;
		} );
}
