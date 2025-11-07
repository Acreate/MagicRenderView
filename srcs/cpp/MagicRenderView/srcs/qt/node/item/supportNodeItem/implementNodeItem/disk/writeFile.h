#ifndef WRITEFILE_H_H_HEAD__FILE__
#define WRITEFILE_H_H_HEAD__FILE__
#pragma once
#include "../../processNodeItem.h"

class WriteFile : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	WriteFile( );
public:
	bool intPortItems( MainWidget *parent ) override;
};

#endif // WRITEFILE_H_H_HEAD__FILE__
