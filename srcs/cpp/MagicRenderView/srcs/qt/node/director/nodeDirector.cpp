#include "nodeDirector.h"

#include "../widgets/nodeItemInfoScrollAreaWidget.h"
bool NodeDirector::addManagementWidget( NodeItemInfoScrollAreaWidget *add_widget ) {
	size_t count = nodeItemInfoScrollAreaWidgets.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto data = nodeItemInfoScrollAreaWidgets.data( );
		for( ; index < count; ++index )
			if( data[ index ] == nullptr ) {
				data[ index ] = add_widget;
				return true;
			}
	}
	nodeItemInfoScrollAreaWidgets.emplace_back( add_widget );
	connect( add_widget, &QWidget::destroyed, [add_widget, this]( ) {
		removeManagementWidget( add_widget );
	} );
	return true;
}
bool NodeDirector::removeManagementWidget( NodeItemInfoScrollAreaWidget *add_widget ) {
	size_t count = nodeItemInfoScrollAreaWidgets.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto data = nodeItemInfoScrollAreaWidgets.data( );
		for( ; index < count; ++index )
			if( data[ index ] == add_widget ) {
				data[ index ] = nullptr;
				return true;
			}
	}
	return false;
}
NodeDirector::NodeDirector( QObject *parent ) : QObject( parent ) {
}
NodeItemInfoScrollAreaWidget * NodeDirector::requestGetNodeEditorWidget( const type_info &request_type, NodeItem *request_node_item_ptr ) {
	return nullptr;
}
bool NodeDirector::linkInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port ) {
	return false;
}
bool NodeDirector::linkUnInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port ) {
	return false;
}
size_t NodeDirector::run( ) {
	return 0;
}
NodeDirector::~NodeDirector( ) {
	size_t count = nodeItemInfoScrollAreaWidgets.size( );
	size_t index = 0;
	auto data = nodeItemInfoScrollAreaWidgets.data( );
	for( ; index < count; ++index )
		if( data[ index ] != nullptr )
			delete data[ index ];
}
