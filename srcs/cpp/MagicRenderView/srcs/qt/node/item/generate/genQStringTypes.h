#ifndef GENQSTRINGTYPES_H_H_HEAD__FILE__
#define GENQSTRINGTYPES_H_H_HEAD__FILE__
#pragma once


#include "../nodeItem.h"

class GenerateListItemWidget;
class VarEditorWidget;
class GenerateListWidget;
class GenQStringTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateListWidget* generateQStringWidget;
protected:
	virtual void changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
	virtual void delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
protected:
	GenQStringTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENQSTRINGTYPES_H_H_HEAD__FILE__
