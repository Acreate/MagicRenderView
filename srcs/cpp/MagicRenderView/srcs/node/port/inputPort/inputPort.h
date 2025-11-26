#ifndef INPUTPORT_H_H_HEAD__FILE__
#define INPUTPORT_H_H_HEAD__FILE__
#pragma once
#include <QObject>
class Node;
class InputPort : public QObject {
	Q_OBJECT;
private:
	friend class Node;
public:
	QString name;
	Node *node;
public:
	InputPort( QObject *parent = nullptr ) : QObject( parent ) { }
	virtual const QString & getName( ) const { return name; }
	virtual void * getVarPtr( ) const = 0;
	virtual Node * getNode( ) const { return node; }
};

#endif // INPUTPORT_H_H_HEAD__FILE__
