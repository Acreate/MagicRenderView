#ifndef NODERUNINFOEDITOR_H_H_HEAD__FILE__
#define NODERUNINFOEDITOR_H_H_HEAD__FILE__
#include "NodeRunInfoOnlyRead.h"
class NodeRunInfoEditor : public NodeRunInfoOnlyRead {
	Q_OBJECT;
public:
	void setNodeRunInfoDataImage( NodeRunInfoData *new_node_run_info_data_image ) override;
	void setNodeRunInfoData( NodeRunInfoData *new_node_run_info_data ) override;
	void appendBuilderNode( Node **append_node_array_ptr, const size_t &append_node_array_count ) override;
	void appendBuilderNode( Node *append_node_unity ) override;
	bool builderRunInstance( ) override;
	void removeBuilderNode( Node *append_node_unity ) override;
	bool resetRunStartNode( ) override;
	bool toNextFrame( ) override;
	bool runNextNode( ) override;
	bool runResidueNode( ) override;
	bool runStopNode( ) override;
	bool runToNextFrame( ) override;
	bool runToNode( const Node *target ) override;
};

#endif // NODERUNINFOEDITOR_H_H_HEAD__FILE__
