#ifndef GENERATENODEJUMP_H_H_HEAD__FILE__
#define GENERATENODEJUMP_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class GenerateNodeJump : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateNodeJump( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( ReleaseVar );
};
#endif // GENERATENODEJUMP_H_H_HEAD__FILE__
