#ifndef SCROLLNODEGRAPH_H_H_HEAD__FILE__
#define SCROLLNODEGRAPH_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>
class NodeGraph;
class ScrollNodeGraph : public QScrollArea {
	Q_OBJECT;
protected:
	NodeGraph *nodeGraph;
public:
	ScrollNodeGraph( QWidget *parent );
	~ScrollNodeGraph() override;
};

#endif // SCROLLNODEGRAPH_H_H_HEAD__FILE__
