#ifndef POINTLOGIC_H_H_HEAD__FILE__
#define POINTLOGIC_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class PointLogic : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	PointLogic( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Point );
};
#endif // POINTLOGIC_H_H_HEAD__FILE__
