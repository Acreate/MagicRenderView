#ifndef ENDNODE_H_H_HEAD__FILE__
#define ENDNODE_H_H_HEAD__FILE__
#pragma once


#include "../nodeItem.h"

class EndNode : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	EndNode( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Node_Item_Type::End );
};
#endif // ENDNODE_H_H_HEAD__FILE__
