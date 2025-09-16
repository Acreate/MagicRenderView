#ifndef STRSUB_H_H_HEAD__FILE__
#define STRSUB_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class StrSub : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrSub( NodeItem_ParentPtr_Type *parent )
		: NodeItem( parent ) {
	}
};
#endif // STRSUB_H_H_HEAD__FILE__
