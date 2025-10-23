#ifndef GENINTTYPES_H_H_HEAD__FILE__
#define GENINTTYPES_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class GenerateIntWidget;
class GenIntTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateIntWidget* generateIntWidget;
protected:
	GenIntTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENINTTYPES_H_H_HEAD__FILE__
