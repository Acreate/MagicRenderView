#ifndef VARTYPE_H_H_HEAD__FILE__
#define VARTYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class NodeItemWidget;
class VarType : public QObject {
	Q_OBJECT
protected:
	QString unityTypeName;
	std_vector< std_shared_ptr< void > > varVector;
private:
	VarType( const QString &unity_type_name ) {
		unityTypeName = unity_type_name;
	}
	VarType( NodeItemWidget *parent = nullptr );

	static VarType * templateVarType( NodeItemWidget *parent, const QString &type_name );
public:
	template< typename TType_Name >
	static VarType * templateVarType( const NodeItemWidget *parent ) {
		return templateVarType( parent, typeid( TType_Name ).name( ) );
	}
public:
	/// @brief 获取数组个数
	/// @return 个数
	virtual size_t size( ) const {
		return varVector.size( );
	}
	/// @brief 获取元素类型名称
	/// @return 类型名称
	virtual const QString & getUnityTypeName( ) const {
		return unityTypeName;
	}
	/// @brief 获取类型转换之后的数据指针
	/// @tparam TType_Name 类型
	/// @return 无法匹配类型返回 nullptr
	template< typename TType_Name >
	TType_Name * data( ) const {
		if( typeid( TType_Name ).name( ) != unityTypeName )
			return nullptr;
		auto data = varVector.data( );
		return ( TType_Name * ) data;
	}
	/// @brief 获取指定下标位置的数据
	/// @tparam TType_Name 类型
	/// @param index 下标
	/// @param result_var 返回
	/// @return 成功返回 true，并且 index 下标位置值赋予 result_var 变量
	template< typename TType_Name >
	bool getIndex( const size_t &index, TType_Name *result_var ) const {
		if( typeid( TType_Name ).name( ) != unityTypeName )
			return false;
		size_t count = varVector.size( );
		if( count <= index )
			return false;
		auto data = varVector.data( );
		*result_var = *( TType_Name * ) data;
		return true;
	}

	/// @brief 设置指定下标位置的数据
	/// @tparam TType_Name 类型
	/// @param index 下标
	/// @param set_var 设置值
	/// @return 成功返回 true，并且 index 下标位置值改为 result_var 变量值
	template< typename TType_Name >
	bool setIndex( const size_t &index, const TType_Name &set_var ) {
		if( typeid( TType_Name ).name( ) != unityTypeName )
			return false;
		size_t count = varVector.size( );
		if( count <= index )
			return false;
		auto data = varVector.data( );
		*( ( TType_Name * ) data[ index ].get( ) ) = *set_var;
		return true;
	}

	/// @brief 获取指定下标位置的数据
	/// @tparam TType_Name 类型
	/// @param index 下标
	/// @param result_var 返回
	/// @param get_index 当前返回的下标
	/// @return 成功返回 true，并且 index 下标位置值赋予 result_var 变量
	template< typename TType_Name >
	bool getIndexEndBorder( const size_t &index, TType_Name *result_var, size_t &get_index ) const {
		if( typeid( TType_Name ).name( ) != unityTypeName )
			return false;
		get_index = varVector.size( );
		if( get_index <= index )
			get_index = get_index - 1;
		else
			get_index = index;
		*result_var = *( ( TType_Name * ) ( ( varVector.data( )[ get_index ] ).get( ) ) );
		return true;
	}
	/// @brief 获取指定下标位置的数据
	/// @tparam TType_Name 类型
	/// @param index 下标
	/// @param result_var 返回
	/// @return 成功返回 true，并且 index 下标位置值赋予 result_var 变量
	template< typename TType_Name >
	bool getIndexEndBorder( const size_t &index, TType_Name *result_var ) const {
		size_t result_index;
		return getIndexEndBorder( index, result_var, result_index );
	}
	/// @brief 配置边缘元素值
	/// @tparam TType_Name 类型
	/// @param index 配置下标
	/// @param set_var 配置的值
	/// @param get_index 真实配置下标
	/// @return 成功返回 true
	template< typename TType_Name >
	bool setIndexEndBorder( const size_t &index, const TType_Name &set_var, size_t &get_index ) {
		if( typeid( TType_Name ).name( ) != unityTypeName )
			return false;
		get_index = varVector.size( );
		if( get_index == 0 ) {
			TType_Name *appendU = new TType_Name( );
			*appendU = set_var;
			std_shared_ptr< void > emplace( appendU, [appendU] ( void *p ) {
				delete appendU;
			} );
			varVector.emplace_back( emplace );
			return get_index;
		} else if( get_index <= index )
			get_index = get_index - 1;
		else
			get_index = index;
		*( ( TType_Name * ) ( varVector.data( )[ get_index ] ).get( ) ) = set_var;
		return get_index;
	}
	/// @brief 配置边缘元素值
	/// @tparam TType_Name 类型
	/// @param index 配置下标
	/// @param set_var 配置的值
	/// @return 成功返回 true
	template< typename TType_Name >
	bool setIndexEndBorder( const size_t &index, const TType_Name &set_var ) {
		size_t setIndex;
		return setIndexEndBorder( index, set_var, setIndex );
	}
	template< typename TType_Name >
	void appendUnity( const TType_Name &emplace_var ) {
		if( typeid( TType_Name ).name( ) != unityTypeName )
			return;
		TType_Name *appendU = new TType_Name( );
		*appendU = emplace_var;
		std_shared_ptr< void > emplace( appendU, [appendU] ( void *p ) {
			delete appendU;
		} );
		varVector.emplace_back( emplace );
	}
	~VarType( ) override {
		emit deleteObjBefore( this );
		varVector.clear( );
	}
Q_SIGNALS:
	void deleteObjBefore( VarType *var_ptr );
};

#endif // VARTYPE_H_H_HEAD__FILE__
