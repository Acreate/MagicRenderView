#ifndef TIMEDATACONVER_H_H_HEAD__FILE__
#define TIMEDATACONVER_H_H_HEAD__FILE__
#pragma once


#include "../nodeItem.h"

class TimeDataConver : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	TimeDataConver( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Node_Item_Type::Process );
};
#endif // TIMEDATACONVER_H_H_HEAD__FILE__
