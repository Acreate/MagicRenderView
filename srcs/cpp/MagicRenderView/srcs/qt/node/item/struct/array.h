#ifndef ARRAY_H_H_HEAD__FILE__
#define ARRAY_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class Array : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	Array(  );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Node_Item_Type::Process );
};

#endif // ARRAY_H_H_HEAD__FILE__
