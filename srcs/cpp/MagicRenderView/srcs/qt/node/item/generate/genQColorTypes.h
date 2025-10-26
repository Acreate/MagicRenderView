#ifndef GENQCOLORTYPES_H_H_HEAD__FILE__
#define GENQCOLORTYPES_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class GenerateListScrollArea;
class GenerateListWidget;
class GenerateListItemWidget;
class VarEditorWidget;
class GenerateQColorWidget;
class GenQColorTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateQColorWidget* generateQColorWidget;
protected:
	virtual void changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
	virtual void delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
protected:
	GenQColorTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( GenerateVar );
};

#endif // GENQCOLORTYPES_H_H_HEAD__FILE__
