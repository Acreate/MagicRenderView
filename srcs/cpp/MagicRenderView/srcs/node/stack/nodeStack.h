#ifndef NODESTACK_H_H_HEAD__FILE__
#define NODESTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class Node;
class QMenu;
class NodeStack : public QObject {
	Q_OBJECT;
	friend class NodeDirector;
protected:
	virtual bool init( ) = 0;
protected:
	std::vector< std::pair< QString, std::function< Node *( ) > > > nodeGenerate;
public:
	NodeStack( QObject *parent = nullptr );
	~NodeStack( ) override;
	virtual Node * createNode( const QString &node_type_name );
	virtual QMenu * toMenu( ) = 0;
};

#endif // NODESTACK_H_H_HEAD__FILE__
