#ifndef NODE_H_H_HEAD__FILE__
#define NODE_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
#include <typeinfo>

#include <enums/nodeEnum.h>

#define Def_Satatic_NodeTypeName( _Type_Name ) static QString nodeTypeName( ) { return _Type_Name; }
class DrawNodeWidget;
class QHBoxLayout;
class QLabel;
class QVBoxLayout;
class SrackInfo;
class NodeRunFunctionTypeInfo;
class VarDirector;
class Application;
class NodePortLinkInfo;
class NodeRefLinkInfo;
class InputPort;
class OutputPort;
class NodeClickInfo;
class NodeDirector;
class Node : public QWidget {
	Q_OBJECT;
	friend class NodeDirector;
	friend class NodeStack;
	friend class NodeRefLinkInfo;
protected:
	using NodeFunctionResultType = void;
	using NodeFunctionType = std::function< NodeFunctionResultType( VarDirector * ) >;
protected:
	/// @brief app 实例
	Application *instancePtr;
	/// @brief app 实例中的变量管理角色
	VarDirector *varDirector;
	/// @brief app 实例中的节点管理角色
	NodeDirector *nodeDirector;
	/// @brief 当前节点的输入列表
	std::vector< InputPort * > inputPortVector;
	/// @brief 当前节点的输出列表
	std::vector< OutputPort * > outputPortVector;
	/// @brief 节点管理角色中派遣的节点引用信息对象指针
	NodeRefLinkInfo *nodeRefLinkInfoPtr;
	/// @brief 节点调用函数
	NodeFunctionType nodeFunction;
	/// @brief 节点名称
	QString nodeName;
	/// @brief 节点主要布局
	QVBoxLayout *mainLayout;
	/// @brief 节点标题管理窗口
	QWidget *titileWidget;
	/// @brief 节点标题管理布局
	QVBoxLayout *titileWidgetLayout;
	/// @brief 节点标题显示
	QLabel *titileLabel;
	/// @brief 节点链接管理窗口
	QWidget *connectWidget;
	/// @brief 节点链接布局
	QHBoxLayout *connectWidgetLayout;
	/// @brief 节点输入管理窗口
	QWidget *inputPortWidget;
	/// @brief 节点输入布局
	QVBoxLayout *inputPortWidgetLayout;
	/// @brief 节点输出管理窗口
	QWidget *outputPortWidget;
	/// @brief 节点输出布局
	QVBoxLayout *outputPortWidgetLayout;
	/// @brief 节点边缘
	int nodeBorderWidth;
public:
	~Node( ) override;
	Node( const QString &node_name );
	virtual bool init( DrawNodeWidget *parent );
	virtual InputPort * getInputPort( const QString &port_name ) const;
	virtual OutputPort * getOutputPort( const QString &port_name ) const;
	virtual const NodeRefLinkInfo & getNodeRefLinkInfoPtr( ) const { return *nodeRefLinkInfoPtr; }
	virtual bool updateLayout( );
	virtual NodeEnum::NodeType getNodeType( ) const = 0;
	virtual const QString & getNodeName( ) const { return nodeName; }
	virtual bool getPointInfo( const QPoint &point, NodeClickInfo &result_node_click_info );
	virtual bool hasInputPort( const InputPort *check_input_port ) const;
	virtual bool hasOutputPort( const OutputPort *check_output_port ) const;
	virtual const std::vector< InputPort * > & getInputPortVector( ) const { return inputPortVector; }
	virtual const std::vector< OutputPort * > & getOutputPortVector( ) const { return outputPortVector; }
protected:
	/// @brief 配置端口变量信息
	/// @param change_var_output_port 修改的输出端口
	/// @param var_type_name 变量名称
	/// @param var_type_varlue_ptr 变量值指针
	virtual void setPortVarInfo( OutputPort *change_var_output_port, const QString &var_type_name, void *var_type_varlue_ptr );
	/// @brief 配置端口变量信息
	/// @param change_var_input_port 修改的输入端口
	/// @param var_type_name 变量名称
	/// @param var_type_varlue_ptr 变量值指针
	virtual void setPortVarInfo( InputPort *change_var_input_port, const QString &var_type_name, void *var_type_varlue_ptr );
private:
	/// @brief 增加一个输入端口
	/// @param input_port 输入端
	/// @return 失败返回 false
	virtual bool appendInputPort( InputPort *input_port );
	/// @brief 增加一个输出端口
	/// @param output_port 输出端口
	/// @return 失败返回 false
	virtual bool appendOutputPort( OutputPort *output_port );
protected:
	template< typename TOutputPortType >
		requires requires ( TOutputPortType *create_ptr, OutputPort *port ) {
			port = create_ptr;
		}
	TOutputPortType * appendOutputPortType( const QString &output_port_name ) {
		TOutputPortType *resultPortPtr = new TOutputPortType( output_port_name );
		if( appendOutputPort( resultPortPtr ) == true )
			return resultPortPtr;
		delete resultPortPtr;
		return nullptr;
	}
	template< typename TInputPortType >
		requires requires ( TInputPortType *create_ptr, InputPort *port ) {
			port = create_ptr;
		}
	TInputPortType * appendInputPortType( const QString &output_port_name ) {
		TInputPortType *resultPortPtr = new TInputPortType( output_port_name );
		if( appendInputPort( resultPortPtr ) == true )
			return resultPortPtr;
		delete resultPortPtr;
		return nullptr;
	}
protected:
	void paintEvent( QPaintEvent *event ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "未实现" ) );
	// 信号
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_node 释放对象指针
	/// @param srack_info 信号行
	void release_node_signal( Node *release_node, const SrackInfo &srack_info );
	/// @brief 节点错误信号
	/// @param error_node 错误节点
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	/// @param srack_info 堆栈信息
	void error_run_node_signal( Node *error_node, NodeEnum::ErrorType error_type, const QString &error_msg, const SrackInfo &srack_info );
	/// @brief 建议节点信号
	/// @param advise_node 建议节点
	/// @param advise_type 建议类型
	/// @param advise_msg 建议消息
	/// @param srack_info 堆栈信息
	void advise_run_node_signal( Node *advise_node, NodeEnum::AdviseType advise_type, const QString &advise_msg, const SrackInfo &srack_info );
	/// @brief 节点完成运行信号
	/// @param finish_node 完成节点
	/// @param srack_info 堆栈信息
	void finish_run_node_signal( Node *finish_node, const SrackInfo &srack_info );
};

#endif // NODE_H_H_HEAD__FILE__
