#ifndef VARTYPE_H_H_HEAD__FILE__
#define VARTYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

#include "../generate/binGenerate.h"

class NodeItemWidget;
class VarType : public QObject {
	Q_OBJECT
public:
	friend class VarTypeGenerate;
	friend class VarTypeGenerateItem;
protected:
	/// @brief 生成代码
	size_t generateCode;
	/// @brief 单元类型名称
	QString unityTypeName;
	/// @brief 单元变量存储序列
	std_vector< void * > varVector;
	/// @brief 单元创建器
	std_function< void *( ) > createFunction = nullptr;
	/// @brief 拷贝函数
	std_function< bool( void *, void * ) > copyFunction = nullptr;
	/// @brief 单元删除器
	std_function< void( void *delete_obj_ptr ) > releaseFunction = nullptr;
	/// @brief 单元序列化
	std_function< size_t( const void *, std_vector< uint8_t > & ) > unitySer = nullptr;
	/// @brief 单元反序列化
	std_function< void*( const uint8_t *source_data_ptr, const size_t &source_data_count, size_t &result_use_data_count ) > unitySerRes = nullptr;
private:
	VarType( const QString &unity_type_name ) {
		unityTypeName = unity_type_name;
	}
	VarType( QObject *parent = nullptr );
public:
	VarType( const VarType &other )
		: QObject( other.parent( ) ),
		generateCode( other.generateCode ),
		unityTypeName( other.unityTypeName ),
		createFunction( other.createFunction ),
		copyFunction( other.copyFunction ),
		releaseFunction( other.releaseFunction ),
		unitySer( other.unitySer ),
		unitySerRes( other.unitySerRes ) {

		if( createFunction == nullptr || copyFunction == nullptr )
			return;
		size_t count = other.varVector.size( );
		if( count == 0 )
			return;
		auto data = other.varVector.data( );
		varVector.resize( count );
		auto fillPtr = varVector.data( );
		for( size_t index = 0; index < count; ++index ) {
			auto ptr = createFunction( );
			copyFunction( ptr, data[ index ] );
			fillPtr[ index ] = ptr;
		}
	}
	VarType & operator=( const VarType &other ) {
		if( this == &other )
			return *this;
		setParent( other.parent( ) );
		generateCode = other.generateCode;
		unityTypeName = other.unityTypeName;
		releaseFunction = other.releaseFunction;
		unitySer = other.unitySer;
		unitySerRes = other.unitySerRes;
		createFunction = other.createFunction;
		copyFunction = other.copyFunction;

		auto fillPtr = varVector.data( );
		size_t count = varVector.size( );
		size_t index = 0;
		for( ; index < count; ++index )
			releaseFunction( fillPtr[ index ] );
		varVector.clear( );
		if( createFunction == nullptr || copyFunction == nullptr )
			return *this;
		count = other.varVector.size( );
		if( count == 0 )
			return *this;
		auto data = other.varVector.data( );
		varVector.resize( count );
		fillPtr = varVector.data( );
		for( index = 0; index < count; ++index ) {
			auto ptr = createFunction( );
			copyFunction( ptr, data[ index ] );
			fillPtr[ index ] = ptr;
		}
		return *this;
	}
private:
	template< typename TType_Name >
	bool init( ) {
		if( typeid( TType_Name ).name( ) != unityTypeName )
			return false;
		releaseFunction = [] ( void *p ) {
			delete ( TType_Name * ) p;
		};
		createFunction = []( )->void * { return new TType_Name( ); };
		copyFunction = [] ( void *left_ptr, void *right_ptr )->bool {
			*( TType_Name * ) left_ptr = *( TType_Name * ) right_ptr;
			return true;
		};
		unitySer = [] ( const void *p, std::vector< uint8_t > &vector ) ->size_t {
			return BinGenerate::toVectorBin< TType_Name >( *( ( const TType_Name * ) p ), vector );
		};
		unitySerRes = [this] ( const uint8_t *source_data_ptr, const size_t &source_data_count, size_t &result_use_data_count ) ->void * {
			TType_Name *result = ( TType_Name * ) createFunction( );
			result_use_data_count = BinGenerate::fillObjPtr< TType_Name >( result, source_data_ptr, source_data_count );
			if( result_use_data_count != 0 )
				return result;
			delete result;
			return nullptr;
		};
		return true;
	}
public:
	/// @brief 数据转换到二进制
	/// @return 二进制数据
	virtual std_vector< uint8_t > toBin( ) const;
	/// @brief 从二进制数据加载到该对象
	/// @param bin 二进制数据
	/// @return 使用数据量
	virtual size_t loadBin( const std_vector< uint8_t > &bin );
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
	TType_Name * const* data( ) const {
		auto name = typeid( TType_Name ).name( );
		if( name != unityTypeName )
			return nullptr;
		auto data = varVector.data( );
		return ( TType_Name * const* ) data;
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
		*result_var = **( ( ( TType_Name * const* ) data ) + index );
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
		*( ( ( TType_Name * const* ) data )[ index ] ) = *set_var;
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
		*result_var = **( ( ( TType_Name * const* ) varVector.data( ) ) + get_index );
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
			appendUnity< TType_Name >( set_var );
			return get_index;
		} else if( get_index <= index )
			get_index = get_index - 1;
		else
			get_index = index;
		**( ( ( TType_Name * const* ) varVector.data( ) ) + get_index ) = set_var;
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
		if( createFunction == nullptr )
			return;;
		if( typeid( TType_Name ).name( ) != unityTypeName )
			return;
		TType_Name *appendU = ( TType_Name * ) createFunction( );
		if( appendU == nullptr )
			return;
		*appendU = emplace_var;
		varVector.emplace_back( appendU );
	}
	virtual void appendUnity( const std::string &emplace_var ) {
		appendUnity< QString >( QString::fromStdString( emplace_var ) );
	}
	virtual void appendUnity( const std::wstring &emplace_var ) {
		appendUnity< QString >( QString::fromStdWString( emplace_var ) );
	}
	virtual void appendUnity( const char *emplace_var ) {
		appendUnity< QString >( emplace_var );
	}
	virtual void appendUnity( const wchar_t *emplace_var ) {
		appendUnity< QString >( QString::fromStdWString( emplace_var ) );
	}
	virtual void appendUnity( const QString &emplace_var ) {
		appendUnity< QString >( emplace_var );
	}
	~VarType( ) override {
		emit deleteObjBefore( this );
		auto ptr = varVector.data( );
		size_t count = varVector.size( );
		size_t index = 0;
		for( ; index < count; ++index )
			releaseFunction( ptr[ index ] );
		varVector.clear( );
	}
Q_SIGNALS:
	void deleteObjBefore( VarType *var_ptr );
};

#endif // VARTYPE_H_H_HEAD__FILE__
