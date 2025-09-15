#ifndef READFILE_H_H_HEAD__FILE__
#define READFILE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class ReadFile : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
public:
	ReadFile( QObject *parent )
		: NodeItem( parent ) { }
};
#endif // READFILE_H_H_HEAD__FILE__
