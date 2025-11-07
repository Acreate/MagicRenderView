#ifndef STARTNODE_H_H_HEAD__FILE__
#define STARTNODE_H_H_HEAD__FILE__
#pragma once


#include "../../beginNodeItem.h"

class StartNodeInfoWidget;
class StartNode : public BeginNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StartNodeInfoWidget *nodeInfoWidget;
protected:
	StartNode( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // STARTNODE_H_H_HEAD__FILE__
