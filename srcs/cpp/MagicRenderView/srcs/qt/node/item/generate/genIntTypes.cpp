#include "genIntTypes.h"

#include <QScrollArea>

#include "../../../generate/varGenerate.h"

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../widgets/generateListWidget/generateListWidget.h"
#include "../../../widgets/generateListWidget/varEditorWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/intOutputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
Imp_StaticMetaInfo( GenIntTypes, QObject::tr( "整数" ), QObject::tr( "生成" ) );

void GenIntTypes::changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
}
void GenIntTypes::delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
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
GenIntTypes::GenIntTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {
	generateIntWidget = new GenerateListWidget( generateListScrollArea );
	generateIntWidget->setNormalVarFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string, I_Var *result_normal_var ) {

		auto typeInfo = result_normal_var->getTypeInfo( );
		auto &info = typeInfo->getTypeInfo( );
		return varGenerate->conver( info, result_normal_var->getVarPtr( ), typeid( QString ), &string );
	} );
	generateIntWidget->setVarCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {

		bool result = false;
		string.toDouble( &result );
		if( result == false )
			var_editor_widget->setValueEditorMsg( tr( "值无法转换到整数" ) );
		return result;
	} );
	generateIntWidget->setNameCheckFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		size_t count = nodeVarVector.size( );
		if( count == 0 )
			return false;
		auto data = nodeVarVector.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ]->getVarName( ) == string ) {
				var_editor_widget->setNameEditorMsg( tr( "存在同名变量" ) );
				return false;
			}
		return true;
	} );
	generateIntWidget->setVarGenerateFunction( [this] {
		using t_current_type = int64_t;
		std_shared_ptr< I_Var > ptr( I_Var::generateVarPtr< t_current_type >( ) );
		nodeVarVector.emplace_back( ptr );
		return ptr;
	} );

	connect( generateIntWidget, &GenerateListWidget::changeVarOverSignal, this, &GenIntTypes::changeVarOver );
	connect( generateIntWidget, &GenerateListWidget::delVarOverSignal, this, &GenIntTypes::delVarOver );
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
