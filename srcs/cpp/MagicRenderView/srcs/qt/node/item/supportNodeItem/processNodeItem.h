#ifndef PROCESSNODEITEM_H_H_HEAD__FILE__
#define PROCESSNODEITEM_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class ProcessNodeItem : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	ProcessNodeItem( ) { }
	ProcessNodeItem( GenerateListScrollArea *node_info_scroll_area ) : NodeItem( node_info_scroll_area ) { }
public:
	Def_Last_Mate_Node_Type( Process );
};
#endif // PROCESSNODEITEM_H_H_HEAD__FILE__
