#ifndef NODEPORT_H_H_HEAD__FILE__
#define NODEPORT_H_H_HEAD__FILE__
#include <QWidget>
#include <define/portFrinedClass.h>
#include <enums/nodeEnum.h>

Declaration_Class_Name( );

class NodePort : public QWidget {
	Q_OBJECT;
	NodePortFrinedClass( );
protected:
	Node *parentNode;
	VarDirector *varDirectorPtr;
	void *varPtr;
	bool multiple;
	QString portName;
	QString varTypeName;
	uint64_t generateCode;
public:
	NodePort( );
	virtual void * getVarPtr( ) const { return varPtr; }
	virtual bool isMultiple( ) const { return multiple; }
	virtual VarDirector * getVarDirector( ) const;
	virtual const QString & getPortName( ) const { return portName; }
	virtual const QString & getVarTypeName( ) const { return varTypeName; }
	virtual uint64_t getGenerateCode( ) const { return generateCode; }
	virtual Node * getParentNode( ) const { return parentNode; }
	virtual bool init( Node *parent ) =0;
	virtual NodeEnum::PortType getPortType( ) const =0;
	virtual QPoint getLinkPoint( ) const =0;
};

#endif // NODEPORT_H_H_HEAD__FILE__
