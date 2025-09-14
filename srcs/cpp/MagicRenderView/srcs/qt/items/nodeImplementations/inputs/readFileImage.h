#ifndef READFILEIMAGE_H_H_HEAD__FILE__
#define READFILEIMAGE_H_H_HEAD__FILE__
#pragma once
#include "../../nodeItemWidget.h"

class ReadFileImage : public NodeItemWidget {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( ReadFileImage, NodeItemWidget );
protected:
	ReadFileImage( QWidget *parent ) : NodeItemWidget( parent ) { }
};

#endif // READFILEIMAGE_H_H_HEAD__FILE__
