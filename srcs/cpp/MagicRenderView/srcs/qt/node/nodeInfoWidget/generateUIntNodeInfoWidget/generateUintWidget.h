#ifndef GENERATEUINTWIDGET_H_H_HEAD__FILE__
#define GENERATEUINTWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

class NodeItem;
class GenerateUintWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
public:
	GenerateUintWidget( NodeItem *node_item ) : nodeItem( node_item ) { };
};
#endif // GENERATEUINTWIDGET_H_H_HEAD__FILE__
