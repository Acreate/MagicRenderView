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
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Logic; }
};
#endif // IFLOGIC_H_H_HEAD__FILE__
