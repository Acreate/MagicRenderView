#ifndef SCROLLNODEGRAPH_H_H_HEAD__FILE__
#define SCROLLNODEGRAPH_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>

#include "qt/serialize/ISerialize.h"
class MainWindow;
class NodeGraph;
class ScrollNodeGraph : public QScrollArea{
	Q_OBJECT;
protected:
	NodeGraph *nodeGraph;
public:
	ScrollNodeGraph( QWidget *parent );
	~ScrollNodeGraph( ) override;
	virtual NodeGraph * getNodeGraph( ) const { return nodeGraph; }
};

#endif // SCROLLNODEGRAPH_H_H_HEAD__FILE__
