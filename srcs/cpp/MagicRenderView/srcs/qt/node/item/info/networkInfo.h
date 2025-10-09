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
	Def_Last_Mate_Node_Type( Node_Item_Type::Process );
};

#endif // NETWORKINFO_H_H_HEAD__FILE__
