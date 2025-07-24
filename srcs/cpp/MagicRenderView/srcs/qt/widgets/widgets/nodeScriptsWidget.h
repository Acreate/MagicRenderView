#ifndef NODESCRIPTSWIDGET_H_H_HEAD__FILE__
#define NODESCRIPTSWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class NodeScriptsWidget : public QWidget {
	Q_OBJECT;
public:
	NodeScriptsWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeScriptsWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
};
#endif // NODESCRIPTSWIDGET_H_H_HEAD__FILE__
