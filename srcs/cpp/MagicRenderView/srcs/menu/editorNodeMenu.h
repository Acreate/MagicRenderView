#ifndef EDITORNODEMENU_H_H_HEAD__FILE__
#define EDITORNODEMENU_H_H_HEAD__FILE__
#pragma once

#include <QMenu>
class EditorNodeMenu : public QMenu {
	Q_OBJECT;
public:
	virtual bool initEditorNodeMenu( ) {
		return false;
	}
};


#endif // EDITORNODEMENU_H_H_HEAD__FILE__
