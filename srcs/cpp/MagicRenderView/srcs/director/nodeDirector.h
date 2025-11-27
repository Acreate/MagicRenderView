#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <enums/nodeEnum.h>

class VarDirector;
class PrinterDirector;
class Node;
class NodeStack;
class QMenu;
class Application;
class NodeDirector : public QObject {
	Q_OBJECT;
private:
	friend class Application;
protected:
	QMenu *nodeCreateMenu;
	std::vector< NodeStack * > nodeStacks;
	Application *instancePtr;
	PrinterDirector *printerDirector;
	VarDirector *varDirector;
	VarDirector *nodeVarDirector;
public:
	NodeDirector( QObject *parent = nullptr );
	void releaseMenu( );
	~NodeDirector( ) override;
	virtual bool init( );
	virtual QMenu * getNodeCreateMenu( ) const { return nodeCreateMenu; }
	virtual Node * createNode( const QString &stack_name, const QString &node_type_name );
Q_SIGNALS:
	/// @brief 节点错误信号
	/// @param error_node 错误节点
	/// @param code_line 信号发生行号
	/// @param code_file_name 信号发生文件
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	void error_node_signal( Node *error_node, size_t code_line, const QString &code_file_name, NodeEnum::ErrorType error_type, const QString &error_msg );
	/// @brief 建议节点信号
	/// @param advise_node 建议节点
	/// @param code_line 信号发生行号
	/// @param code_file_name 信号发生文件
	/// @param advise_type 建议类型
	/// @param advise_msg 建议消息
	void advise_node_signal( Node *advise_node, size_t code_line, const QString &code_file_name, NodeEnum::AdviseType advise_type, const QString &advise_msg );
	/// @brief 节点完成运行信号
	/// @param finish_node 完成节点
	/// @param code_line 信号发生行号
	/// @param code_file_name 信号发生文件
	void finish_node_signal( Node *finish_node, size_t code_line, const QString &code_file_name );
	/// @brief 成功创建节点信号
	/// @param create_name 节点名称
	void finish_create_signal( const QString &create_name );
	/// @brief 节点创建失败信号
	/// @param create_name 节点名称
	/// @param error_type_info 错误类型
	/// @param error_msg 失败信息
	void error_create_signal( const QString &create_name, NodeEnum::CreateType error_type_info, const QString &error_msg );
};

#endif // NODEDIRECTOR_H_H_HEAD__FILE__
