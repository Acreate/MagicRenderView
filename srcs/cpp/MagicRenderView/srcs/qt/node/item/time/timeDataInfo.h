#ifndef TIMEDATAINFO_H_H_HEAD__FILE__
#define TIMEDATAINFO_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class TimeDataInfo : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	TimeDataInfo( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Process );
};

#endif // TIMEDATAINFO_H_H_HEAD__FILE__
