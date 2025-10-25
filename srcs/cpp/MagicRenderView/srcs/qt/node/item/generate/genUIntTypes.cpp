#include "genUIntTypes.h"

#include <QScrollArea>

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../widgets/generateListWidget/generateListWidget.h"

#include "../../nodeInfoWidget/generateUIntNodeInfoWidget/generateUintWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
Imp_StaticMetaInfo( GenUIntTypes, QObject::tr( "无符号" ), QObject::tr( "生成" ) );

GenUIntTypes::GenUIntTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {
	generateUintWidget = new GenerateListWidget( nodeInfoScrollArea );
	generateUintWidget->setVarCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateUintWidget->setNameCheckFunction( [] ( VarEditorWidget *var_editor_widget, const QString &string ) {
		return true;
	} );
	generateUintWidget->setVarGenerateFunction( [] {
		using t_current_type = uint64_t;
		auto type = new I_Type( typeid( t_current_type ), sizeof( t_current_type ), [] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		}, [] {
			return new t_current_type( 0 );
		} );
		auto var = new I_Var( type );
		return std_shared_ptr< I_Var >( var );
	} );
}
bool GenUIntTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< UIntOutputPort >( "列表" );
			return true;
		} );
}
