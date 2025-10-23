#ifndef GENBINTYPES_H_H_HEAD__FILE__
#define GENBINTYPES_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class GenerateBinWidget;
class GenBinTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateBinWidget* generateBinWidget;
protected:
	GenBinTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENBINTYPES_H_H_HEAD__FILE__
