#include "genBinTypes.h"

#include <QScrollArea>

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/generateListWidget/GenerateListWidget.h"
#include "../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../widgets/generateListWidget/varEditorWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/bin/binOutputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
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
		if( data[ index ].get(  ) == var ) {
			auto begin = nodeVarVector.begin( );
			nodeVarVector.erase( begin );
			return;
		}
}
GenBinTypes::GenBinTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {
	generateBinWidget = new GenerateListWidget( nodeInfoScrollArea );
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
		} /*else if( length < 5 ) {
			auto data = string.data( );
			if( data[ 0 ] != '0' )
				return false;
			QChar upper = data[ 1 ].toUpper( );
			if( upper != 'X' )
				return false;
			for( size_t index = 2; index < length; ++index )
				if( upper = data[ index ].toUpper( ), upper < '0' || upper > 'F' || ( upper > '9' && upper < 'A' ) )
					return false;
		} */else
			return false;
		return true;
	} );
	generateBinWidget->setNameCheckFunction( [this] ( VarEditorWidget *var_editor_widget, const QString &string ) {
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
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< BinOutputPort >( "列表" );
			return true;
		} );
}
