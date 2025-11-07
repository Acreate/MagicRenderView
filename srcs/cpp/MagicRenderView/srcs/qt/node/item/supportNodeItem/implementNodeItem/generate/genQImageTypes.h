#ifndef GENQIMAGETYPES_H_H_HEAD__FILE__
#define GENQIMAGETYPES_H_H_HEAD__FILE__
#pragma once

#include "../../generateVarNodeItem.h"

class GenerateListScrollArea;
class GenerateQImageWidget;
class GenerateListItemWidget;
class VarEditorWidget;
class GenerateListWidget;
class GenQImageTypes : public GenerateVarNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateQImageWidget* generateQImageWidget;
protected:
	virtual void changeVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
	virtual void delVarOver( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
protected:
	GenQImageTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
};


#endif // GENQIMAGETYPES_H_H_HEAD__FILE__
