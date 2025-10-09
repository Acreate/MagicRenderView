#ifndef VARDIV_H_H_HEAD__FILE__
#define VARDIV_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class VarDiv : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarDiv( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Node_Item_Type::Process );
};
#endif // VARDIV_H_H_HEAD__FILE__
