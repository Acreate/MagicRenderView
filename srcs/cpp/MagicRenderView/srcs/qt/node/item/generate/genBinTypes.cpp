#include "genBinTypes.h"

#include <QScrollArea>

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/generateListWidget/GenerateListWidget.h"
#include "../../../widgets/generateListWidget/generateListScrollArea.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/bin/binOutputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
Imp_StaticMetaInfo( GenBinTypes, QObject::tr( "二进制" ), QObject::tr( "生成" ) );

void GenBinTypes::changeVarOverSignal( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
}
GenBinTypes::GenBinTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {
	generateBinWidget = new GenerateListWidget( nodeInfoScrollArea );
	generateBinWidget->setVarCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateBinWidget->setNameCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateBinWidget->setVarGenerateFunction( [] {
		using t_current_type = uint8_t;
		auto type = new I_Type( typeid( t_current_type ), sizeof( t_current_type ), [] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		}, [] {
			return new t_current_type( 0 );
		} );
		auto var = new I_Var( type );
		return std_shared_ptr< I_Var >( var );
	} );

	connect( generateBinWidget, &GenerateListWidget::changeVarOverSignal, this, &GenBinTypes::changeVarOverSignal );
}
bool GenBinTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< BinOutputPort >( "列表" );
			return true;
		} );
}
