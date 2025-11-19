#include "genFloatTypes.h"

#include <QScrollArea>

#include "../../../../../generate/varGenerate.h"

#include "../../../../../varType/I_Type.h"
#include "../../../../../varType/I_Var.h"

#include "../../../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../../../widgets/generateListWidget/generateListWidget.h"
#include "../../../../../widgets/generateListWidget/varEditorWidget.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/float/floatOutputPort.h"

Imp_StaticMetaInfo( GenFloatTypes, QObject::tr( "浮点" ), QObject::tr( "生成" ) );

using t_current_type = double;
void GenFloatTypes::changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
}
void GenFloatTypes::delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
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
GenFloatTypes::GenFloatTypes( ) : GenerateVarNodeItem( new GenerateListScrollArea( ) ) {
	nodeTypeInfo = std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) );
	generateFloatWidget = new GenerateListWidget( generateListScrollArea );
	generateFloatWidget->setNormalVarFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string, const QString &title, I_Var *result_normal_var ) {
		result_normal_var->setVarName( title );
		auto typeInfo = result_normal_var->getTypeInfo( );
		auto &info = typeInfo->getTypeInfo( );
		return varGenerate->conver( info, result_normal_var->getVarPtr( ), typeid( QString ), &string );
		return true;
	} );
	generateFloatWidget->setVarCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		bool result = false;
		string.toDouble( &result );
		if( result == false )
			var_editor_widget->setValueEditorMsg( tr( "值无法转换到浮点" ) );
		return result;
	} );
	generateFloatWidget->setNameCheckFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string ) {
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
	generateFloatWidget->setVarGenerateFunction( [this] {
		std_shared_ptr< I_Var > ptr( I_Var::generateVarPtr< t_current_type >( ) );
		nodeVarVector.emplace_back( ptr );
		return ptr;
	} );
	connect( generateFloatWidget, &GenerateListWidget::changeVarOverSignal, this, &GenFloatTypes::changeVarOver );
	connect( generateFloatWidget, &GenerateListWidget::delVarOverSignal, this, &GenFloatTypes::delVarOver );
}
bool GenFloatTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意", true );
			addOutputProt< FloatOutputPort >( "列表" );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
