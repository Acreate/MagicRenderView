#ifndef NODERUNCREATETYPEQUEUEDATA_H_H_HEAD__FILE__
#define NODERUNCREATETYPEQUEUEDATA_H_H_HEAD__FILE__
#include "../../nodeRunTypeQueueData.h"

class NodeRunCreateTypeQueueData : public NodeRunTypeQueueData {
	Q_OBJECT;
public:
	NodeRunCreateTypeQueueData( );
	bool appendNode( Node *append_node_ptr ) override;
	bool removeNode( const Node *remove_node_ptr ) override;
	const std::vector< Node * > & getNodeQueue( ) const override;
	NodeEnum::NodeType getType( ) const override;
};

#endif // NODERUNCREATETYPEQUEUEDATA_H_H_HEAD__FILE__
