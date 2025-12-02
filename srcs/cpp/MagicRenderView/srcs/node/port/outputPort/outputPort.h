#ifndef OUTPUTPORT_H_H_HEAD__FILE__
#define OUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <QWidget>

#include <enums/nodeEnum.h>

class QHBoxLayout;
class QLabel;
class SrackInfo;
class InputPort;
class Application;
class VarDirector;
class Node;
class OutputPort : public QWidget {
	Q_OBJECT;
private:
	friend class Node;
	friend class InputPort;
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
	QMenu *disLinkMenu;
public:
	OutputPort( const QString &name );
	~OutputPort( ) override;
	virtual bool init( Node *parent );
	virtual NodeEnum::PortType getPortType( ) const =0;
	virtual const QString & getPortName( ) const { return portName; }
	virtual const QString & getVarTypeName( ) const { return varTypeName; }
	virtual void * getVarPtr( ) const { return varPtr; }
	virtual QPoint getLinkPoint( ) const;
	virtual Node * getParentNode( ) const { return parentNode; }
	virtual QMenu * getDisLinkMenu( ) const { return disLinkMenu; }
};
#endif // OUTPUTPORT_H_H_HEAD__FILE__
