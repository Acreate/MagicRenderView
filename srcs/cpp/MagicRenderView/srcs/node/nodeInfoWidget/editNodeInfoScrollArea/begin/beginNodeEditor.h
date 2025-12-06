#ifndef BEGINNODEEDITOR_H_H_HEAD__FILE__
#define BEGINNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class BeginNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	std::vector< std::pair< QWidget *, Node * > > beginVectorNode;
	std::vector< std::pair< QWidget *, Node * > > endVectorNode;
	std::vector< std::pair< QWidget *, Node * > > processVectorNode;
public:
	BeginNodeEditor( NodeInfoWidget *parent );
	virtual void setBeginNodeVector( const std::vector< Node * > &begin_vector_node );
	virtual void setEndNodeVector( const std::vector< Node * > &end_vector_node );
	virtual void setProcessNodeVector( const std::vector< Node * > &process_vector_node );
	void * getVarPtr( ) const override;
	const std::type_info & getVarType( ) const override;
	void clearVar( ) override;
	~BeginNodeEditor( ) override;
	bool initNode( Node *init_node ) override;
Q_SIGNALS:
	void clickNodeItem( Node *click_node );
};

#endif // BEGINNODEEDITOR_H_H_HEAD__FILE__
