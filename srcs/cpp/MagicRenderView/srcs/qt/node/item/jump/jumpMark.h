#ifndef JUMPMARK_H_H_HEAD__FILE__
#define JUMPMARK_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class JumpMark : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	JumpMark( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Jump );
};

#endif // JUMPMARK_H_H_HEAD__FILE__
