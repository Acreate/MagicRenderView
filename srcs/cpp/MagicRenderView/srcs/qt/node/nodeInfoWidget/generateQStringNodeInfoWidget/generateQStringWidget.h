#ifndef GENERATEQSTRINGWIDGET_H_H_HEAD__FILE__
#define GENERATEQSTRINGWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

class NodeItem;
class GenerateQStringWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
public:
	GenerateQStringWidget( NodeItem *node_item ) : nodeItem( node_item ) { };
};
#endif // GENERATEQSTRINGWIDGET_H_H_HEAD__FILE__
