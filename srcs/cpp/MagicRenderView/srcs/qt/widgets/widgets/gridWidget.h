#ifndef GRIDWIDGET_H_H_HEAD__FILE__
#define GRIDWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../../functionDeclaration/IFunctionDeclaration.h"

class INodeGeneraterItem;
class QGridLayout;
class GridWidget : public QWidget {
	Q_OBJECT;
protected:
	QGridLayout *mainLayout;
	QWidget *mainContentWidget;
	std_vector< std_pairt< std_shared_ptr< INodeGeneraterItem >, QWidget * > > nodeGeneraterItems;
	std_vector< QWidget * > showNodeList;
	std::shared_ptr< INodeGeneraterItem > selectItem;
	int columnCount;
protected:
public:
	GridWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	virtual bool addNode( const IFunctionDeclaration &function_declaration );
	virtual void updateLayout( );
	virtual void removeItem( const INodeGeneraterItem *node_generater_item );
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
Q_SIGNALS:
	void dragNode( const std_shared_ptr< INodeGeneraterItem > &node_generater_item );
	void selectNode( const std_shared_ptr< INodeGeneraterItem > &node_generater_item );
};

#endif // GRIDWIDGET_H_H_HEAD__FILE__
