#include "./nodeRunFunctionSequenceItemWidget.h"
NodeRunFunctionSequenceItemWidget::NodeRunFunctionSequenceItemWidget( NodeRunSequenceWidget *node_run_sequence_widget, const std::shared_ptr< IFunctionDeclaration > &function_declaration ) : QWidget( node_run_sequence_widget ), itemParent( node_run_sequence_widget ) {

}
NodeRunFunctionSequenceItemWidget::~NodeRunFunctionSequenceItemWidget( ) {
	thisObjectDestory( this );
	disconnect( );
}
