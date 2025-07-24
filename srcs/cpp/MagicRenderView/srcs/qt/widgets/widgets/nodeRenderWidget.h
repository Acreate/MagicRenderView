#ifndef NODERENDERWIDGET_H_H_HEAD__FILE__
#define NODERENDERWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class NodeRenderWidget : public QWidget {
	Q_OBJECT;
public:
	NodeRenderWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeRenderWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
};
#endif // NODERENDERWIDGET_H_H_HEAD__FILE__
