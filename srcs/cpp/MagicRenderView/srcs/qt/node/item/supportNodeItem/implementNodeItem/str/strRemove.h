#ifndef STRREMOVE_H_H_HEAD__FILE__
#define STRREMOVE_H_H_HEAD__FILE__
#pragma once


#include "../../processNodeItem.h"

class StrRemove : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrRemove(  );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Process );
};
#endif // STRREMOVE_H_H_HEAD__FILE__
