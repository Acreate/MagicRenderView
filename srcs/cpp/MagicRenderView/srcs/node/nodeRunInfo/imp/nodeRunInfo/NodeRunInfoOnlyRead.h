#ifndef NODERUNINFOONLYREAD_H_H_HEAD__FILE__
#define NODERUNINFOONLYREAD_H_H_HEAD__FILE__

#include "../../nodeRunInfo.h"

class NodeRunInfoOnlyRead : public NodeRunInfo {
	Q_OBJECT;
public:
	NodeRunInfoData * getNodeRunInfoData( ) const override;
	NodeRunInfoData * getNodeRunInfoDataImage( ) const override;
	bool hasBuilderNode( const Node *check_node_ptr ) override;
};

#endif // NODERUNINFOONLYREAD_H_H_HEAD__FILE__
