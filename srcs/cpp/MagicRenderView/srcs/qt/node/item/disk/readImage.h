#ifndef READIMAGE_H_H_HEAD__FILE__
#define READIMAGE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class ReadImage : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	ReadImage( NodeItem_ParentPtr_Type *parent )
		: NodeItem( parent ) {
		nodeTitleName = getMetaObjectName( );
	}
};
#endif // READIMAGE_H_H_HEAD__FILE__
