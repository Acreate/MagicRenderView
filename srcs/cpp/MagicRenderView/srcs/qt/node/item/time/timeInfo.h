#ifndef TIMEINFO_H_H_HEAD__FILE__
#define TIMEINFO_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class TimeInfo : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	TimeInfo( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Node_Item_Type::Process );
};
#endif // TIMEINFO_H_H_HEAD__FILE__
