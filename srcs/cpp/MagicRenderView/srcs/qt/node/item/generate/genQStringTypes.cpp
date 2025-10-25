#include "genQStringTypes.h"

#include <QScrollArea>

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../widgets/generateListWidget/generateListWidget.h"
#include "../../../widgets/generateListWidget/varEditorWidget.h"

#include "../../nodeInfoWidget/generateQStringNodeInfoWidget/generateQStringWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"
Imp_StaticMetaInfo( GenQStringTypes, QObject::tr( "字符" ), QObject::tr( "生成" ) );


void GenQStringTypes::changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
}
void GenQStringTypes::delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
	size_t count = nodeVarVector.size( );
	if( count == 0 )
		return;
	auto var = change_var_obj_ptr->getEditorVar( ).get( );
	auto data = nodeVarVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == var ) {
			auto begin = nodeVarVector.begin( );
			nodeVarVector.erase( begin );
			return;
		}
}
GenQStringTypes::GenQStringTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {
	generateQStringWidget = new GenerateListWidget( nodeInfoScrollArea );
	generateQStringWidget->setVarCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateQStringWidget->setNameCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateQStringWidget->setVarGenerateFunction( [] {
		using t_current_type = QString;
		return std_shared_ptr< I_Var >( I_Var::generateVarPtr< t_current_type >( ) );
	} );
	connect( generateQStringWidget, &GenerateListWidget::changeVarOverSignal, this, &GenQStringTypes::changeVarOver );
	connect( generateQStringWidget, &GenerateListWidget::delVarOverSignal, this, &GenQStringTypes::delVarOver );
}
bool GenQStringTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< StringOutputPort >( "列表" );
			return true;
		} );
}
