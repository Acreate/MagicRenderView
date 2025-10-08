#ifndef GENBINTYPES_H_H_HEAD__FILE__
#define GENBINTYPES_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class GenBinTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenBinTypes(  );
public:
	bool intPortItems( MainWidget *parent ) override;
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Process; }
};
#endif // GENBINTYPES_H_H_HEAD__FILE__
