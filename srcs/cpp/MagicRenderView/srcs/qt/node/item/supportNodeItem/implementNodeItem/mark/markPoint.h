#ifndef MARKPOINT_H_H_HEAD__FILE__
#define MARKPOINT_H_H_HEAD__FILE__
#pragma once

#include "../../markNodeItem.h"

class MarkPoint : public MarkNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	MarkPoint( );
public:
	bool intPortItems( MainWidget *parent ) override;
};

#endif // MARKPOINT_H_H_HEAD__FILE__
