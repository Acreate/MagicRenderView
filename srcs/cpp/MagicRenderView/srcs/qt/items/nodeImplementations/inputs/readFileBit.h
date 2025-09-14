#ifndef READFILEBIT_H_H_HEAD__FILE__
#define READFILEBIT_H_H_HEAD__FILE__
#pragma once


#include "../../nodeItemWidget.h"

class ReadFileBit : public NodeItemWidget {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( ReadFileBit, NodeItemWidget );
protected:
	ReadFileBit( QWidget *parent ) : NodeItemWidget( parent ) { }
};

#endif // READFILEBIT_H_H_HEAD__FILE__
