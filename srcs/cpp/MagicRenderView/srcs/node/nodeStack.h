#ifndef NODESTACK_H_H_HEAD__FILE__
#define NODESTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class QMenu;
class NodeStack : public QObject {
	Q_OBJECT;
public:
	NodeStack( QObject *parent = nullptr);
	virtual QMenu * toMenu( ) const;
};

#endif // NODESTACK_H_H_HEAD__FILE__
