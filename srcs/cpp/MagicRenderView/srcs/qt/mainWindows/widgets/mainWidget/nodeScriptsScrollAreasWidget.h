#ifndef NODESCRIPTSSCROLLAREASWIDGET_H_H_HEAD__FILE__
#define NODESCRIPTSSCROLLAREASWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class NodeScriptsWidget;
class NodeScriptsScrollAreasWidget : public QScrollArea {
	Q_OBJECT;
protected:
	NodeScriptsWidget* nodeScriptsWidget;
public:
	NodeScriptsScrollAreasWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeScriptsScrollAreasWidget( ) override;
};

#endif // NODESCRIPTSSCROLLAREASWIDGET_H_H_HEAD__FILE__
