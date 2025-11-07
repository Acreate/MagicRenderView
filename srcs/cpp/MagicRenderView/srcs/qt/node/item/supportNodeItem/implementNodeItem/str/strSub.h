#ifndef STRSUB_H_H_HEAD__FILE__
#define STRSUB_H_H_HEAD__FILE__
#pragma once


#include "../../processNodeItem.h"

class StrSub : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrSub(  );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // STRSUB_H_H_HEAD__FILE__
