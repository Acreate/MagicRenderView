#ifndef VARMUL_H_H_HEAD__FILE__
#define VARMUL_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class VarMul : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarMul( NodeItem_ParentPtr_Type *parent )
		: NodeItem( parent ) {
	}
};
#endif // VARMUL_H_H_HEAD__FILE__
