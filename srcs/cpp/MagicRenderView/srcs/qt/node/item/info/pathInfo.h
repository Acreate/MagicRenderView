#ifndef PATHINFO_H_H_HEAD__FILE__
#define PATHINFO_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class PathInfo : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	PathInfo( NodeItem_ParentPtr_Type *parent )
		: NodeItem( parent ) {
		nodeTitleName = getMetaObjectName( );
	}
};
#endif // PATHINFO_H_H_HEAD__FILE__
