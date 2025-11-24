#ifndef NODE_H_H_HEAD__FILE__
#define NODE_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "../../enums/nodeEnum.h"
#define Def_Satatic_NodeTypeName( _Type_Name ) static QString nodeTypeName( ) { return _Type_Name; }
class Node : public QWidget {
	Q_OBJECT;
public:
	Node( QWidget *parent, const Qt::WindowFlags &f );
	virtual bool init( QWidget *parent ) = 0;
public:
	Def_Satatic_NodeTypeName( Node::tr( "未实现" ) );
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
};

#endif // NODE_H_H_HEAD__FILE__
