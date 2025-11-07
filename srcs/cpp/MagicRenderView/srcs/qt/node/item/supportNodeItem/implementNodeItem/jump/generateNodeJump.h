#ifndef GENERATENODEJUMP_H_H_HEAD__FILE__
#define GENERATENODEJUMP_H_H_HEAD__FILE__
#pragma once

#include "../../releaseNodeItem.h"

class GenerateNodeJump : public ReleaseNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateNodeJump( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // GENERATENODEJUMP_H_H_HEAD__FILE__
