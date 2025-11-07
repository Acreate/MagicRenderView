#ifndef ENDNODE_H_H_HEAD__FILE__
#define ENDNODE_H_H_HEAD__FILE__
#pragma once
#include "../../endNodeItem.h"

class EndNode : public EndNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	EndNode( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // ENDNODE_H_H_HEAD__FILE__
