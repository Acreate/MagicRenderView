#ifndef VARADD_H_H_HEAD__FILE__
#define VARADD_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class VarAdd : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarAdd( )
		: NodeItem(  ) {
	}
};
#endif // VARADD_H_H_HEAD__FILE__
