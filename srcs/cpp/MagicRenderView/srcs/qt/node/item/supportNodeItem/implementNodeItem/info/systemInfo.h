#ifndef SYSTEMINFO_H_H_HEAD__FILE__
#define SYSTEMINFO_H_H_HEAD__FILE__
#pragma once

#include "../../processNodeItem.h"

class SystemInfo : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	SystemInfo( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // SYSTEMINFO_H_H_HEAD__FILE__
