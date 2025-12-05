#ifndef ENDNODEEDITOR_H_H_HEAD__FILE__
#define ENDNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class EndNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
public:
	EndNodeEditor( NodeInfoWidget *parent )
		: EditorNodeInfoScrollArea( parent ) { }
};

#endif // ENDNODEEDITOR_H_H_HEAD__FILE__
