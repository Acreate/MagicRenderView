#ifndef READIMAGE_H_H_HEAD__FILE__
#define READIMAGE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class ReadImage : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	ReadImage( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Process );
};
#endif // READIMAGE_H_H_HEAD__FILE__
