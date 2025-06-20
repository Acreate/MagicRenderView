#ifndef SCROLLNODEINFO_H_H_HEAD__FILE__
#define SCROLLNODEINFO_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>

class NodeInfo;
class ScrollNodeInfo : public QScrollArea {
	Q_OBJECT;
protected:
	NodeInfo *nodeInfo;
public:
	ScrollNodeInfo( QWidget *parent );
	virtual NodeInfo * getNodeInfo( ) const { return nodeInfo; }
};


#endif // SCROLLNODEINFO_H_H_HEAD__FILE__
