#ifndef NETWORKINFO_H_H_HEAD__FILE__
#define NETWORKINFO_H_H_HEAD__FILE__
#pragma once

#include "../../processNodeItem.h"

class NetworkInfo : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	NetworkInfo( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Process );
};

#endif // NETWORKINFO_H_H_HEAD__FILE__
