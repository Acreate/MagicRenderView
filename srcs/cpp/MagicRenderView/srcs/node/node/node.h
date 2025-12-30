#ifndef NODE_H_H_HEAD__FILE__
#define NODE_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
#include <qpen.h>
#include <typeinfo>

#include <enums/nodeEnum.h>

#include <define/nodeFrinedClass.h>

#define Def_Interface_NodeTypeName( _Type_Name ) static QString getStaticNodeTypeName( ) { return _Type_Name; } virtual QString getVirtualNodeTypeName( ) { return _Type_Name; }
#define Def_Extend_NodeTypeName( _Type_Name ) static QString getStaticNodeTypeName( ) { return _Type_Name; }  QString getVirtualNodeTypeName( ) override { return _Type_Name; }
class NodeLinkLibInfo;
class NodeBuilderInfo;
class MainWidget;
class NodeInfoWidget;
class QHBoxLayout;
class QLabel;
class QVBoxLayout;
class SrackInfo;
class VarDirector;
class Application;
class InputPort;
class OutputPort;
class NodeClickInfo;
class NodeDirector;
class NodeRunInfo;
class Node : public QWidget {
	Q_OBJECT;
	NodeFrinedClass( );
protected:
	using NodeFunctionResultType = void;
	using NodeFunctionType = std::function< NodeFunctionResultType( VarDirector * ) >;
protected:
	uint64_t generateCode;
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
	/// @brief 节点信息显示菜单
	NodeInfoWidget *nodeInfoWidget;
	/// @brief 节点边缘
	int nodeBorderWidth;
	/// @brief 生成变量类型（仅在生成节点有效）
	QString generateTypeName;
	/// @brief 变量指向
	void *varPtr;
	/// @brief 当前风格
	NodeEnum::NodeStyleType nodeStyle;
	int penWidth;
	int doubleWidth;
	/// @brief 默认笔刷
	QPen nonePen;
	/// @brief 函数调用笔刷
	QPen callFunctionPen;
	/// @brief 创建笔刷
	QPen createPen;
	/// @brief 选中笔刷
	QPen selectActivePen;
	/// @brief 上一次选中笔刷
	QPen selectOldPen;
	/// @brief 输出引用笔刷
	QPen selectOutputRefPen;
	/// @brief 输入引用笔刷
	QPen selectInputRefPen;
	/// @brief 警告笔刷
	QPen warningPen;
	/// @brief 错误笔刷
	QPen errorPen;
	/// @brief 建议笔刷
	QPen advisPen;
	/// @brief 初始化时候自动调用
	std::function< bool( MainWidget * ) > initExCallFunction;
	/// @brief 绑定的编译对象
	NodeRunInfo *nodeRunInfo;
private:
	std::vector< Node * > refInputPortNode;
	std::vector< Node * > refOutputPortNode;
	/// @brief 链接信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	virtual void inputAddRef_Slot( InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 断开信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	virtual void inputDelRef_Slot( InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 链接信号
	/// @param output_port 输出端口
	/// @param ref_input_port 输入端口
	virtual void outputAddRef_Slot( OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 断开信号
	/// @param output_port 输出端口
	/// @param ref_input_port 输入端口
	virtual void outputDelRef_Slot( OutputPort *output_port, InputPort *ref_input_port );
protected:
	/// @brief 增加输入引用
	/// @param output_port
	/// @param output_port
	/// @param ref_input_port 输入端口
	/// @return 失败返回 false
	virtual bool emplaceBackRefInputPortNode( OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 删除输入引用
	/// @param output_port
	/// @param ref_input_port 输入端
	/// @return 失败返回 false
	virtual bool eraseRefInputPortNode( OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 增加输出引用
	/// @param input_port
	/// @param ref_output_port 输出端
	/// @return 失败返回 false
	virtual bool emplaceBackRefOutputPortNode( InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 删除输出引用
	/// @param input_port
	/// @param ref_output_port 输出端
	/// @return 失败返回 false
	virtual bool eraseRefOutputPortNode( InputPort *input_port, OutputPort *ref_output_port );
	virtual void releaseInputPortRefNode( Node *node );
	virtual void releaseOutputPortRefNode( Node *node );
	virtual void releaseAllInputPortRefNode( );
	virtual void releaseAllOutputPortRefNode( );
	virtual void releaseAllRefNode( );
protected:
	virtual bool init( MainWidget *parent );
	virtual NodeBuilderInfo * builderNodeBuilderInfo( ) {
		return nullptr;
	}
public:
	~Node( ) override;
	Node( const QString &node_name );
	virtual bool initEx( MainWidget *parent );
	virtual const std::vector< Node * > & getRefInputPortNode( ) const { return refInputPortNode; }
	virtual const std::vector< Node * > & getRefOutputPortNode( ) const { return refOutputPortNode; }
	virtual bool hasRefInputNodeRef( InputPort *input_port ) const;
	virtual bool hasRefOutputNodeRef( OutputPort *output_port ) const;
	virtual InputPort * getInputPort( const QString &port_name ) const;
	virtual OutputPort * getOutputPort( const QString &port_name ) const;
	virtual bool updateLayout( );
	virtual NodeEnum::NodeType getNodeType( ) const = 0;
	virtual const QString & getNodeName( ) const { return nodeName; }
	virtual bool getPointInfo( const QPoint &point, NodeClickInfo &result_node_click_info );
	virtual bool hasInputPort( const InputPort *check_input_port ) const;
	virtual bool hasOutputPort( const OutputPort *check_output_port ) const;
	virtual const std::vector< InputPort * > & getInputPortVector( ) const { return inputPortVector; }
	virtual const std::vector< OutputPort * > & getOutputPortVector( ) const { return outputPortVector; }
	virtual bool toUint8VectorData( std::vector< uint8_t > &result_vector_data );
	virtual bool formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count );
	virtual QString toQString( ) const;
	virtual const QString & getGenerateTypeName( ) const { return generateTypeName; }
	virtual void * getVarPtr( ) const { return varPtr; }
	virtual NodeEnum::NodeStyleType getNodeStyle( ) const { return nodeStyle; }
	virtual void setNodeStyle( NodeEnum::NodeStyleType node_style ) { nodeStyle = node_style; }
	virtual int getNodeBorderWidth( ) const { return nodeBorderWidth; }
	virtual InputPort * getInputPort( const size_t &input_port_generate_code ) const;
	virtual OutputPort * getOutputPort( const size_t &output_port_generate_code ) const;
protected:
	/// @brief 更新端口的生成代号
	/// @return 失败返回 false
	virtual bool updatePortGenerateCodes( );
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
	Def_Interface_NodeTypeName( Node::tr( "未实现" ) );
	// 信号
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_node 释放对象指针
	/// @param srack_info 信号行
	void release_node_signal( Node *release_node, const SrackInfo &srack_info );
	/// @brief 产生链接节点引用
	/// @param output_port_node 输出节点
	/// @param ref_input_port_node 输入节点
	void connect_ref_input_port_node_signal( Node *output_port_node, Node *ref_input_port_node );
	/// @brief 断开链接节点引用
	/// @param output_port 输出节点
	/// @param ref_input_port 输入节点
	void dis_connect_ref_input_port_node_signal( Node *output_port, Node *ref_input_port );
	/// @brief 产生链接节点引用
	/// @param input_port_node 输入节点
	/// @param ref_output_port 输出节点
	void connect_ref_output_port_node_signal( Node *input_port_node, Node *ref_output_port );
	/// @brief 断开链接节点引用
	/// @param input_port_node 输入节点
	/// @param ref_output_port 输出节点
	void dis_connect_ref_output_port_node_signal( Node *input_port_node, Node *ref_output_port );
	/// @brief 链接信号
	/// @param output_port 输出端
	/// @param ref_input_port 输入端
	void connect_output_port_signal( OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 断开信号
	/// @param output_port 输出端
	/// @param ref_input_port 输入端
	void dis_connect_output_port_signal( OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 链接信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void connect_input_port_signal( InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 断开信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void dis_connect_input_port_signal( InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 节点错误信号
	/// @param error_node 错误节点
	/// @param srack_info 堆栈信息
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	void error_run_node_signal( Node *error_node, const SrackInfo &srack_info, NodeEnum::ErrorType error_type, const QString &error_msg );
	/// @brief 建议节点信号
	/// @param advise_node 建议节点
	/// @param advise_msg 建议消息
	/// @param advise_type 建议类型
	/// @param srack_info 堆栈信息
	void advise_run_node_signal( Node *advise_node, const SrackInfo &srack_info, NodeEnum::AdviseType advise_type, const QString &advise_msg );
	/// @brief 节点完成运行信号
	/// @param finish_node 完成节点
	/// @param srack_info 堆栈信息
	void finish_run_node_signal( Node *finish_node, const SrackInfo &srack_info );
};

#endif // NODE_H_H_HEAD__FILE__
