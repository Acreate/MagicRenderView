#include "./nodeRunFunctionSequenceItemWidget.h"

#include <qt/functionDeclaration/IFunctionDeclaration.h>

NodeRunFunctionSequenceItemWidget::NodeRunFunctionSequenceItemWidget( NodeRunSequenceWidget *node_run_sequence_widget, const std::shared_ptr< IFunctionDeclaration > &function_declaration ) : QWidget( node_run_sequence_widget ), itemParent( node_run_sequence_widget ) {
	if( function_declaration.get( )->isIsControlCode( ) == false )
		itemChild = nullptr;
}
NodeRunFunctionSequenceItemWidget::~NodeRunFunctionSequenceItemWidget( ) {
	itemParent->removeItem( this );
	disconnect( );
}
