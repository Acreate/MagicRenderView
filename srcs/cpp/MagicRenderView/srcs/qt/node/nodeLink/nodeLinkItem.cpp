#include "./nodeLinkItem.h"

#include "qt/node/nodeComponent/INodeComponent.h"
#include "qt/node/nodeWidget/INodeWidget.h"

inline bool link( std_pairt< INodeWidget *, INodeComponent * > &left, std_pairt< INodeWidget *, INodeComponent * > &right, INodeWidget *node_widget, INodeComponent *node_component ) {
	if( right.first == node_widget /* 自己连接自己 */ )
		return false;
	if( right.first == nullptr )
		return true;
	if( right.second->tryLetChangeVar( node_component ) )
		return true;
	return false;
}

bool NodeLinkItem::setInput( INodeWidget *input_node_widget, INodeComponent *input_node_component ) {
	if( link( input_node_component_info, output_node_component_info, input_node_widget, input_node_component ) == false )
		return false;
	input_node_component_info.first = input_node_widget;
	input_node_component_info.second = input_node_component;
	return true; // 成功返回 true
}
bool NodeLinkItem::setOutput( INodeWidget *output_node_widget, INodeComponent *output_node_component ) {
	if( link( output_node_component_info, input_node_component_info, output_node_widget, output_node_component ) == false )
		return false;
	output_node_component_info.first = output_node_widget;
	output_node_component_info.second = output_node_component;
	return true; // 成功返回 true
}
bool NodeLinkItem::getInputOutputPos( QPoint *result_input_component_pos, QPoint *result_output_component_pos ) const {
	if( input_node_component_info.first == nullptr || input_node_component_info.second == nullptr || output_node_component_info.first == nullptr || output_node_component_info.second == nullptr )
		return false;

	if( input_node_component_info.first->getComponentLinkPos( input_node_component_info.second, *result_input_component_pos ) == false || output_node_component_info.first->getComponentLinkPos( output_node_component_info.second, *result_output_component_pos ) == false )
		return false;

	return true;
}
