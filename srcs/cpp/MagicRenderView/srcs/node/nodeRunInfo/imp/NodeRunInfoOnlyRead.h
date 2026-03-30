#ifndef NODERUNINFOONLYREAD_H_H_HEAD__FILE__
#define NODERUNINFOONLYREAD_H_H_HEAD__FILE__

#include "../nodeRunInfo.h"
#include "../nodeRunInfoData.h"

class NodeRunInfoOnlyRead : public NodeRunInfo {
	Q_OBJECT;
public:
	NodeRunInfoData * getNodeRunInfoData( ) const override;
	NodeRunInfoDataEditor * getNodeRunInfoDataEditor( ) const override;
	NodeRunInfoDataOnlyRead * getNodeRunInfoDataOnlyRead( ) const override;
	NodeRunInfoDataEditor * getNodeRunInfoDataEditorImage( ) const override;
	NodeRunInfoData * getNodeRunInfoDataImage( ) const override;
	NodeRunInfoDataOnlyRead * getNodeRunInfoDataOnlyReadImage( ) const override;
	bool hasBuilderNode( const Node *check_node_ptr ) override;
};

#endif // NODERUNINFOONLYREAD_H_H_HEAD__FILE__
