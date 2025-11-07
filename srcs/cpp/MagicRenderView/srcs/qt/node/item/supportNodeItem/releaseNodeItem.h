#ifndef RELEASENODEITEM_H_H_HEAD__FILE__
#define RELEASENODEITEM_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class ReleaseNodeItem : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	ReleaseNodeItem( ) { }
	ReleaseNodeItem( GenerateListScrollArea *node_info_scroll_area ) : NodeItem( node_info_scroll_area ) { }
public:
	Def_Last_Mate_Node_Type( ReleaseVar );
};
#endif // RELEASENODEITEM_H_H_HEAD__FILE__
