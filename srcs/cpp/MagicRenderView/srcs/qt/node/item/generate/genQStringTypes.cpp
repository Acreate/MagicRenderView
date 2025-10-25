#include "genQStringTypes.h"

#include <QScrollArea>

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../widgets/generateListWidget/generateListWidget.h"

#include "../../nodeInfoWidget/generateQStringNodeInfoWidget/generateQStringWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"
Imp_StaticMetaInfo( GenQStringTypes, QObject::tr( "字符" ), QObject::tr( "生成" ) );

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
		auto type = new I_Type( typeid( t_current_type ), sizeof( t_current_type ), [] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		}, [] {
			return new t_current_type( );
		} );
		auto var = new I_Var( type );
		return std_shared_ptr< I_Var >( var );
	} );
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
