#ifndef TYPE_ALIAS_H_H_HEAD__FILE__
#define TYPE_ALIAS_H_H_HEAD__FILE__
#pragma once

#include "cmake_value_to_c_cpp_header_env.h"
#include <vector>
#include <memory>
#include <QString>
#include <set>
#include <QEvent>
#include <mutex>

#include <QObject>

/// @brief 事件类型
using t_event_type = decltype(QEvent::Type::AcceptDropsChange);

template< typename TPtrType >
using std_shared_ptr = std::shared_ptr< TPtrType >;

/// @brief 映射容器
/// @tparam TKey 映射关键字
/// @tparam TValue 映射值
template< typename TKey, typename TValue >
using std_pairt = std::pair< TKey, TValue >;
/// @brief 映射序列容器
/// @tparam TKey 映射关键字
/// @tparam TValue 映射值
template< typename TKey, typename TValue >
using std_vector_pairt = std::vector< std_pairt< TKey, TValue > >;

/// @brief 容器别名
/// @tparam TValue 元素类型 
template< typename TValue >
using std_vector = std::vector< TValue >;

/// @brief 列表别名
/// @tparam TValue 元素类型 
template< typename TValue >
using std_list = std::list< TValue >;

/// @brief 容器别名
/// @tparam TValue 元素类型 
template< typename TValue >
using std_vector_unity_shared = std::vector< std_shared_ptr< TValue > >;

/// @brief 共享指针容器指针对象
/// @tparam TValue 元素类型 
template< typename TValue >
using std_vector_shared_unity_shared = std_shared_ptr< std_vector_unity_shared< TValue > >;

/// @brief 红黑树别名
/// @tparam TValue 元素类型 
template< typename TValue >
using std_set = std::set< TValue >;
/// @brief 属性功能函数
template< typename TFunction >
using std_function = std::function< TFunction >;
/// @brief 锁
using std_mutex = std::mutex;
/// @brief 自动锁
using std_lock_grad_mutex = std::lock_guard< std_mutex >;
/// @brief 创建函数
using createFunction = std_function< void *( ) >;
/// @brief 释放函数
using releaseFunction = std_function< bool( void *p ) >;

/// @brief 比较运算符
/// @param righth_type_ 比较数
#define DEF_EQU_OPERATOR_CALCULATE( left_type_, righth_type_) \
	public:\
		friend bool operator ==(  righth_type_ left_type_var_ref,  left_type_ right_type_var_ref ){ return right_type_var_ref == left_type_var_ref ;}\
		friend bool operator !=(  righth_type_ left_type_var_ref,  left_type_ right_type_var_ref ){ return !( right_type_var_ref == left_type_var_ref );}\
		bool operator !=( righth_type_ right_type_var_ref )const{ return !(*this == right_type_var_ref );}\
		bool operator ==( righth_type_ right_type_var_ref )const

/// @brief 赋值计算操作符重载
/// @param left_type_ 左值
/// @param righth_type_ 右值
#define DEF_ASSIGN_OPERATOR_CALCULATE( left_type_, righth_type_) \
	public:\
		virtual	left_type_ operator =(const righth_type_ right_type_var_ref );\
		virtual	bool operator ==(const righth_type_ right_type_var_ref );\
		virtual	bool operator !=(const righth_type_ right_type_var_ref ){\
			return this->operator==( right_type_var_ref ) == false;\
		}\
		virtual	bool operator >(const righth_type_ right_type_var_ref );\
		virtual	bool operator <(const righth_type_ right_type_var_ref );\
		virtual	bool operator <=(const righth_type_ right_type_var_ref );\
		virtual	bool operator >=(const righth_type_ right_type_var_ref )

/// @brief 字符串的赋值计算操作符重载
/// @param left_type_ 左值
/// @param righth_type_ 右值
#define DEF_ASSIGN_OPERATOR_REF_AND_PTR_AT_STR_CALCULATE( left_type_) \
public:\
	virtual left_type_ * operator =( const std::wstring &right_type_var_ref ) {		QString var = QString::fromStdWString( right_type_var_ref );		return operator=( var );	}\
	virtual left_type_ * operator =( const std::string &right_type_var_ref ) {		QString var = QString::fromStdString( right_type_var_ref );		return operator=( var );	}\
	virtual left_type_ * operator =( const QString &right_type_var_ref );\
	virtual left_type_ * operator =( const QString *right_type_var_ref ){	 return this->operator=( *right_type_var_ref );}\
	virtual left_type_ * operator =( const std::wstring *right_type_var_ref ){	 return this->operator=( *right_type_var_ref );}\
	virtual left_type_ * operator =( const std::string *right_type_var_ref ){ return operator=( *right_type_var_ref );}\
	virtual bool operator ==( const std::wstring *right_type_var_ref ) { return this->operator==( *right_type_var_ref ); }\
	virtual bool operator !=( const std::wstring *right_type_var_ref ) { return this->operator!=( *right_type_var_ref ); }\
	virtual bool operator >( const std::wstring *right_type_var_ref ) { return this->operator>( *right_type_var_ref ); }\
	virtual bool operator <( const std::wstring *right_type_var_ref ) { return this->operator<( *right_type_var_ref ); }\
	virtual bool operator <=( const std::wstring *right_type_var_ref ) { return this->operator<=( *right_type_var_ref ); }\
	virtual bool operator >=( const std::wstring *right_type_var_ref ) { return this->operator>=( *right_type_var_ref ); }\
	virtual bool operator ==( const std::string *right_type_var_ref ) { return this->operator==( *right_type_var_ref ); }\
	virtual bool operator !=( const std::string *right_type_var_ref ) { return this->operator!=( *right_type_var_ref ); }\
	virtual bool operator >( const std::string *right_type_var_ref ) { return this->operator>( *right_type_var_ref ); }\
	virtual bool operator <( const std::string *right_type_var_ref ) { return this->operator<( *right_type_var_ref ); }\
	virtual bool operator <=( const std::string *right_type_var_ref ) { return this->operator<=( *right_type_var_ref ); }\
	virtual bool operator >=( const std::string *right_type_var_ref ) { return this->operator>=( *right_type_var_ref ); }\
	virtual bool operator ==( const std::wstring &right_type_var_ref ) { QString var = QString::fromStdWString( right_type_var_ref ); return operator==( var );}\
	virtual bool operator !=( const std::wstring &right_type_var_ref ) { return this->operator==( right_type_var_ref ) == false; }\
	virtual bool operator >( const std::wstring &right_type_var_ref ) {		QString var = QString::fromStdWString( right_type_var_ref );		return operator>( var );	}\
	virtual bool operator <( const std::wstring &right_type_var_ref ) {		QString var = QString::fromStdWString( right_type_var_ref );		return operator<( var );	}\
	virtual bool operator <=( const std::wstring &right_type_var_ref ) {		QString var = QString::fromStdWString( right_type_var_ref );		return operator<=( var );	}\
	virtual bool operator >=( const std::wstring &right_type_var_ref ) {		QString var = QString::fromStdWString( right_type_var_ref );		return operator>=( var );	}\
	virtual bool operator ==( const QString *right_type_var_ref ) { return this->operator==( *right_type_var_ref ); }\
	virtual bool operator !=( const QString *right_type_var_ref ) { return this->operator!=( *right_type_var_ref ); }\
	virtual bool operator >( const QString *right_type_var_ref ) { return this->operator>( *right_type_var_ref ); }\
	virtual bool operator <( const QString *right_type_var_ref ) { return this->operator<( *right_type_var_ref ); }\
	virtual bool operator <=( const QString *right_type_var_ref ) { return this->operator<=( *right_type_var_ref ); }\
	virtual bool operator >=( const QString *right_type_var_ref ) { return this->operator>=( *right_type_var_ref ); };\
	virtual bool operator ==( const std::string &right_type_var_ref ) {		QString var = QString::fromStdString( right_type_var_ref );		return operator==( var );	}\
	virtual bool operator !=( const std::string &right_type_var_ref ) { return this->operator==( right_type_var_ref ) == false; }\
	virtual bool operator >( const std::string &right_type_var_ref ) {		QString var = QString::fromStdString( right_type_var_ref );		return operator>( var );	}\
	virtual bool operator <( const std::string &right_type_var_ref ) {QString var = QString::fromStdString( right_type_var_ref );return operator< (var);}\
	virtual bool operator <=( const std::string &right_type_var_ref ) {	QString var = QString::fromStdString( right_type_var_ref );	return operator<=( var );}\
	virtual bool operator >=( const std::string &right_type_var_ref ) {	QString var = QString::fromStdString( right_type_var_ref );	return operator>=( var );}\
	virtual bool operator !=( const QString &right_type_var_ref ){return !operator==( right_type_var_ref );}\
	virtual bool operator ==( const QString &right_type_var_ref );\
	virtual bool operator >( const QString &right_type_var_ref );\
	virtual bool operator <( const QString &right_type_var_ref );\
	virtual bool operator <=( const QString &right_type_var_ref );\
	virtual bool operator >=( const QString &right_type_var_ref )

#define DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( left_type_, righth_type_) \
	public:\
		virtual	bool operator ==(const righth_type_* right_type_var_ref ){\
			return this->operator==( right_type_var_ref );\
		}\
		virtual	bool operator !=(const righth_type_* right_type_var_ref ){\
			return this->operator!=( right_type_var_ref );\
		}\
		virtual	bool operator >(const righth_type_ *right_type_var_ref ){\
			return this->operator>( right_type_var_ref );\
		}\
		virtual	bool operator <(const righth_type_* right_type_var_ref ){\
			return this->operator<( right_type_var_ref );\
		}\
		virtual	bool operator <=(const righth_type_* right_type_var_ref ){\
			return this->operator<=( right_type_var_ref );\
		}\
		virtual	bool operator >=(const righth_type_* right_type_var_ref){\
			return this->operator>=( *right_type_var_ref );\
		};\
	DEF_ASSIGN_OPERATOR_CALCULATE( left_type_*, righth_type_&)

/// @brief 用于定义四则运算与 = 赋值
/// @param left_type_ 做操作符
/// @param righth_type_ 有操作符
#define DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( left_type_, righth_type_, result_type_ ) \
	public:\
		friend result_type_ operator +( left_type_ left_type_var_ref, righth_type_ right_type_var_ref ); \
		friend result_type_ operator -( left_type_ left_type_var_ref, righth_type_ right_type_var_ref ); \
		friend result_type_ operator *( left_type_ left_type_var_ref, righth_type_ right_type_var_ref ); \
		friend result_type_ operator /( left_type_ left_type_var_ref, righth_type_ right_type_var_ref )

/// @brief 用于定义四则运算与 = 赋值
/// @param left_type_ 做操作符
/// @param righth_type_ 有操作符
#define DEF_FRIEND_OPERATOR_CALCULATE( left_type_, righth_type_ ) \
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT(const left_type_&,const righth_type_&, left_type_ )

/// @brief 用于定义四则运算与 = 赋值
/// @param left_type_ 做操作符
/// @param righth_type_ 有操作符
#define DEF_OPERATOR_CALCULATE( left_type_, righth_type_) \
	DEF_FRIEND_OPERATOR_CALCULATE(left_type_, righth_type_); \
	DEF_ASSIGN_OPERATOR_CALCULATE(left_type_&, righth_type_&)

/// @brief 定义字符串的四则运算
/// @param _left_type 重载类型
#define STR_CALCU_OPERATOR( _left_type , result_type_) \
public:\
	friend result_type_ operator +( _left_type left_type_var_ref,const std::string* right_type_var_ref ) { \
		return operator+( left_type_var_ref, *right_type_var_ref  ); \
	}\
	friend result_type_ operator -( _left_type left_type_var_ref,const std::string* right_type_var_ref ) {\
		return operator-( left_type_var_ref, *right_type_var_ref  );\
	}\
	friend result_type_ operator *( _left_type left_type_var_ref,const std::string* right_type_var_ref ) {\
		return operator*( left_type_var_ref, *right_type_var_ref  ); \
	}\
	friend result_type_ operator /( _left_type left_type_var_ref,const std::string* right_type_var_ref ) {\
		return operator/( left_type_var_ref, *right_type_var_ref );\
	}\
	friend result_type_ operator +( _left_type left_type_var_ref,const std::string& right_type_var_ref ) {\
		QString str = QString::fromStdString( right_type_var_ref );\
		return operator+( left_type_var_ref, str );\
	}\
	friend result_type_ operator -( _left_type left_type_var_ref,const std::string& right_type_var_ref ) {\
		QString str = QString::fromStdString( right_type_var_ref );\
		return operator-( left_type_var_ref, str );\
	}\
	friend result_type_ operator *( _left_type left_type_var_ref,const std::string& right_type_var_ref ) {\
		QString str = QString::fromStdString( right_type_var_ref );\
		return operator*( left_type_var_ref, str );\
	}\
	friend result_type_ operator /( _left_type left_type_var_ref,const std::string& right_type_var_ref ) {\
		QString str = QString::fromStdString( right_type_var_ref );\
		return operator/( left_type_var_ref, str );\
	}\
	friend result_type_ operator +( _left_type left_type_var_ref,const std::wstring* right_type_var_ref ) { \
		return operator+( left_type_var_ref, *right_type_var_ref  ); \
	}\
	friend result_type_ operator -( _left_type left_type_var_ref,const std::wstring* right_type_var_ref ) {\
		return operator-( left_type_var_ref, *right_type_var_ref  );\
	}\
	friend result_type_ operator *( _left_type left_type_var_ref,const std::wstring* right_type_var_ref ) {\
		return operator*( left_type_var_ref, *right_type_var_ref  ); \
	}\
	friend result_type_ operator /( _left_type left_type_var_ref,const std::wstring* right_type_var_ref ) {\
		return operator/( left_type_var_ref, *right_type_var_ref );\
	}\
	friend result_type_ operator +( _left_type left_type_var_ref,const std::wstring& right_type_var_ref ) {\
		QString str = QString::fromStdWString( right_type_var_ref );\
		return operator+( left_type_var_ref, str );\
	}\
	friend result_type_ operator -( _left_type left_type_var_ref,const std::wstring& right_type_var_ref ) {\
		QString str = QString::fromStdWString( right_type_var_ref );\
		return operator-( left_type_var_ref, str );\
	}\
	friend result_type_ operator *( _left_type left_type_var_ref,const std::wstring& right_type_var_ref ) {\
		QString str = QString::fromStdWString( right_type_var_ref );\
		return operator*( left_type_var_ref, str );\
	}\
	friend result_type_ operator /( _left_type left_type_var_ref,const std::wstring& right_type_var_ref ) {\
		QString str = QString::fromStdWString( right_type_var_ref );\
		return operator/( left_type_var_ref, str );\
	}\
	friend result_type_ operator +( _left_type left_type_var_ref, const QString *right_type_var_ref ){ return operator+(left_type_var_ref,*right_type_var_ref); }\
	friend result_type_ operator -(  _left_type left_type_var_ref, const QString *right_type_var_ref ){ return operator-(left_type_var_ref,*right_type_var_ref); }\
	friend result_type_ operator *( _left_type left_type_var_ref, const QString *right_type_var_ref ){ return operator*(left_type_var_ref,*right_type_var_ref); }\
	friend result_type_ operator /( _left_type left_type_var_ref,  const QString *right_type_var_ref ){ return operator/(left_type_var_ref,*right_type_var_ref); }\
	friend result_type_ operator +( _left_type left_type_var_ref,  const QString &right_type_var_ref );\
	friend result_type_ operator -( _left_type left_type_var_ref,  const QString &right_type_var_ref );\
	friend result_type_ operator *( _left_type left_type_var_ref, const QString &right_type_var_ref );\
	friend result_type_ operator /( _left_type left_type_var_ref,  const QString &right_type_var_ref )

#ifdef Def_First_StaticMetaInfo
#undef Def_First_StaticMetaInfo
#endif

#define Def_First_StaticMetaInfo(  ) \
public: \
	static QString getStaticMetaObjectName( ); \
	static QString getStaticMetaObjectDir( ); \
	static QString getStaticMetaObjectPathName( ); \
public: \
	virtual QString getMetaObjectName( ) const; \
	virtual QString getMetaObjectDir( ) const;\
	virtual QString getMetaObjectPathName( ) const

#ifdef Def_Last_StaticMetaInfo
#undef Def_Last_StaticMetaInfo
#endif

#define Def_Last_StaticMetaInfo(  ) \
public: \
	static QString getStaticMetaObjectName( ); \
	static QString getStaticMetaObjectDir( ); \
	static QString getStaticMetaObjectPathName( ); \
public: \
	QString getMetaObjectName( ) const override; \
	QString getMetaObjectDir( ) const override; \
	QString getMetaObjectPathName( ) const override

#ifdef Def_Last_Firend_StaticMetaInfo
#undef Def_Last_Firend_StaticMetaInfo
#endif

#define Def_Last_Firend_StaticMetaInfo( Friend_Class ) \
public:\
	friend class Friend_Class;\
	Def_Last_StaticMetaInfo(  )

#ifdef Imp_StaticMetaInfo
#undef Imp_StaticMetaInfo
#endif

#define Imp_StaticMetaInfo_Def_sep( Imp_Class , Class_Translate, Dir_Translate, sep) \
	QString Imp_Class::getStaticMetaObjectName( ) { \
		return Class_Translate; \
	}\
	QString Imp_Class::getStaticMetaObjectDir( ) { \
		return Dir_Translate; \
	}\
	QString Imp_Class::getStaticMetaObjectPathName( ) { \
		return QString( "%1%2%3").arg(Dir_Translate).arg(sep).arg(Class_Translate) ; \
	}\
	QString Imp_Class::getMetaObjectName( ) const {\
		return Class_Translate;\
	}\
	QString Imp_Class::getMetaObjectDir( ) const {\
		return Dir_Translate;\
	}\
	QString Imp_Class::getMetaObjectPathName( ) const {\
		return QString( "%1%2%3").arg(Dir_Translate).arg(sep).arg(Class_Translate) ; \
	}\
	class Imp_Class

#define Imp_StaticMetaInfo( Imp_Class , Class_Translate, Dir_Translate) \
	Imp_StaticMetaInfo_Def_sep( Imp_Class , Class_Translate, Dir_Translate, "/")

#define Def_NodeItem_StaticMetaInfo( ) \
	Def_Last_StaticMetaInfo( );\
	friend class NodeItemGenerate;\
	friend class Application;\
	friend class VarGenerate

#define Def_NodeItem_Last_StaticMetaInfo( ) \
	Def_Last_Firend_StaticMetaInfo( NodeItem );\
	friend class NodeItemGenerate;\
	friend class Application;\
	friend class VarGenerate

#define Def_First_Mate_Node_Type( node_Item_enum_type_value ) \
	public: \
	virtual nodeItemEnum::Node_Item_Type getNodeMetaType( ) const { return nodeItemEnum::Node_Item_Type::node_Item_enum_type_value; } \
	static nodeItemEnum::Node_Item_Type getStaticMetaNodeType( ) { return nodeItemEnum::Node_Item_Type::node_Item_enum_type_value; }

#define Def_Last_Mate_Node_Type( node_Item_enum_type_value ) \
	public: \
	nodeItemEnum::Node_Item_Type getNodeMetaType( ) const override { return nodeItemEnum::Node_Item_Type::node_Item_enum_type_value; } \
	static nodeItemEnum::Node_Item_Type getStaticMetaNodeType( ) { return nodeItemEnum::Node_Item_Type::node_Item_enum_type_value; }

class Type_Alias {
	Def_First_StaticMetaInfo( );
public:
	virtual ~Type_Alias( ) { }
};

namespace nodeItemEnum {
	Q_NAMESPACE;
	enum class Click_Type {
		None, // 没有
		Space, // 空白
		Title, // 标题
		InputPort, // 输入
		OutputPort, // 输出
	};
	Q_ENUM_NS( Click_Type );

	enum class Node_Item_Type {
		None, // 非正式
		Root, // 根，节点运行必须在连接的根源存在根节点，具备循环权与运行权节点
		End, // 尾，节点链表结束节点，具备整个节点运行结束的能力。运行到该节点，总会结束整个节点链
		Process, // 过程，一般的调度节点，自身不具备运行能力
		Logic, // 逻辑，具备选择输出权，自身不具备运行能力
		Foreach, // 循环，具备循环权，自身不具备运行能力
		Loop, // 回路，运行该节点之后，整个渲染流程回到最近的循环权节点，具备完整跳转权。与 End 不同，该类型会询问循环权节点是否继续循环。
	};
	Q_ENUM_NS( Node_Item_Type );
	bool getEnumName( const Node_Item_Type &enum_var, QString &result_str );
	bool getEnumName( const Click_Type &enum_var, QString &result_str );
}

#endif // TYPE_ALIAS_H_H_HEAD__FILE__
