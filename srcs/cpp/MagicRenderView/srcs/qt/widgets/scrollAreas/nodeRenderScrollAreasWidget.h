#ifndef NODERENDERSCROLLAREASWIDGET_H_H_HEAD__FILE__
#define NODERENDERSCROLLAREASWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class NodeRenderWidget;
class NodeRenderScrollAreasWidget : public QScrollArea {
	Q_OBJECT;
protected:
	NodeRenderWidget* nodeRenderWidget;
public:
	NodeRenderScrollAreasWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeRenderScrollAreasWidget( ) override;
};

#endif // NODERENDERSCROLLAREASWIDGET_H_H_HEAD__FILE__
