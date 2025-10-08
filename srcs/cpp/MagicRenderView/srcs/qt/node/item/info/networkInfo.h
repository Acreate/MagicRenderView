#ifndef NETWORKINFO_H_H_HEAD__FILE__
#define NETWORKINFO_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class NetworkInfo : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	NetworkInfo( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Root; }
};

#endif // NETWORKINFO_H_H_HEAD__FILE__
