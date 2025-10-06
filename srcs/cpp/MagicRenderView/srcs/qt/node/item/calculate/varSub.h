#ifndef VARSUB_H_H_HEAD__FILE__
#define VARSUB_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class VarSub : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarSub( )
		: NodeItem(  ){
	}
};
#endif // VARSUB_H_H_HEAD__FILE__
