#ifndef JUMPNODEITEM_H_H_HEAD__FILE__
#define JUMPNODEITEM_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class JumpNodeItem : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	JumpNodeItem( ) { }
	JumpNodeItem( GenerateListScrollArea *node_info_scroll_area ) : NodeItem( node_info_scroll_area ) { }
public:
	Def_Last_Mate_Node_Type( Jump );
};
#endif // JUMPNODEITEM_H_H_HEAD__FILE__
