#ifndef READFILE_H_H_HEAD__FILE__
#define READFILE_H_H_HEAD__FILE__
#pragma once


#include "../../processNodeItem.h"

class ReadFile : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	ReadFile( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // READFILE_H_H_HEAD__FILE__
