#include "genIntTypes.h"

#include <QScrollArea>

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../widgets/generateListWidget/generateListWidget.h"

#include "../../nodeInfoWidget/generateIntNodeInfoWidget/generateIntWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/intOutputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
Imp_StaticMetaInfo( GenIntTypes, QObject::tr( "整数" ), QObject::tr( "生成" ) );

void GenIntTypes::changeVarOverSignal( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
}
GenIntTypes::GenIntTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {
	generateIntWidget = new GenerateListWidget( nodeInfoScrollArea );
	generateIntWidget->setVarCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateIntWidget->setNameCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateIntWidget->setVarGenerateFunction( [] {
		using t_current_type = int64_t;
		auto type = new I_Type( typeid( t_current_type ), sizeof( t_current_type ), [] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		}, [] {
			return new t_current_type( 0 );
		} );
		auto var = new I_Var( type );
		return std_shared_ptr< I_Var >( var );
	} );
	connect( generateIntWidget, &GenerateListWidget::changeVarOverSignal, this, &GenIntTypes::changeVarOverSignal );
}
bool GenIntTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< IntOutputPort >( "列表" );
			return true;
		} );
}
