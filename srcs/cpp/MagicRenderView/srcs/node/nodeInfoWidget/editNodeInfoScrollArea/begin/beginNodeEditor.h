#ifndef BEGINNODEEDITOR_H_H_HEAD__FILE__
#define BEGINNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class BeginNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
public:
	BeginNodeEditor( NodeInfoWidget *parent );
	void * getVarPtr( ) const override;
	const std::type_info & getVarType( ) const override;
	void clearVar( ) override;
	~BeginNodeEditor( ) override;
	bool initNode( Node *init_node ) override;
};

#endif // BEGINNODEEDITOR_H_H_HEAD__FILE__
