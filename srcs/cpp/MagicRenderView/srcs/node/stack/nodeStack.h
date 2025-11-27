#ifndef NODESTACK_H_H_HEAD__FILE__
#define NODESTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../enums/nodeEnum.h"

class VarDirector;
class PrinterDirector;
class Application;
class QAction;
class Node;
class QMenu;
class NodeStack : public QObject {
	Q_OBJECT;
	friend class NodeDirector;
protected:
protected:
	virtual bool init( );
private:
	std::vector< std::pair< QString, std::function< Node *( ) > > > nodeGenerate;
	QMenu *mainMenu;
	std::vector< std::pair< std::vector< QString >, QAction * > > actions;
	std::vector< std::pair< std::vector< QString >, QMenu * > > subMenus;
protected:
	Application *instancePtr;
	PrinterDirector *printerDirector;
	VarDirector *nodeVarDirector;
protected:
	virtual bool appendNodeGenerateUnity( const QString &name, const std::function< Node *( ) > &generate_function );
public:
	NodeStack( VarDirector *node_var_director, QObject *parent = nullptr );
	void releaseMainMenu( );
	~NodeStack( ) override;
	virtual Node * createNode( const QString &node_type_name );
	virtual QMenu * getMainMenu( ) const { return mainMenu; }
Q_SIGNALS:
	/// @brief 成功创建节点信号
	/// @param create_name 节点名称
	void finish_create_signal( const QString &create_name );
	/// @brief 节点创建失败信号
	/// @param create_name 节点名称
	/// @param error_type_info 错误类型
	/// @param error_msg 失败信息
	void error_create_signal( const QString &create_name, NodeEnum::CreateType error_type_info, const QString &error_msg );
};

#endif // NODESTACK_H_H_HEAD__FILE__
