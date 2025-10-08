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
};
#endif // TIMEDATACONVER_H_H_HEAD__FILE__
