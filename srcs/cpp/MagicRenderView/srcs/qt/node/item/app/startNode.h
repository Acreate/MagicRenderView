#ifndef STARTNODE_H_H_HEAD__FILE__
#define STARTNODE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class StartNodeInfoWidget;
class StartNode : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StartNodeInfoWidget *nodeInfoWidget;
protected:
	StartNode( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Begin );
};
#endif // STARTNODE_H_H_HEAD__FILE__
