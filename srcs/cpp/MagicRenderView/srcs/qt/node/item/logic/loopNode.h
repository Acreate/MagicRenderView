#ifndef LOOPNODE_H_H_HEAD__FILE__
#define LOOPNODE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class LoopNode : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	LoopNode( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Loop );
};
#endif // LOOPNODE_H_H_HEAD__FILE__
