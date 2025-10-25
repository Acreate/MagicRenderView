#include "genFloatTypes.h"

#include <QScrollArea>

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../widgets/generateListWidget/generateListWidget.h"

#include "../../nodeInfoWidget/generateFloatNodeInfoWidget/generateFloatWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
Imp_StaticMetaInfo( GenFloatTypes, QObject::tr( "浮点" ), QObject::tr( "生成" ) );

void GenFloatTypes::changeVarOverSignal( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
}
GenFloatTypes::GenFloatTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {
	generateFloatWidget = new GenerateListWidget( nodeInfoScrollArea );
	generateFloatWidget->setVarCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateFloatWidget->setNameCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateFloatWidget->setVarGenerateFunction( [] {
		using t_current_type = double;
		auto type = new I_Type( typeid( t_current_type ), sizeof( t_current_type ), [] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		}, [] {
			return new t_current_type( 0 );
		} );
		auto var = new I_Var( type );
		return std_shared_ptr< I_Var >( var );
	} );
	connect( generateFloatWidget, &GenerateListWidget::changeVarOverSignal, this, &GenFloatTypes::changeVarOverSignal );
}
bool GenFloatTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< FloatOutputPort >( "列表" );
			return true;
		} );
}
