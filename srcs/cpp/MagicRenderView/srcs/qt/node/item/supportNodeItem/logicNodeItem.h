#ifndef LOGICNODEITEM_H_H_HEAD__FILE__
#define LOGICNODEITEM_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class LogicNodeItem : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	LogicNodeItem( ) { }
	LogicNodeItem( GenerateListScrollArea *node_info_scroll_area ) : NodeItem( node_info_scroll_area ) { }
public:
	Def_Last_Mate_Node_Type( Logic );
};
#endif // LOGICNODEITEM_H_H_HEAD__FILE__
