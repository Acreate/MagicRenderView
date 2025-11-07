#ifndef MARKNODEITEM_H_H_HEAD__FILE__
#define MARKNODEITEM_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class MarkNodeItem : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	MarkNodeItem( ) { }
	MarkNodeItem( GenerateListScrollArea *node_info_scroll_area ) : NodeItem( node_info_scroll_area ) { }
public:
	Def_Last_Mate_Node_Type( Mark );
};
#endif // MARKNODEITEM_H_H_HEAD__FILE__
