#ifndef GENFLOATTYPES_H_H_HEAD__FILE__
#define GENFLOATTYPES_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class GenerateFloatWidget;
class GenFloatTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateFloatWidget* generateFloatWidget;
protected:
	GenFloatTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENFLOATTYPES_H_H_HEAD__FILE__
