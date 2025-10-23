#ifndef GENERATEQCOLORWIDGET_H_H_HEAD__FILE__
#define GENERATEQCOLORWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

class NodeItem;
class GenerateQColorWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
public:
	GenerateQColorWidget( NodeItem *node_item ) : nodeItem( node_item ) { };
};
#endif // GENERATEQCOLORWIDGET_H_H_HEAD__FILE__
