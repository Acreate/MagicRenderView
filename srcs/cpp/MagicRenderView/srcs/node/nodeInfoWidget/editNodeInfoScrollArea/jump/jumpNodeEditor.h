#ifndef JUMPNODEEDITOR_H_H_HEAD__FILE__
#define JUMPNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class JumpNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
public:
	JumpNodeEditor( NodeInfoWidget *parent )
		: EditorNodeInfoScrollArea( parent ) { }
};

#endif // JUMPNODEEDITOR_H_H_HEAD__FILE__
