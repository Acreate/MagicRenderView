#ifndef NODERENDERWIDGET_H_H_HEAD__FILE__
#define NODERENDERWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>
class NodeRenderWidget : public QScrollArea {
	Q_OBJECT;
public:
	~NodeRenderWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // NODERENDERWIDGET_H_H_HEAD__FILE__
