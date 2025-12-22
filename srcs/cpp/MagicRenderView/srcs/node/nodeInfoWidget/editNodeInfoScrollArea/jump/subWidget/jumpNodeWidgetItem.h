#ifndef JUMPNODEWIDGETITEM_H_H_HEAD__FILE__
#define JUMPNODEWIDGETITEM_H_H_HEAD__FILE__
#pragma once
#include <qpen.h>
#include <QWidget>

#include "../../../../node/node.h"

class JumpNodeEditor;
class QVBoxLayout;
class JumpNodeWidgetItem : public QWidget {
	Q_OBJECT;
private:
	using TCurrentAction = std::pair< QAction *, QAction * >;
	using ItemPair = std::pair< QWidget *, std::pair< TCurrentAction *, Node * > >;
protected:
	QVBoxLayout *mainLayout;
	std::vector< ItemPair > nodeVector;
	QPen itemPen;
	QPen subItemPen;
	QMenu *popMenu;
	TCurrentAction *currentAction;
	size_t nodeArrayCount;
	ItemPair *nodeArratPtr;
	size_t nodeArrayIndex;
	bool isPopMenu;
protected:
	virtual void appendNodeRefItem( Node *item );
	virtual void clearCurrentAction( );
	virtual void selectionCurrentAction( );
	virtual void releaseNodeArrayInfo( );
public:
	JumpNodeWidgetItem( QWidget *parent );
	~JumpNodeWidgetItem( ) override;
	virtual void setNodeRefVector( const std::vector< Node * > &node_ref_link_infos );
	virtual const QPen & getItemPen( ) const { return itemPen; }
	virtual void setItemPen( const QPen &item_pen ) { itemPen = item_pen; }
	virtual const QPen & getSubItemPen( ) const { return subItemPen; }
	virtual void setSubItemPen( const QPen &sub_item_pen ) { subItemPen = sub_item_pen; }
	virtual bool isIsPopMenu( ) const { return isPopMenu; }
	virtual void setIsPopMenu( bool is_pop_menu ) { isPopMenu = is_pop_menu; }
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	bool eventFilter( QObject *watched, QEvent *event ) override;
	void hideEvent( QHideEvent *event ) override;
Q_SIGNALS:
	void showNodeInfoWidgetLeft( Node *node_ref_link_info );
	void showNodeInfoWidgetRight( Node *node_ref_link_info );

};

#endif // JUMPNODEWIDGETITEM_H_H_HEAD__FILE__
