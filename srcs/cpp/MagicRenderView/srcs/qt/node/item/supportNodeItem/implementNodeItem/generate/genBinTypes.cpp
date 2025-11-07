#include "genBinTypes.h"

#include <QScrollArea>

#include "../../../../../generate/varGenerate.h"

#include "../../../../../varType/I_Type.h"
#include "../../../../../varType/I_Var.h"

#include "../../../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../../../widgets/generateListWidget/generateListWidget.h"
#include "../../../../../widgets/generateListWidget/varEditorWidget.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/bin/binOutputPort.h"

Imp_StaticMetaInfo( GenBinTypes, QObject::tr( "二进制" ), QObject::tr( "生成" ) );

void GenBinTypes::changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
}
void GenBinTypes::delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
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
GenBinTypes::GenBinTypes( ) : GenerateVarNodeItem( new GenerateListScrollArea( ) ) {
	generateBinWidget = new GenerateListWidget( generateListScrollArea );
	generateBinWidget->setNormalVarFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string, const QString &title, I_Var *result_normal_var ) {
		result_normal_var->setVarName( title );
		bool result = false;
		QString number = QString::number( string.toULongLong( &result, 16 ) );
		if( result == false )
			return false;
		auto typeInfo = result_normal_var->getTypeInfo( );
		auto &info = typeInfo->getTypeInfo( );
		return varGenerate->conver( info, result_normal_var->getVarPtr( ), typeid( QString ), &number );
	} );
	generateBinWidget->setVarCheckFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		qsizetype length = string.length( );
		if( length == 0 )
			return true;
		if( length < 3 ) {
			auto data = string.data( );
			QChar upper;
			for( size_t index = 0; index < length; ++index )
				if( upper = data[ index ].toUpper( ), upper < '0' || upper > 'F' || ( upper > '9' && upper < 'A' ) )
					return false;
		} else {
			var_editor_widget->setValueEditorMsg( tr( "值无法转换到二进制（00 ~ FF）" ) );
			return false;
		}
		return true;
	} );
	generateBinWidget->setNameCheckFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string ) {
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
	generateBinWidget->setVarGenerateFunction( [this] {
		using t_current_type = uint8_t;
		std_shared_ptr< I_Var > ptr( I_Var::generateVarPtr< t_current_type >( ) );
		nodeVarVector.emplace_back( ptr );
		return ptr;
	} );

	connect( generateBinWidget, &GenerateListWidget::changeVarOverSignal, this, &GenBinTypes::changeVarOver );
	connect( generateBinWidget, &GenerateListWidget::delVarOverSignal, this, &GenBinTypes::delVarOver );
}
bool GenBinTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意", true );
			addOutputProt< BinOutputPort >( "列表" );
			return true;
		} );
}
