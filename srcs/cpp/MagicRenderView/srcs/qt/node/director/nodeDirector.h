#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../../alias/type_alias.h"

class NodeItemInfoScrollAreaWidget;
class NodeItem;
class NodeEditorWidget;
class NodeOutputPort;
class NodeInputPort;
class NodeDirector : public QObject {
	Q_OBJECT;
protected:
	std_vector< NodeItemInfoScrollAreaWidget * > nodeItemInfoScrollAreaWidgets;
protected:
	virtual bool addManagementWidget( NodeItemInfoScrollAreaWidget *add_widget );
	virtual bool removeManagementWidget( NodeItemInfoScrollAreaWidget *add_widget );
public:
	NodeDirector( QObject *parent = nullptr );
	~NodeDirector( ) override;
	virtual NodeItemInfoScrollAreaWidget * requestGetNodeEditorWidget( const type_info &request_type, NodeItem *request_node_item_ptr );
	virtual bool linkInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port );
	virtual bool linkUnInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port );
	virtual size_t run( );
};

#endif // NODEDIRECTOR_H_H_HEAD__FILE__
