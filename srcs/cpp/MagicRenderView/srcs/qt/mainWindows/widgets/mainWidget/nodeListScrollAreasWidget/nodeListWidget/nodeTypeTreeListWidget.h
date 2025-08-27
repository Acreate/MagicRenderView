#ifndef NODETYPETREELISTWIDGET_H_H_HEAD__FILE__
#define NODETYPETREELISTWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QTreeWidget.h>

class NodeTypeTreeListWidget : public QTreeWidget {
	Q_OBJECT;
public:
	NodeTypeTreeListWidget( QWidget *parent = nullptr ) : QTreeWidget( parent ) { }
};

#endif // NODETYPETREELISTWIDGET_H_H_HEAD__FILE__
