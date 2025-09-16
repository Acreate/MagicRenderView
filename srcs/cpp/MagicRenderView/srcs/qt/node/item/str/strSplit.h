#ifndef STRSPLIT_H_H_HEAD__FILE__
#define STRSPLIT_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class StrSplit : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrSplit( NodeItem_ParentPtr_Type *parent )
		: NodeItem( parent ) {
	}
};
#endif // STRSPLIT_H_H_HEAD__FILE__
