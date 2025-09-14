#ifndef WRITEFILEBIT_H_H_HEAD__FILE__
#define WRITEFILEBIT_H_H_HEAD__FILE__
#pragma once

#include "../../nodeItemWidget.h"

class WriteFileBit : public NodeItemWidget {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( WriteFileBit, NodeItemWidget );
protected:
	WriteFileBit( QWidget *parent ) : NodeItemWidget( parent ) { }
};
#endif // WRITEFILEBIT_H_H_HEAD__FILE__
