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
		if( data[ index ].get( ) == var ) {
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
	generateQStringWidget->setNameCheckFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		size_t count = nodeVarVector.size( );
		if( count == 0 )
			return false;
		auto data = nodeVarVector.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ]->getVarName( ) == string ) {
				var_editor_widget->setNameEditorMsg( "存在同名变量" );
				return false;
			}
		return true;
	} );
	generateQStringWidget->setVarGenerateFunction( [this] {
		using t_current_type = QString;
		std_shared_ptr< I_Var > ptr( I_Var::generateVarPtr< t_current_type >( ) );
		nodeVarVector.emplace_back( ptr );
		return ptr;
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
