#ifndef SYSTEMINFO_H_H_HEAD__FILE__
#define SYSTEMINFO_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class SystemInfo : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	SystemInfo( NodeItem_ParentPtr_Type *parent )
		: NodeItem( parent ) {
	}
};
#endif // SYSTEMINFO_H_H_HEAD__FILE__
