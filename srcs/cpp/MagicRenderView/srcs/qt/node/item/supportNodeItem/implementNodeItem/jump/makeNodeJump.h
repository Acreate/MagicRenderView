#ifndef MAKENODEJUMP_H_H_HEAD__FILE__
#define MAKENODEJUMP_H_H_HEAD__FILE__
#pragma once

#include "../../jumpNodeItem.h"

class MakeNodeJump : public JumpNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	MakeNodeJump( );
public:
	bool intPortItems( MainWidget *parent ) override;
};


#endif // MAKENODEJUMP_H_H_HEAD__FILE__
