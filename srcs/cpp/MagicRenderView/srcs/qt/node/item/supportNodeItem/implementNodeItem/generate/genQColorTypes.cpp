#include "genQColorTypes.h"

#include <QScrollArea>

#include "../../../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../../../widgets/generateListWidget/varEditorWidget.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/color/qColorOutputPort.h"

Imp_StaticMetaInfo( GenQColorTypes, QObject::tr( "qt颜色" ), QObject::tr( "生成" ) );

void GenQColorTypes::changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
}
void GenQColorTypes::delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
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
GenQColorTypes::GenQColorTypes( ) : GenerateVarNodeItem( new GenerateListScrollArea( ) ) {

}
bool GenQColorTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意", true );
			addOutputProt< QColorOutputPort >( "列表" );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
