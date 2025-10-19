#ifndef MARKPOINT_H_H_HEAD__FILE__
#define MARKPOINT_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class MarkPoint : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	MarkPoint( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Mark );
};

#endif // MARKPOINT_H_H_HEAD__FILE__
