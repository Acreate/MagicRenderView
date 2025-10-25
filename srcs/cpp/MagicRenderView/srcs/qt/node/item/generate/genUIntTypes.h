#ifndef GENUINTTYPES_H_H_HEAD__FILE__
#define GENUINTTYPES_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class GenerateListItemWidget;
class VarEditorWidget;
class GenerateListWidget;
class GenUIntTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateListWidget *generateUintWidget;
protected:
	virtual void changeVarOverSignal( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
protected:
	GenUIntTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENUINTTYPES_H_H_HEAD__FILE__
