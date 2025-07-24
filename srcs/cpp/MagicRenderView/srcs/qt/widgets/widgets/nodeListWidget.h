#ifndef NODELISTWIDGET_H_H_HEAD__FILE__
#define NODELISTWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>
class NodeListWidget : public QWidget {
	Q_OBJECT;
public:
	NodeListWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeListWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // NODELISTWIDGET_H_H_HEAD__FILE__
