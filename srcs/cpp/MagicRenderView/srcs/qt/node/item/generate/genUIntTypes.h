#ifndef GENUINTTYPES_H_H_HEAD__FILE__
#define GENUINTTYPES_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class GenUIntTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenUIntTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENUINTTYPES_H_H_HEAD__FILE__
