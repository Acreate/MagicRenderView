#include "genQImageTypes.h"

#include <QScrollArea>

#include "../../../widgets/generateListWidget/generateListScrollArea.h"
#include "../../../widgets/generateListWidget/varEditorWidget.h"

#include "../../nodeInfoWidget/generateQImageNodeInfoWidget/generateQImageWidget.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"
#include "../../prot/outputProt/impOutputPort/image/qImageOutputPort.h"
Imp_StaticMetaInfo( GenQImageTypes, QObject::tr( "qt图像" ), QObject::tr( "生成" ) );

void GenQImageTypes::changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
}
void GenQImageTypes::delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
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
GenQImageTypes::GenQImageTypes( ) : NodeItem( new GenerateListScrollArea( ) ) {

	generateQImageWidget = new GenerateQImageWidget( this );
	nodeInfoScrollArea->setWidget( generateQImageWidget );
}
bool GenQImageTypes::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意" );
			addOutputProt< QImageOutputPort >( "列表" );
			return true;
		} );
}
