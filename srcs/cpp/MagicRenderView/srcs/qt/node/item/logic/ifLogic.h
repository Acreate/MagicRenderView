#ifndef IFLOGIC_H_H_HEAD__FILE__
#define IFLOGIC_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class IfLogic : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	IfLogic( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Node_Item_Type::Logic );
};
#endif // IFLOGIC_H_H_HEAD__FILE__
