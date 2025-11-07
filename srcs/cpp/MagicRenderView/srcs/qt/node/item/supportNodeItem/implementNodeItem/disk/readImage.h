#ifndef READIMAGE_H_H_HEAD__FILE__
#define READIMAGE_H_H_HEAD__FILE__
#pragma once

#include "../../processNodeItem.h"

class ReadImage : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	ReadImage( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Process );
};
#endif // READIMAGE_H_H_HEAD__FILE__
