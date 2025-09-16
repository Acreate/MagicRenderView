#ifndef STRREPLACE_H_H_HEAD__FILE__
#define STRREPLACE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class StrReplace : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrReplace( NodeItem_ParentPtr_Type *parent )
		: NodeItem( parent ){
	}
};
#endif // STRREPLACE_H_H_HEAD__FILE__
