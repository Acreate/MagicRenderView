#ifndef GENERATEFLOATWIDGET_H_H_HEAD__FILE__
#define GENERATEFLOATWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

class NodeItem;
class GenerateFloatWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
public:
	GenerateFloatWidget( NodeItem *node_item ) : nodeItem( node_item ) { };
};
#endif // GENERATEFLOATWIDGET_H_H_HEAD__FILE__
