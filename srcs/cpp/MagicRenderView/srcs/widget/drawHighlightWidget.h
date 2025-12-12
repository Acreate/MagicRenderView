#ifndef DRAWHIGHLIGHTWIDGET_H_H_HEAD__FILE__
#define DRAWHIGHLIGHTWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../enums/nodeEnum.h"

class Node;
class MainWidget;
class SrackInfo;
class DrawHighlightWidget : public QWidget {
	Q_OBJECT;
	using TPaintCallFunction = std::function< void( Node *, NodeEnum::NodeStyleType ) >;
	using TPairType = std::pair< NodeEnum::NodeStyleType, TPaintCallFunction >;
	using TArrayPairType = std::pair< Node *, TPairType >;
protected:
	std::vector< TArrayPairType > drawNodeType;
	TArrayPairType *drawNodeTypeArratPtr;
	size_t drawNodeTypeArratCount;
	size_t drawNodeTypeArratIndex;
protected:
	/// @brief 释放对象产生信号
	/// @param release_node 释放对象指针
	/// @param srack_info 信号行
	void releaseNode( Node *release_node, const SrackInfo &srack_info );
public:
	DrawHighlightWidget( MainWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual bool init( MainWidget *parent );
	virtual NodeEnum::NodeStyleType getNodeDrawNodeType( const Node *find_node_ptr ) const;
	virtual TPaintCallFunction getNodeDrawNodeCallFuntionType( const Node *find_node_ptr ) const;
	virtual TPairType getNodeDrawNodePairType( const Node *find_node_ptr ) const;
	virtual void setNodeDrawNodeType( Node *set_node_ptr, NodeEnum::NodeStyleType new_node_type );
	virtual void setNodeDrawNodeType( Node *set_node_ptr, NodeEnum::NodeStyleType new_node_type, const TPaintCallFunction &paint_event );
	~DrawHighlightWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
Q_SIGNALS:
	void release_signal( DrawHighlightWidget *release_ptr );
};

#endif // DRAWHIGHLIGHTWIDGET_H_H_HEAD__FILE__
