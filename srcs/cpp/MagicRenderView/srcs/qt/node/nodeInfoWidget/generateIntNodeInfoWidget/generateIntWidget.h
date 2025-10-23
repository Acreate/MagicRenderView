#ifndef GENERATEINTWIDGET_H_H_HEAD__FILE__
#define GENERATEINTWIDGET_H_H_HEAD__FILE__
#pragma once


#include <QWidget>

class NodeItem;
class GenerateIntWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
public:
	GenerateIntWidget( NodeItem *node_item ) : nodeItem( node_item ) { };
};
#endif // GENERATEINTWIDGET_H_H_HEAD__FILE__
