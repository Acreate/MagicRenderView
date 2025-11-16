#ifndef GENERATEVARNODEITEM_H_H_HEAD__FILE__
#define GENERATEVARNODEITEM_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class GenerateVarNodeItem : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateVarNodeItem( ) { }
	GenerateVarNodeItem( GenerateListScrollArea *node_info_scroll_area ) : NodeItem( node_info_scroll_area ) { }
public:
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENERATEVARNODEITEM_H_H_HEAD__FILE__
