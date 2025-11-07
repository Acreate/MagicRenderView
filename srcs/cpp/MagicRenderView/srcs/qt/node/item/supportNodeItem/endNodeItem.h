#ifndef ENDNODEITEM_H_H_HEAD__FILE__
#define ENDNODEITEM_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class EndNodeItem : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	EndNodeItem( ) { }
	EndNodeItem( GenerateListScrollArea *node_info_scroll_area ) : NodeItem( node_info_scroll_area ) { }
public:
	Def_Last_Mate_Node_Type( End );
};
#endif // ENDNODEITEM_H_H_HEAD__FILE__
