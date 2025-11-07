#ifndef VARMUL_H_H_HEAD__FILE__
#define VARMUL_H_H_HEAD__FILE__
#pragma once


#include "../../processNodeItem.h"

class VarMul : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarMul( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Process );
};
#endif // VARMUL_H_H_HEAD__FILE__
