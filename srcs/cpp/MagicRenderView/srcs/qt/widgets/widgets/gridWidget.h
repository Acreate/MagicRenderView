#ifndef GRIDWIDGET_H_H_HEAD__FILE__
#define GRIDWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../../functionDeclaration/IFunctionDeclaration.h"

#include "../../nodes/nodeGeneraterItems/INodeGeneraterItem.h"

class QGridLayout;
class GridWidget : public QWidget {
	Q_OBJECT;
protected:
	QGridLayout *mainLayout;
	std_vector<std_shared_ptr<INodeGeneraterItem>> nodeGeneraterItems;
public:
	GridWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	virtual bool addNode( const IFunctionDeclaration &function_declaration );
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
Q_SIGNALS:
	void dragNode( const INodeGeneraterItem &node_generater_item );
};

#endif // GRIDWIDGET_H_H_HEAD__FILE__
