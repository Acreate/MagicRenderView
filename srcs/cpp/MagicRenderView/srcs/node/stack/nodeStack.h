#ifndef NODESTACK_H_H_HEAD__FILE__
#define NODESTACK_H_H_HEAD__FILE__

#include <QObject>

#include "../../enums/nodeEnum.h"

#define Def_EmaplaceBackNode( _Type) appendNodeGenerateUnity( _Type::getStaticNodeTypeName( ), [](const QString& node_name) { return new _Type( node_name ); }  )

class VarDirector;
class PrinterDirector;
class Application;
class QAction;
class Node;
class QMenu;
class NodeStack : public QObject {
	Q_OBJECT;
	friend class NodeDirector;
	friend class NormalGenerateNodeMenu;
protected:
protected:
	virtual bool init( );
private:
	std::vector< std::pair< QString, std::function< Node *( const QString & ) > > > nodeGenerate;
protected:
	Application *instancePtr;
	PrinterDirector *printerDirector;
protected:
	virtual bool appendNodeGenerateUnity( const QString &name, const std::function< Node *( const QString & ) > &generate_function );
public:
	NodeStack( QObject *parent = nullptr );
	~NodeStack( ) override;
	virtual Node * createNode( const QString &node_type_name );
};

#endif // NODESTACK_H_H_HEAD__FILE__
