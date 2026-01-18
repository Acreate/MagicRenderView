#ifndef NODETOOLS_H_H_HEAD__FILE__
#define NODETOOLS_H_H_HEAD__FILE__
#include <typeinfo>
#include <vector>
#include <QString>
// 在调用对应模版成员好时候，使用对应的头文件
// NodeTools::appendDynamicInputPortType<>
// #include <node/port/inputPort/dynamicTypeInputPort.h>
// NodeTools::appendDynamicOutputPortType<>
// #include <node/port/outputPort/dynamicTypeOutputPort.h>

class DynamicTypeInputPort;
class DynamicTypeOutputPort;
class VarDirector;
namespace NodeEnum {
	enum class PortType;
	enum class NodeType;
}
class Node;
class OutputPort;
class InputPort;
class NodeTools {
	friend class Node;
public:
	virtual ~NodeTools( ) = default;
protected:
	Node *nodePtr;
protected:
	NodeTools( Node *node_ptr )
		: nodePtr( node_ptr ) { }
public:
	virtual std::vector< InputPort * > * getRefPort( OutputPort *output_port );
	virtual const std::vector< InputPort * > * getRefPort( const OutputPort *output_port );
	virtual bool getRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector );
	virtual bool getFilterRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type );
	virtual bool getFilterNotRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type );
	virtual bool setVarInfo( OutputPort *output_port, void *new_par );
	virtual bool setVarInfo( DynamicTypeOutputPort *output_port, void *new_par );
	virtual bool setVarInfo( OutputPort *output_port, VarDirector *var_director, void *var_ptr );
	virtual bool setPortMultiple( OutputPort *output_port, bool multiple );
	virtual bool getVarDirector( OutputPort *output_port, VarDirector * &result_var_director, void *&result_var_ptr );
	virtual bool setVarDirector( OutputPort *output_port, VarDirector *var_director );
	virtual bool getVarInfo( OutputPort *output_port, Node * &result_input_port_node_parent, VarDirector * &result_var_director, void *&result_var_ptr );
	virtual bool getVarInfo( OutputPort *output_port_ptr, VarDirector *&result_var_director, void * &result_var_ptr );

	virtual std::vector< OutputPort * > * getRefPort( InputPort *input_port );
	virtual const std::vector< OutputPort * > * getRefPort( const InputPort *input_port );
	virtual bool getRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector );
	virtual bool getFilterRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type );
	virtual bool getFilterNotRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type );
	virtual bool setVarInfo( InputPort *input_port, void *new_par );
	virtual bool setVarInfo( DynamicTypeInputPort *input_port, void *new_par );
	virtual bool setVarInfo( InputPort *input_port, VarDirector *var_director, void *var_ptr );
	virtual bool setPortMultiple( InputPort *input_port, bool multiple );
	virtual bool setVarDirector( InputPort *input_port, VarDirector *var_director );
	virtual bool getVarDirector( InputPort *input_port, VarDirector * &result_var_director, void *&result_var_ptr ) const;
	virtual bool getVarInfo( InputPort *input_port, Node * &result_input_port_node_parent, VarDirector * &result_var_director, void *&result_var_ptr ) const;
	virtual bool getVarInfo( InputPort *input_port_ptr, VarDirector *&result_var_director, void * &result_var_ptr );
	// 名称
public:
	virtual bool getVirtualNormalPath( InputPort *input_port_ptr, QString &resul_normal_path );
	virtual bool getVirtualNormalPath( OutputPort *output_port_ptr, QString &resul_normal_path );
	virtual bool getStaticNormalPath( InputPort *input_port_ptr, QString &resul_normal_path );
	virtual bool getStaticNormalPath( OutputPort *output_port_ptr, QString &resul_normal_path );
	virtual bool getVirtualNormalPath( Node *node_ptr, QString &resul_normal_path );
	virtual bool getStaticNormalPath( Node *node_ptr, QString &resul_normal_path );

	virtual bool getVirtualNormalPathLastName( InputPort *input_port_ptr, QString &resul_normal_path );
	virtual bool getVirtualNormalPathLastName( OutputPort *output_port_ptr, QString &resul_normal_path );
	virtual bool getStaticNormalPathLsstName( InputPort *input_port_ptr, QString &resul_normal_path );
	virtual bool getStaticNormalPathLsstName( OutputPort *output_port_ptr, QString &resul_normal_path );
	virtual bool getVirtualNormalPathLastName( Node *node_ptr, QString &resul_normal_path );
	virtual bool getStaticNormalPathLsstName( Node *node_ptr, QString &resul_normal_path );
	// 重构宏
protected:
	/// @brief 生成一个对象，并且赋值到指针，如果成功，则绑定指针到端口
	/// @param bind_type_name 生成对象类型名称
	/// @param bind_output_port 绑定端口
	/// @param result_var_ptr 返回生成对象的指针
	/// @return 成功返回 true
	virtual bool bindPortVar( const QString &bind_type_name, OutputPort *bind_output_port, void * &result_var_ptr );
	/// @brief 生成一个对象，并且赋值到指针，如果成功，则绑定指针到端口
	/// @param bind_type_name 生成对象类型名称
	/// @param bind_output_port 绑定端口
	/// @param result_var_ptr 返回生成对象的指针
	/// @return 成功返回 true
	virtual bool bindPortVar( const QString &bind_type_name, DynamicTypeOutputPort *bind_output_port, void * &result_var_ptr );
	/// @brief 追加输出端口到目标节点当中
	/// @param append_output_port_target_node 追加的目标节点
	/// @param result_output_port 追加到末尾的输出端口
	/// @return 成功返回 true
	virtual bool appendOutputPortType( Node *append_output_port_target_node, OutputPort *result_output_port );
	/// @brief 追加输入端口到目标节点当中
	/// @param append_input_port_target_node 追加的目标节点
	/// @param result_input_port 追加到末尾的输入端口
	/// @return 成功返回 true
	virtual bool appendInputPortType( Node *append_input_port_target_node, DynamicTypeInputPort *result_input_port );
	/// @brief 追加输出端口到目标节点当中
	/// @param append_output_port_target_node 追加的目标节点
	/// @param result_output_port 追加到末尾的输出端口
	/// @return 成功返回 true
	virtual bool appendOutputPortType( Node *append_output_port_target_node, DynamicTypeOutputPort *result_output_port );
	/// @brief 追加输入端口到目标节点当中
	/// @param append_input_port_target_node 追加的目标节点
	/// @param result_input_port 追加到末尾的输入端口
	/// @return 成功返回 true
	virtual bool appendInputPortType( Node *append_input_port_target_node, InputPort *result_input_port );
	/// @brief 从节点当中获取正确的类型名称
	/// @param form_node_type_name 节点
	/// @param conver_type_name 原始的类型名称
	/// @param result_type_name 正确的类型名称
	/// @return 成功返回 true
	virtual bool getNodeTypeName( Node *form_node_type_name, const QString &conver_type_name, QString &result_type_name );

	/// @brief 创建动态输入端口
	/// @param dynamic_type_output_port_type_name 端口类型名称
	/// @param port_enum_type 端口类型
	/// @param name 端口名称
	/// @param dynamic_type_var_name 端口变量类型名称
	/// @param result_dynamic_type_output_port_ptr 创建端口返回
	/// @return 成功返回 true
	virtual bool createDynamicTypeOutputPort( const QString &dynamic_type_output_port_type_name, const NodeEnum::PortType &port_enum_type, const QString &name, const QString &dynamic_type_var_name, DynamicTypeOutputPort *&result_dynamic_type_output_port_ptr );
	/// @brief 创建动态输出端口
	/// @param dynamic_type_input_port_type_name 端口类型名称
	/// @param port_enum_type 端口类型
	/// @param name 端口名称
	/// @param dynamic_type_var_name 端口变量类型名称
	/// @param result_dynamic_type_input_port_ptr 创建端口返回
	/// @return 成功返回 true
	virtual bool createDynamicTypeInputPort( const QString &dynamic_type_input_port_type_name, const NodeEnum::PortType &port_enum_type, const QString &name, const QString &dynamic_type_var_name, DynamicTypeInputPort *&result_dynamic_type_input_port_ptr );
	/// @brief 获取变量的真实类型名称
	/// @param var_type_get_var_director 获取的管理类
	/// @param org_type_name 原始名称
	/// @param result_var_director_type_name 返回真实名称
	/// @return 失败返回 false
	virtual bool finVarDirectorTypeName( const VarDirector *var_type_get_var_director, const QString &org_type_name, QString &result_var_director_type_name );
	/// @brief 获取指针变量的真实名称
	/// @param var_type_get_var_director 获取的管理类
	/// @param find_var_ptr 指针变量
	/// @param result_var_director_type_name 返回真实名称
	/// @return 失败返回 false
	virtual bool finVarDirectorVarPtrTypeName( const VarDirector *var_type_get_var_director, const void *find_var_ptr, QString &result_var_director_type_name );
	/// @brief 获取变量的真实类型名称
	/// @param var_type_get_var_director 获取的管理类
	/// @param org_type_name 原始名称
	/// @param result_var_director_type_name 返回真实名称
	/// @return 失败返回 false
	virtual bool finVarDirectorTypeName( const VarDirector *var_type_get_var_director, const std::type_info &org_type_name, QString &result_var_director_type_name ) {
		return finVarDirectorTypeName( var_type_get_var_director, org_type_name.name( ), result_var_director_type_name );
	}
	// 重构宏
public:
	/// @brief 绑定一个对象到端口
	/// @tparam TCreateType 对象类型
	/// @param bind_output_port 绑定端口
	/// @param result_var_ptr 绑定对象指针，该对象由调用函数窗口，不需要调用者创建
	/// @return 失败返回 false
	template< typename TCreateType >
	bool bindPortVar( OutputPort *bind_output_port, TCreateType * &result_var_ptr ) {
		return bindPortVar( typeid( TCreateType ).name( ), bind_output_port, result_var_ptr );
	}
	/// @brief 追加一个输出端口类型到端口
	/// @tparam TCreateType 输出类型绑定的对象类型 
	/// @tparam TCreateOutputPort 创建的输出类型
	/// @param append_output_port_target_node 追加的节点
	/// @param out_put_port_name 端口名称
	/// @param result_bind_output_port 绑定端口
	/// @param result_var_ptr 返回的绑定端口对象指针
	/// @return 成功返回 true
	template< typename TCreateType, typename TCreateOutputPort, typename= std::enable_if_t< std::is_base_of_v< OutputPort, TCreateOutputPort > > >
	bool appendOutputPortType( Node *append_output_port_target_node, const QString &out_put_port_name, TCreateOutputPort *&result_bind_output_port, TCreateType * &result_var_ptr ) {
		result_bind_output_port = new TCreateOutputPort( out_put_port_name );
		if( result_bind_output_port == nullptr )
			return false;
		if( appendOutputPortType( append_output_port_target_node, result_bind_output_port ) == false ) {
			delete result_bind_output_port;
			result_bind_output_port = nullptr;
			return false;
		}

		void *converPtr;
		if( bindPortVar( typeid( TCreateType ).name( ), result_bind_output_port, converPtr ) == false ) {
			delete result_bind_output_port;
			result_bind_output_port = nullptr;
			return false;
		}
		result_var_ptr = ( TCreateType * ) converPtr;
		return true;
	}
	/// @brief 追加一个输出端口类型到端口
	/// @tparam TCreateOutputPort 创建的输出类型
	/// @param append_output_port_target_node 追加的节点
	/// @param out_put_port_name 端口名称
	/// @param result_bind_output_port 绑定端口
	/// @return 成功返回 true
	template< typename TCreateOutputPort, typename= std::enable_if_t< std::is_base_of_v< OutputPort, TCreateOutputPort > > >
	bool appendOutputPortType( Node *append_output_port_target_node, const QString &out_put_port_name, TCreateOutputPort *&result_bind_output_port ) {
		result_bind_output_port = new TCreateOutputPort( out_put_port_name );
		if( result_bind_output_port == nullptr )
			return false;
		if( appendOutputPortType( append_output_port_target_node, result_bind_output_port ) == true )
			return true;
		delete result_bind_output_port;
		result_bind_output_port = nullptr;
		return false;
	}
	/// @brief 节点追加一个输入接口
	/// @tparam TCreateInputPort 输入接口类型
	/// @param append_output_port_target_node 追加的节点
	/// @param out_put_port_name 输出端口名称
	/// @param result_bind_input_port 返回绑定端口的变量对象指针
	/// @return 失败返回 false
	template< typename TCreateInputPort, typename= std::enable_if_t< std::is_base_of_v< InputPort, TCreateInputPort > > >
	bool appendInputPortType( Node *append_output_port_target_node, const QString &out_put_port_name, TCreateInputPort *&result_bind_input_port ) {
		result_bind_input_port = new TCreateInputPort( out_put_port_name );
		if( result_bind_input_port == nullptr )
			return false;
		if( appendInputPortType( append_output_port_target_node, result_bind_input_port ) == true )
			return true;
		delete result_bind_input_port;
		result_bind_input_port = nullptr;
		return false;
	}

	/// @brief 追加一个输出端口类型到端口
	/// @tparam TCreateType 输出类型绑定的对象类型 
	/// @tparam TCreateOutputPort 创建的输出类型
	/// @param append_output_port_target_node 追加的节点
	/// @param port_enum_type 端口类型
	/// @param out_put_port_name 端口名称
	/// @param result_bind_output_port 绑定端口
	/// @return 成功返回 true
	template< typename TCreateType, typename TCreateOutputPort >
		requires requires ( DynamicTypeOutputPort *org_ptr, TCreateOutputPort *create_ptr ) {
			org_ptr = create_ptr;
		}
	bool appendDynamicOutputPortType( Node *append_output_port_target_node, const NodeEnum::PortType &port_enum_type, const QString &out_put_port_name, TCreateOutputPort *&result_bind_output_port ) {
		QString typeName = typeid( TCreateType ).name( );
		QString normalName;
		result_bind_output_port = nullptr;
		if( getNodeTypeName( append_output_port_target_node, typeName, normalName ) == false )
			return false;
		result_bind_output_port = new TCreateOutputPort( port_enum_type, out_put_port_name, normalName );
		if( result_bind_output_port == nullptr )
			return false;
		if( appendOutputPortType( append_output_port_target_node, result_bind_output_port ) == false ) {
			delete result_bind_output_port;
			result_bind_output_port = nullptr;
			return false;
		}
		return true;
	}

	/// @brief 追加一个输出端口类型到端口
	/// @tparam TCreateType 输出类型绑定的对象类型 
	/// @tparam TCreateOutputPort 创建的输出类型
	/// @param append_output_port_target_node 追加的节点
	/// @param port_enum_type 端口类型
	/// @param out_put_port_name 端口名称
	/// @param result_bind_output_port 绑定端口
	/// @param result_var_ptr 返回的绑定端口对象指针
	/// @return 成功返回 true
	template< typename TCreateType, typename TCreateOutputPort >
		requires requires ( DynamicTypeOutputPort *org_ptr, TCreateOutputPort *create_ptr ) {
			org_ptr = create_ptr;
		}
	bool appendDynamicOutputPortType( Node *append_output_port_target_node, const NodeEnum::PortType &port_enum_type, const QString &out_put_port_name, TCreateOutputPort *&result_bind_output_port, TCreateType * &result_var_ptr ) {
		QString typeName = typeid( TCreateType ).name( );
		QString normalName;
		result_bind_output_port = nullptr;
		if( getNodeTypeName( append_output_port_target_node, typeName, normalName ) == false )
			return false;
		result_bind_output_port = new TCreateOutputPort( port_enum_type, out_put_port_name, normalName );

		if( result_bind_output_port == nullptr )
			return false;
		if( appendOutputPortType( append_output_port_target_node, result_bind_output_port ) == false ) {
			delete result_bind_output_port;
			result_bind_output_port = nullptr;
			return false;
		}

		void *converPtr;
		typeName = typeid( TCreateType ).name( );
		if( bindPortVar( typeName, result_bind_output_port, converPtr ) == false ) {
			delete result_bind_output_port;
			result_bind_output_port = nullptr;
			return false;
		}
		result_var_ptr = ( TCreateType * ) converPtr;
		return true;
	}
	/// @brief 节点追加一个输入端口
	/// @tparam TCreateInputPort 输入端口绑定变量类型
	/// @tparam TInputPortType 输入端口类型
	/// @param append_output_port_target_node 追加的节点对象
	/// @param port_enum_type 端口类型
	/// @param name 端口名称
	/// @param result_bind_input_port 绑定的变量
	/// @return 成功返回 true
	template< typename TInputPortType, typename TCreateInputPort >
		requires requires ( DynamicTypeInputPort *org_ptr, TCreateInputPort *create_ptr ) {
			org_ptr = create_ptr;
		}
	bool appendDynamicInputPortType( Node *append_output_port_target_node, const NodeEnum::PortType &port_enum_type, const QString &name, TCreateInputPort *&result_bind_input_port ) {
		QString typeName = typeid( TInputPortType ).name( );
		QString normalName;
		result_bind_input_port = nullptr;
		if( getNodeTypeName( append_output_port_target_node, typeName, normalName ) == false )
			return false;

		result_bind_input_port = new TCreateInputPort( port_enum_type, name, normalName );
		if( result_bind_input_port == nullptr )
			return false;
		if( appendInputPortType( append_output_port_target_node, result_bind_input_port ) == false )
			return true;
		delete result_bind_input_port;
		result_bind_input_port = nullptr;
		return false;
	}

	/// @brief 追加一个输出端口类型到端口
	/// @tparam TCreateType 输出类型绑定的对象类型 
	/// @tparam TCreateOutputPort 创建的输出类型
	/// @param append_output_port_target_node 追加的节点
	/// @param port_enum_type 端口类型
	/// @param out_put_port_name 端口名称
	/// @param result_bind_output_port 绑定端口
	/// @return 成功返回 true
	template< typename TCreateType, typename TCreateOutputPort >
	bool appendDynamicOutputPortType( Node *append_output_port_target_node, const NodeEnum::PortType &port_enum_type, const QString &out_put_port_name, DynamicTypeOutputPort *&result_bind_output_port ) {
		QString typeName = typeid( TCreateType ).name( );
		QString normalName;
		result_bind_output_port = nullptr;
		if( getNodeTypeName( append_output_port_target_node, typeName, normalName ) == false )
			return false;
		if( createDynamicTypeOutputPort( typeid( TCreateOutputPort ).name( ), port_enum_type, out_put_port_name, normalName, result_bind_output_port ) == false )
			return false;
		if( appendOutputPortType( append_output_port_target_node, result_bind_output_port ) == false )
			return true;
		delete ( TCreateOutputPort * ) result_bind_output_port;
		result_bind_output_port = nullptr;
		return false;
	}

	/// @brief 追加一个输出端口类型到端口
	/// @tparam TCreateType 输出类型绑定的对象类型 
	/// @tparam TCreateOutputPort 创建的输出类型
	/// @param append_output_port_target_node 追加的节点
	/// @param port_enum_type 端口类型
	/// @param out_put_port_name 端口名称
	/// @param result_bind_output_port 绑定端口
	/// @param result_var_ptr 返回的绑定端口对象指针
	/// @return 成功返回 true
	template< typename TCreateType, typename TCreateOutputPort >
	bool appendDynamicOutputPortType( Node *append_output_port_target_node, const NodeEnum::PortType &port_enum_type, const QString &out_put_port_name, DynamicTypeOutputPort *&result_bind_output_port, DynamicTypeOutputPort * &result_var_ptr ) {
		QString typeName = typeid( TCreateType ).name( );
		QString normalName;
		result_bind_output_port = nullptr;
		if( getNodeTypeName( append_output_port_target_node, typeName, normalName ) == false )
			return false;

		if( createDynamicTypeOutputPort( typeid( TCreateType ).name( ), port_enum_type, out_put_port_name, normalName, result_bind_output_port ) == false )
			return false;
		if( appendOutputPortType( append_output_port_target_node, result_bind_output_port ) == false ) {
			delete ( TCreateType * ) result_bind_output_port;
			result_bind_output_port = nullptr;
			return false;
		}

		void *converPtr;
		typeName = typeid( TCreateType ).name( );
		if( bindPortVar( typeName, result_bind_output_port, converPtr ) == false ) {
			delete ( TCreateOutputPort * ) result_bind_output_port;
			result_bind_output_port = nullptr;
			return false;
		}
		result_var_ptr = ( TCreateType * ) converPtr;
		return true;
	}
	/// @brief 节点追加一个输入端口
	/// @tparam TCreateInputPort 输入端口绑定变量类型
	/// @tparam TInputPortType 输入端口类型
	/// @param append_output_port_target_node 追加的节点对象
	/// @param port_enum_type 端口类型
	/// @param name 端口名称
	/// @param result_bind_input_port 绑定的变量
	/// @return 成功返回 true
	template< typename TInputPortType, typename TCreateInputPort >
	bool appendDynamicInputPortType( Node *append_output_port_target_node, const NodeEnum::PortType &port_enum_type, const QString &name, DynamicTypeInputPort *&result_bind_input_port ) {
		QString typeName = typeid( TInputPortType ).name( );
		QString normalName;
		result_bind_input_port = nullptr;
		if( getNodeTypeName( append_output_port_target_node, typeName, normalName ) == false )
			return false;
		if( createDynamicTypeInputPort( typeid( TCreateInputPort ).name( ), port_enum_type, name, normalName, result_bind_input_port ) == false )
			return false;
		if( appendInputPortType( append_output_port_target_node, result_bind_input_port ) == false )
			return true;
		delete ( TCreateInputPort * ) result_bind_input_port;
		result_bind_input_port = nullptr;
		return false;
	}
	// 类型
public:
	template< typename TCreateType, typename TPortType >
		requires requires ( TPortType *port_type, OutputPort *output_port ) {
			output_port = port_type;
		}
	bool cast_ptr_port_var_ptr( TPortType *get_port, TCreateType * &result_ptr ) {
		VarDirector *varDirectorPtr;
		void *varPtr;
		if( getVarInfo( get_port, varDirectorPtr, varPtr ) == false )
			return false;
		QString converTypeName;
		QString name = typeid( TCreateType ).name( );
		if( finVarDirectorTypeName( varDirectorPtr, name, converTypeName ) == false )
			return false;

		// 检查是否存在指定的类型
		if( finVarDirectorVarPtrTypeName( varDirectorPtr, varPtr, name ) == false )
			return false;
		if( name != converTypeName )
			return false;
		// 同一类型返回转换后的类型对象指针
		result_ptr = ( TCreateType * ) varPtr;
		return true;
	}
	template< typename TCreateType, typename TPortType >
		requires requires ( TPortType *port_type, OutputPort *output_port ) {
			output_port = port_type;
		}
	bool cast_ptr_ref_first_port_var_ptr( TPortType *get_port, TCreateType * &result_ptr ) {
		VarDirector *varDirectorPtr;
		void *varPtr;
		auto refPort = getRefPort( get_port );
		if( refPort.size( ) == 0 )
			return false;
		auto firstPort = refPort.data( )[ 0 ];
		if( getVarInfo( firstPort, varDirectorPtr, varPtr ) == false )
			return false;
		QString converTypeName;
		QString name = typeid( TCreateType ).name( );
		if( finVarDirectorTypeName( varDirectorPtr, name, converTypeName ) == false )
			return false;

		// 检查是否存在指定的类型
		if( finVarDirectorVarPtrTypeName( varDirectorPtr, varPtr, name ) == false )
			return false;
		if( name != converTypeName )
			return false;
		// 同一类型返回转换后的类型对象指针
		result_ptr = ( TCreateType * ) varPtr;
		return true;
	}

	template< typename TCreateType, typename TPortType >
		requires requires ( TPortType *port_type, InputPort *input_port_ptr ) {
			input_port_ptr = port_type ;
		}
	bool cast_ptr_port_var_ptr( TPortType *get_port, TCreateType * &result_ptr ) {
		VarDirector *varDirectorPtr;
		void *varPtr;
		if( getVarInfo( get_port, varDirectorPtr, varPtr ) == false )
			return false;
		QString converTypeName;
		QString name = typeid( TCreateType ).name( );
		if( finVarDirectorTypeName( varDirectorPtr, name, converTypeName ) == false )
			return false;

		// 检查是否存在指定的类型
		if( finVarDirectorVarPtrTypeName( varDirectorPtr, varPtr, name ) == false )
			return false;
		if( name != converTypeName )
			return false;
		// 同一类型返回转换后的类型对象指针
		result_ptr = ( TCreateType * ) varPtr;
		return true;
	}
	template< typename TCreateType, typename TPortType >
		requires requires ( TPortType *port_type, InputPort *input_port_ptr ) {
			input_port_ptr = port_type ;
		}
	bool cast_ptr_ref_first_port_var_ptr( TPortType *get_port, TCreateType * &result_ptr ) {
		VarDirector *varDirectorPtr;
		void *varPtr;
		auto refPort = getRefPort( get_port );
		if( refPort.size( ) == 0 )
			return false;
		auto firstPort = refPort.data( )[ 0 ];
		if( getVarInfo( firstPort, varDirectorPtr, varPtr ) == false )
			return false;
		QString converTypeName;
		QString name = typeid( TCreateType ).name( );
		if( finVarDirectorTypeName( varDirectorPtr, name, converTypeName ) == false )
			return false;

		// 检查是否存在指定的类型
		if( finVarDirectorVarPtrTypeName( varDirectorPtr, varPtr, name ) == false )
			return false;
		if( name != converTypeName )
			return false;
		// 同一类型返回转换后的类型对象指针
		result_ptr = ( TCreateType * ) varPtr;
		return true;
	}
};

#endif // NODETOOLS_H_H_HEAD__FILE__
