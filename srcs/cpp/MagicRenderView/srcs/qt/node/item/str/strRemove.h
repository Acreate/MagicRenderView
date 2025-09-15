#ifndef STRREMOVE_H_H_HEAD__FILE__
#define STRREMOVE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class StrRemove : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrRemove( NodeItem_ParentPtr_Type *parent )
		: NodeItem( parent ) {
		nodeTitleName = getMetaObjectName( );
	}
};
#endif // STRREMOVE_H_H_HEAD__FILE__
