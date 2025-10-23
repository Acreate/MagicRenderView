#ifndef GENQIMAGETYPES_H_H_HEAD__FILE__
#define GENQIMAGETYPES_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class GenerateQImageWidget;
class GenQImageTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateQImageWidget* generateQImageWidget;
protected:
	GenQImageTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};


#endif // GENQIMAGETYPES_H_H_HEAD__FILE__
