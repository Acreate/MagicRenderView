#ifndef POINTNODEEDITOR_H_H_HEAD__FILE__
#define POINTNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class PointNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
public:
	PointNodeEditor( NodeInfoWidget *parent )
		: EditorNodeInfoScrollArea( parent ) { }
	void * getVarPtr( ) const override;
	const std::type_info & getVarType( ) const override;
	void clearVar( ) override;
};

#endif // POINTNODEEDITOR_H_H_HEAD__FILE__
