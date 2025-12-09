#ifndef GENERATENODEEDITOR_H_H_HEAD__FILE__
#define GENERATENODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class GenerateInfoEditorTitle;
class GeneratePanelWidget;
class GenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	GenerateInfoEditorTitle *topAddVarMenu;
	GeneratePanelWidget *addShowItemWidget;
public:
	GenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
protected:
	void resizeEvent( QResizeEvent * ) override;
};

#endif // GENERATENODEEDITOR_H_H_HEAD__FILE__
