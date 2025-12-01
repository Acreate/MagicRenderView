#ifndef INPUTPORT_H_H_HEAD__FILE__
#define INPUTPORT_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QWidget>

#include <enums/nodeEnum.h>
class QHBoxLayout;
class QLabel;
class Application;
class VarDirector;
class OutputPort;
class NodePortLinkInfo;
class Node;
class InputPort : public QWidget {
	Q_OBJECT;
private:
	friend class Node;
	friend class OutputPort;
	friend class NodeDirector;
	friend class NodeStack;
	friend class NodeRefLinkInfoTools;
protected:
	Application *instancePtr;
	VarDirector *varDirector;
protected:
	QString portName;
	QString varTypeName;
	void *varPtr;
protected:
	QLabel *ico;
	QLabel *showTitle;
	QHBoxLayout *mainLayout;
	Node *parentNode;
public:
	InputPort( const QString &name );
	virtual bool init( Node *parent );
	~InputPort( ) override;
	virtual NodeEnum::PortType getPortType( ) const =0;
	virtual const QString & getPortName( ) const { return portName; }
	virtual const QString & getVarTypeName( ) const { return varTypeName; }
	virtual void * getVarPtr( ) const { return varPtr; }
	virtual QPoint getLinkPoint( ) const;
	virtual Node * getParentNode( ) const { return parentNode; }
};

#endif // INPUTPORT_H_H_HEAD__FILE__
