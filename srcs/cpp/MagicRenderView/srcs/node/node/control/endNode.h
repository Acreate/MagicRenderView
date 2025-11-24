#ifndef ENDNODE_H_H_HEAD__FILE__
#define ENDNODE_H_H_HEAD__FILE__
#pragma once
#include "../node.h"

class EndNode : public Node {
	Q_OBJECT;
public:
	EndNode(  QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: Node( parent, f ) { }
	bool init( QWidget *parent ) override;
	Def_Satatic_NodeTypeName( Node::tr( "控制/结束" ) );
};

#endif // ENDNODE_H_H_HEAD__FILE__
