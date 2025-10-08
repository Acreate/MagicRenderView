#ifndef WRITEFILE_H_H_HEAD__FILE__
#define WRITEFILE_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class WriteFile : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	WriteFile(  );
public:
	bool intPortItems( MainWidget *parent ) override;
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Loop; }
};

#endif // WRITEFILE_H_H_HEAD__FILE__
