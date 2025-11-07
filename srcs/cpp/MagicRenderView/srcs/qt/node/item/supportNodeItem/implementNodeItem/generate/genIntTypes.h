#ifndef GENINTTYPES_H_H_HEAD__FILE__
#define GENINTTYPES_H_H_HEAD__FILE__
#pragma once


#include "../../generateVarNodeItem.h"

class GenerateListScrollArea;
class GenerateListItemWidget;
class VarEditorWidget;
class GenerateListWidget;
class GenIntTypes : public GenerateVarNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateListWidget* generateIntWidget;
protected:
	virtual void changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
	virtual void delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
protected:
	GenIntTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENINTTYPES_H_H_HEAD__FILE__
