#ifndef GENSTRINGTYPES_H_H_HEAD__FILE__
#define GENSTRINGTYPES_H_H_HEAD__FILE__
#pragma once


#include "../nodeItem.h"

class GenStringTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenStringTypes(  );
public:
	bool intPortItems( MainWidget *parent ) override;
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Root; }
};
#endif // GENSTRINGTYPES_H_H_HEAD__FILE__
