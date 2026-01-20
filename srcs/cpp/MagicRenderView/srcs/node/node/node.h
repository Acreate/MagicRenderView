#ifndef NODE_H_H_HEAD__FILE__
#define NODE_H_H_HEAD__FILE__

#include <QWidget>
#include <qpen.h>
#include <typeinfo>

#include <define/nodeFrinedClass.h>

/// @brief 标记节点名称（建议使用：[功能]/[类型]/[动作]）
/// @param _Type_Name 名称
#define Def_Interface_NodeTypeName( _Type_Name ) public: static QString getStaticNodeTypeName( ) { return _Type_Name; } virtual QString getVirtualNodeTypeName( ) const { return _Type_Name; }

/// @brief 标记节点名称（建议使用：[功能]/[类型]/[动作]）
/// @param _Type_Name 名称
#define Def_Extend_NodeTypeName( _Type_Name ) public: static QString getStaticNodeTypeName( ) { return _Type_Name; }  QString getVirtualNodeTypeName( ) const override { return _Type_Name; }

class NodeAfterEffect;
namespace NodeEnum {
	enum class NodeStatusType;
	enum class NodeSelctType;
	enum class AdviseType;
	enum class ErrorType;
	enum class PortType;
	enum class NodeType;
}
class DynamicTypeOutputPort;
class DynamicTypeInputPort;
class NodeStyleTypePen;
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
	/// @brief 节点工具指针对象
	NodeTools *nodeToolsPtr;
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
	/// @brief 节点名称
	QString nodeTitleName;
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
	/// @brief 生成变量类型（仅在生成节点有效）
	QString generateTypeName;
	/// @brief 变量指向
	void *varPtr;
	/// @brief 初始化时候自动调用
	std::function< bool( MainWidget * ) > initExCallFunction;
	/// @brief 获取节点输出端口所依赖的节点（输出端口所链接的节点）
	std::vector< Node * > thisNodeOutputPortRefOtherNodeInputPortVector;
	/// @brief 依赖该节点输入端的所有节点（输入端所链接的节点）
	std::vector< Node * > otherNodeOutputPortRefThisNodeInputPortVector;
	/// @brief 特效组件
	NodeAfterEffect* nodeAfterEffect;
private:
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
	/// @brief 该窗口应该被 NodeInfoEditorDirector::getNodeInfoEditorWidget 调用，并且交由 NodeInfoEditorDirector 销毁
	/// @return 成功返回编辑窗口
	virtual NodeInfoWidget * getNodeEditorWidget( );
public:
	/// @brief 配置首次运行所需要的数据
	/// @return 失败返回 false
	virtual bool readyNodeRunData( ) { return true; }
	/// @brief 填充输入端口
	/// @param ndoe_run_start_data_time
	/// @param result_need_run_ref_node_vector 先于该节点运行的节点列表
	/// @param current_frame
	/// @return 失败返回 false
	virtual bool fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector, size_t current_frame ) {
		result_need_run_ref_node_vector = otherNodeOutputPortRefThisNodeInputPortVector;
		return true;
	}
	/// @brief 填充输出端口
	/// @param result_next_run_advise_node_vector 建议后运行节点列表
	/// @param ndoe_run_start_data_time
	/// @param current_frame
	/// @return 失败返回 false
	virtual bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
		result_next_run_advise_node_vector = thisNodeOutputPortRefOtherNodeInputPortVector;
		return true;
	}
	/// @brief 节点运行调用
	/// @return 失败返回 false
	virtual bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame );
public:
	~Node( ) override;
	Node( const QString &node_name );
	virtual bool initEx( MainWidget *parent );
	virtual NodeEnum::NodeSelctType getNodeSelctType( ) const;
	virtual void setNodeSelctType( NodeEnum::NodeSelctType node_selct_type );
	virtual NodeEnum::NodeStatusType getNodeStatusType( ) const;
	virtual void setNodeStatusType( NodeEnum::NodeStatusType node_status_type );
	/// @brief 获取节点输出端口所依赖的节点（输出端口所链接的节点）
	/// @return 依赖序列
	virtual const std::vector< Node * > & getThisNodeOutputPortRefOtherNodeInputPortVector( ) const { return thisNodeOutputPortRefOtherNodeInputPortVector; }
	/// @brief 依赖该节点输入端的所有节点（输入端所链接的节点）
	/// @return 依赖序列
	virtual const std::vector< Node * > & getOtherNodeOutputPortRefThisNodeInputPortVector( ) const { return otherNodeOutputPortRefThisNodeInputPortVector; }
	virtual bool hasRefInputNodeRef( InputPort *input_port ) const;
	virtual bool hasRefOutputNodeRef( OutputPort *output_port ) const;
	virtual InputPort * getInputPort( const QString &port_name ) const;
	virtual OutputPort * getOutputPort( const QString &port_name ) const;
	virtual bool updateLayout( );
	virtual NodeEnum::NodeType getNodeType( ) const = 0;
	virtual const QString & getNodeTitleName( ) const { return nodeTitleName; }
	virtual void setNodeTitleName( const QString &node_title_name );
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
	virtual int getNodeBorderWidth( ) const { return nodeBorderWidth; }
	virtual InputPort * getInputPort( const size_t &input_port_generate_code ) const;
	virtual OutputPort * getOutputPort( const size_t &output_port_generate_code ) const;
	virtual VarDirector * getVarDirector( ) const { return varDirector; }
protected:
	/// @brief 编辑窗口初始化时被动调用该函数
	/// @param release_ptr 释放窗口指针
	virtual bool initNodeInfoWidget( NodeInfoWidget *release_ptr ) { return false; }
	/// @brief 编辑窗口释放时被动调用该函数
	/// @param release_ptr 释放窗口指针
	virtual void releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) { }
	/// @brief 更新端口的生成代号
	/// @return 失败返回 false
	virtual bool updatePortGenerateCodes( );
	/// @brief 绑定端口信息
	/// @return 成功返回 true
	virtual bool bindPortInfo( );
	/// @brief 释放端口信息
	/// @return 成功返回 true
	virtual bool releasePortInfo( );
private:
	/// @brief 增加一个输入端口
	/// @param input_port 输入端
	/// @return 失败返回 false
	virtual bool appendInputPort( InputPort *input_port );
	/// @brief 增加一个输出端口
	/// @param output_port 输出端口
	/// @return 失败返回 false
	virtual bool appendOutputPort( OutputPort *output_port );
	/// @brief 增加一个输入端口
	/// @param input_port 输入端
	/// @return 失败返回 false
	virtual bool appendDynamicTypeInputPort( DynamicTypeInputPort *input_port );
	/// @brief 增加一个输出端口
	/// @param output_port 输出端口
	/// @return 失败返回 false
	virtual bool appendDynamicTypeOutputPort( DynamicTypeOutputPort *output_port );
	/// @brief 创建一个动态输入端口对象
	/// @param port_enum_type 端口类型
	/// @param input_port_name 端口名称
	/// @param input_port_var_name 端口输入类型
	/// @return 失败返回 nullptr
	virtual DynamicTypeInputPort * createDynamicTypeInputPort( const NodeEnum::PortType &port_enum_type, const QString &input_port_name, const QString &input_port_var_name );
	/// @brief 创建一个动态输入端口对象
	/// @param port_enum_type 端口类型
	/// @param input_port_name 端口名称
	/// @param input_port_var_type_info 端口输入类型
	/// @return 失败返回 nullptr
	virtual DynamicTypeInputPort * createDynamicTypeInputPort( const NodeEnum::PortType &port_enum_type, const QString &input_port_name, const std::type_info &input_port_var_type_info );
	/// @brief 释放一个动态输入端口对象
	/// @param delete_dynamic_type_input_port 释放指针对象
	/// @return 成功释放返回 true
	virtual bool releaseDynamicTypeInputPort( DynamicTypeInputPort *delete_dynamic_type_input_port );
	/// @brief 创建一个动态输出端口对象
	/// @param port_enum_type 端口类型
	/// @param output_port_name 端口名称 
	/// @param output_port_var_name 端口输出类型
	/// @return 失败返回 nullptr
	virtual DynamicTypeOutputPort * createDynamicTypeOutputPort( const NodeEnum::PortType &port_enum_type, const QString &output_port_name, const QString &output_port_var_name );
	/// @brief 创建一个动态输出端口对象
	/// @param port_enum_type 端口类型
	/// @param output_port_name 端口名称 
	/// @param output_port_var_type_info 端口输出类型
	/// @return 失败返回 nullptr
	virtual DynamicTypeOutputPort * createDynamicTypeOutputPort( const NodeEnum::PortType &port_enum_type, const QString &output_port_name, const type_info &output_port_var_type_info );
	/// @brief 释放一个动态输出端口对象
	/// @param delete_dynamic_type_output_port 释放指针对象
	/// @return 成功释放返回 true
	virtual bool releaseDynamicTypeOutputPort( DynamicTypeOutputPort *delete_dynamic_type_output_port );
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

	template< typename TOutputPortType >
		requires requires ( TOutputPortType *create_ptr, OutputPort *port ) {
			port = create_ptr;
		}
	bool appendOutputPortType( const QString &output_port_name, TOutputPortType *&result_output_port_ptr ) {
		TOutputPortType *resultPortPtr = new TOutputPortType( output_port_name );
		if( resultPortPtr == nullptr )
			return false;
		if( appendOutputPort( resultPortPtr ) == true ) {
			result_output_port_ptr = resultPortPtr;
			return true;
		}
		delete resultPortPtr;
		return false;
	}

	template< typename TCInputTypePort >
	bool appendDynamicOutputPortType( const NodeEnum::PortType &port_enum_type, const QString &output_port_name, DynamicTypeOutputPort *&result_output_port_ptr ) {
		result_output_port_ptr = createDynamicTypeOutputPort( port_enum_type, output_port_name, typeid( TCInputTypePort ) );
		if( result_output_port_ptr == nullptr )
			return false;
		if( appendDynamicTypeOutputPort( result_output_port_ptr ) == true )
			return true;
		releaseDynamicTypeOutputPort( result_output_port_ptr );
		return false;
	}

	template< typename TCInputTypePort, typename TCreateBindVar >
	bool appendDynamicOutputPortType( const NodeEnum::PortType &port_enum_type, const QString &output_port_name, DynamicTypeOutputPort *&result_output_port_ptr, TCreateBindVar *bind_port_var_ptr ) {
		result_output_port_ptr = createDynamicTypeOutputPort( port_enum_type, output_port_name, typeid( TCInputTypePort ) );
		if( result_output_port_ptr == nullptr )
			return false;
		if( appendDynamicTypeOutputPort( result_output_port_ptr ) == true ) {
			if( setVarInfo( result_output_port_ptr, bind_port_var_ptr ) == true )
				return true;
		}
		releaseDynamicTypeOutputPort( result_output_port_ptr );
		return false;
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
	template< typename TInputPortType >
		requires requires ( TInputPortType *create_ptr, InputPort *port ) {
			port = create_ptr;
		}
	bool appendInputPortType( const QString &output_port_name, TInputPortType *&result_input_port_ptr ) {
		TInputPortType *resultPortPtr = new TInputPortType( output_port_name );
		if( resultPortPtr == nullptr )
			return false;
		if( appendInputPort( resultPortPtr ) == true ) {
			result_input_port_ptr = resultPortPtr;
			return true;
		}
		delete resultPortPtr;
		return false;
	}
	template< typename TInputPortType, typename TCreateBindVar >
		requires requires ( TInputPortType *create_ptr, InputPort *port ) {
			port = create_ptr;
		}
	bool appendInputPortType( const QString &output_port_name, TInputPortType *&result_input_port_ptr, TCreateBindVar *bind_port_var_ptr ) {
		TInputPortType *resultPortPtr = new TInputPortType( output_port_name );
		if( resultPortPtr == nullptr )
			return false;
		if( appendInputPort( resultPortPtr ) == true ) {
			result_input_port_ptr = resultPortPtr;
			if( setVarInfo( resultPortPtr, bind_port_var_ptr ) == true )
				return true;
		}
		delete resultPortPtr;
		return false;
	}
	template< typename TCInputTypePort >
	bool appendDynamicInputPortType( const NodeEnum::PortType &port_enum_type, const QString &port_name, DynamicTypeInputPort *&result_ptr ) {
		result_ptr = createDynamicTypeInputPort( port_enum_type, port_name, typeid( TCInputTypePort ) );
		if( result_ptr == nullptr )
			return false;
		if( appendDynamicTypeInputPort( result_ptr ) == true )
			return true;
		releaseDynamicTypeInputPort( result_ptr );
		return false;
	}
	template< typename TCInputTypePort, typename TCreateBindVar >
	bool appendDynamicInputPortType( const NodeEnum::PortType &port_enum_type, const QString &port_name, DynamicTypeInputPort *&result_ptr, TCreateBindVar *bind_port_var_ptr ) {
		result_ptr = createDynamicTypeInputPort( port_enum_type, port_name, typeid( TCInputTypePort ) );
		if( result_ptr == nullptr )
			return false;
		if( appendDynamicTypeInputPort( result_ptr ) == true ) {
			if( setVarInfo( result_ptr, bind_port_var_ptr ) == true )
				return true;
		}
		releaseDynamicTypeInputPort( result_ptr );
		return false;
	}
protected:
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
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
