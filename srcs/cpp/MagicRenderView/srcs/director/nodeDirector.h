#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>
class QMenu;
class NodeDirector : public QObject {
	Q_OBJECT;
	friend class Application;
protected:
	QMenu *nodeCreateMenu;
protected:
	virtual bool init( );
public:
	NodeDirector( QObject *parent = nullptr );
	virtual QMenu * getNodeCreateMenu( ) const { return nodeCreateMenu; }

};

#endif // NODEDIRECTOR_H_H_HEAD__FILE__
