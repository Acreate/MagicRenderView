#ifndef NODERUNPOINTTYPEQUEUEDATA_H_H_HEAD__FILE__
#define NODERUNPOINTTYPEQUEUEDATA_H_H_HEAD__FILE__
#include "../../nodeRunTypeQueueData.h"

class NodeRunPointTypeQueueData : public NodeRunTypeQueueData {
	Q_OBJECT;
public:
	NodeRunPointTypeQueueData( );
	bool appendNode( Node *append_node_ptr ) override;
	bool removeNode( const Node *remove_node_ptr ) override;
	const std::vector< Node * > & getNodeQueue( ) const override;
	NodeEnum::NodeType getType( ) const override;
};

#endif // NODERUNPOINTTYPEQUEUEDATA_H_H_HEAD__FILE__
