#ifndef STRREPLACE_H_H_HEAD__FILE__
#define STRREPLACE_H_H_HEAD__FILE__
#pragma once


#include "../../processNodeItem.h"

class StrReplace : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrReplace(  );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // STRREPLACE_H_H_HEAD__FILE__
