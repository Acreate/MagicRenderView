#ifndef BEGINNODEITEM_H_H_HEAD__FILE__
#define BEGINNODEITEM_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class BeginNodeItem : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	BeginNodeItem( ) { }
	BeginNodeItem( GenerateListScrollArea *node_info_scroll_area ) : NodeItem( node_info_scroll_area ) { }
public:
	Def_Last_Mate_Node_Type( Begin );
};
#endif // BEGINNODEITEM_H_H_HEAD__FILE__
