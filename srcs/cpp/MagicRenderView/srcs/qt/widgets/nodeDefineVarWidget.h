#ifndef NODEDEFINEVARWIDGET_H_H_HEAD__FILE__
#define NODEDEFINEVARWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

class QMenuBar;
class QVBoxLayout;
class QTreeWidget;
class NodeDefineVarWidget : public QWidget {
	Q_OBJECT;
protected:
	QTreeWidget *defindeTree;
	QVBoxLayout *mainLayout;
	QMenuBar *menuBar;
public:
	NodeDefineVarWidget( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
};

#endif // NODEDEFINEVARWIDGET_H_H_HEAD__FILE__
