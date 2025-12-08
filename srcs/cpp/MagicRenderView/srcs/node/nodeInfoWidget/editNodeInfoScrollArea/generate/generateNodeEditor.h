#ifndef GENERATENODEEDITOR_H_H_HEAD__FILE__
#define GENERATENODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class GenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
public:
	GenerateNodeEditor( NodeInfoWidget *parent );
	void * getVarPtr( ) const override;
	const std::type_info & getVarType( ) const override;
	void clearVar( ) override;
};

#endif // GENERATENODEEDITOR_H_H_HEAD__FILE__
