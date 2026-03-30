#ifndef NODERUNFUNCTIONTYPEQUEUEDATA_H_H_HEAD__FILE__
#define NODERUNFUNCTIONTYPEQUEUEDATA_H_H_HEAD__FILE__
#include "../../nodeRunTypeQueueData.h"

class NodeRunFunctionTypeQueueData : public NodeRunTypeQueueData {
	Q_OBJECT;
public:
	NodeRunFunctionTypeQueueData( );
	bool appendNode( Node *append_node_ptr ) override;
	bool removeNode( const Node *remove_node_ptr ) override;
	const std::vector< Node * > & getNodeQueue( ) const override;
	NodeEnum::NodeType getType( ) const override;
};

#endif // NODERUNFUNCTIONTYPEQUEUEDATA_H_H_HEAD__FILE__
