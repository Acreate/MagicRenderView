#ifndef FOREACHLOGIC_H_H_HEAD__FILE__
#define FOREACHLOGIC_H_H_HEAD__FILE__
#pragma once


#include "../nodeItem.h"

class ForeachLogic : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	ForeachLogic( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Foreach; }
};
#endif // FOREACHLOGIC_H_H_HEAD__FILE__
