#include "genQStringTypes.h"

#include <QScrollArea>

#include "../../../../../generate/varGenerate.h"

#include "../../../../../varType/I_Type.h"
#include "../../../../../varType/I_Var.h"

#include "../../../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../../../widgets/generateListWidget/generateListWidget.h"
#include "../../../../../widgets/generateListWidget/varEditorWidget.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( GenQStringTypes, QObject::tr( "字符" ), QObject::tr( "生成" ) );

using t_current_type = QString;
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
GenQStringTypes::GenQStringTypes( ) : GenerateVarNodeItem( new GenerateListScrollArea( ) ) {
	nodeTypeInfo = std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) );
	generateQStringWidget = new GenerateListWidget( generateListScrollArea );
	generateQStringWidget->setNormalVarFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string, const QString &title, I_Var *result_normal_var ) {
		result_normal_var->setVarName( title );
		auto typeInfo = result_normal_var->getTypeInfo( );
		auto &info = typeInfo->getTypeInfo( );
		return varGenerate->conver( info, result_normal_var->getVarPtr( ), typeid( QString ), &string );
	} );
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
				var_editor_widget->setNameEditorMsg( tr( "存在同名变量" ) );
				return false;
			}
		return true;
	} );
	generateQStringWidget->setVarGenerateFunction( [this] {
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
			addInputProt< AnyInputPort >( "任意", true );
			addOutputProt< StringOutputPort >( "列表" );
			return true;
		} );
}
