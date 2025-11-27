#ifndef POINTNODE_H_H_HEAD__FILE__
#define POINTNODE_H_H_HEAD__FILE__
#pragma once
#include "../node.h"

class PointNode : public Node {
	Q_OBJECT;
public:
	PointNode(  QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: Node( parent, f ) { }
	bool init( QWidget *parent ) override;
	bool updateLayout( ) override;
	Def_Satatic_NodeTypeName( Node::tr( "控制/坐标点" ) );
};

#endif // POINTNODE_H_H_HEAD__FILE__
