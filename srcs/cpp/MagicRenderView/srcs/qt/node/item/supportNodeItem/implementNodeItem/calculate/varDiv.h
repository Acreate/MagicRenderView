#ifndef VARDIV_H_H_HEAD__FILE__
#define VARDIV_H_H_HEAD__FILE__
#pragma once


#include "../../processNodeItem.h"

class VarDiv : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarDiv( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // VARDIV_H_H_HEAD__FILE__
