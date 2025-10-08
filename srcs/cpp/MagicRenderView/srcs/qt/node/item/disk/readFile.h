#ifndef READFILE_H_H_HEAD__FILE__
#define READFILE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class ReadFile : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	ReadFile( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Process; }
};
#endif // READFILE_H_H_HEAD__FILE__
