#ifndef GENCOLORTYPES_H_H_HEAD__FILE__
#define GENCOLORTYPES_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class GenColorTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenColorTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENCOLORTYPES_H_H_HEAD__FILE__
