#ifndef STRAPPEND_H_H_HEAD__FILE__
#define STRAPPEND_H_H_HEAD__FILE__
#pragma once


#include "../../processNodeItem.h"

class StrAppend : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrAppend( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // STRAPPEND_H_H_HEAD__FILE__
