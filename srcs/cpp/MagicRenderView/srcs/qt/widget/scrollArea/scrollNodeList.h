#ifndef SCROLLNODELIST_H_H_HEAD__FILE__
#define SCROLLNODELIST_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>
class NodeList;

class ScrollNodeList : public QScrollArea {
	Q_OBJECT;
protected:
	NodeList *nodeList;
public:
	ScrollNodeList( QWidget *parent );
};

#endif // SCROLLNODELIST_H_H_HEAD__FILE__
