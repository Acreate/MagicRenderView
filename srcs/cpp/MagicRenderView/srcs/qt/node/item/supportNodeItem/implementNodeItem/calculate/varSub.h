#ifndef VARSUB_H_H_HEAD__FILE__
#define VARSUB_H_H_HEAD__FILE__
#pragma once


#include "../../processNodeItem.h"

class VarSub : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarSub( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Process );
};
#endif // VARSUB_H_H_HEAD__FILE__
