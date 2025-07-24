#ifndef NODELISTSCROLLAREASWIDGET_H_H_HEAD__FILE__
#define NODELISTSCROLLAREASWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>
class NodeListWidget;
class NodeListScrollAreasWidget : public QScrollArea {
	Q_OBJECT;
protected:
	NodeListWidget* nodeListWidget;
public:
	NodeListScrollAreasWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeListScrollAreasWidget( ) override;
};

#endif // NODELISTSCROLLAREASWIDGET_H_H_HEAD__FILE__
