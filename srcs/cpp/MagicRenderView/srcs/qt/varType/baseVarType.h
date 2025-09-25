#ifndef BASEVARTYPE_H_H_HEAD__FILE__
#define BASEVARTYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class I_Type;
class I_Conver;
class I_Del;
class I_New;
class BaseVarType : public QObject {
	Q_OBJECT;
private:
	friend class VarGenerate;
	std_function< bool ( ) > baseVarTypeInitTypeInfo;
protected:
	/// @brief 生成代码
	size_t generateCode;
	/// @brief 记录当前类型
	std_shared_ptr< I_Type > varTypeInfo;
	/// @brief 记录对象自身类型
	std_shared_ptr< I_Type > objTypeInfo;
	/// @brief 初始化函数
	std_function< bool ( ) > initTypeInfo;
	/// @brief 对象释放调用函数
	std_function< void ( ) > deleteCall;
public:
	BaseVarType( );
	BaseVarType( QObject *parent );

	virtual const std_function< bool( ) > & getBaseVarTypeInitTypeInfo( ) const { return baseVarTypeInitTypeInfo; }
	virtual void * getVarPtr( ) const = 0;
	virtual void * getVarPtr( const I_Type &type_info ) const;
	/// @brief 重置为默认
	virtual void resetVar( ) = 0;
	~BaseVarType( ) override;
	virtual bool setVar( const BaseVarType *target_data );
	virtual I_Type * getVarTypeInfoPtr( ) const;
	virtual I_Type * getThisTypeInfoPtr( ) const;
	template< typename type >
	type * getVarPtr( ) const {
		return ( type * ) getVarPtr( typeid( type ) );
	}
public: // 删除列表

	/// @brief 同时与 BaseVarType & operator =( const BaseVarType *right_type_var_ref )  激活时，赋予指针赋值，但类型会降级，再也无法升级到子类。@code *varptr = varptr @cond 
	/// @param other 
	BaseVarType( const BaseVarType &other ) = delete;
	/// @brief 同时与 BaseVarType( const BaseVarType &other ) 激活时，赋予指针赋值，但类型会降级，再也无法升级到子类。@code *varptr = varptr @cond 
	const BaseVarType & operator =( const BaseVarType *right_type_var_ref ) = delete;
public: // 重载列表
#define def_operater_calcu( result_type_, param_type_, param_name_ ) \
	result_type_ operator=(  param_type_ param_name_ ); \
	result_type_ operator+(  param_type_ param_name_ ) = delete; \
	result_type_ operator-(  param_type_ param_name_ ) = delete; \
	result_type_ operator*(  param_type_ param_name_ ) = delete; \
	result_type_ operator/(  param_type_ param_name_ ) = delete; \
	result_type_ operator+=(  param_type_ param_name_ ); \
	result_type_ operator-=(  param_type_ param_name_ ); \
	result_type_ operator*=(  param_type_ param_name_ ); \
	result_type_ operator/=(  param_type_ param_name_ ); \
	bool operator==(  param_type_ param_name_ ) const; \
	bool operator>(  param_type_ param_name_ ) const; \
	bool operator<(  param_type_ param_name_ ) const; \
	bool operator>=(  param_type_ param_name_ ) const; \
	bool operator<=(  param_type_ param_name_ ) const

#define delete_friend_operater( result_type_, left_param_type_, right_param_type_, operater_symbol) \
	public :\
	friend result_type_ operator operater_symbol( left_param_type_, right_param_type_ ) = delete

#define del_fr_op_c( result_type_, left_param_type_, right_param_type_) \
	delete_friend_operater( bool, left_param_type_, right_param_type_, == ) ;\
	delete_friend_operater( bool, left_param_type_, right_param_type_, > );\
	delete_friend_operater( bool, left_param_type_, right_param_type_, < );\
	delete_friend_operater( bool, left_param_type_, right_param_type_, >= );\
	delete_friend_operater( bool, left_param_type_, right_param_type_, <= )

#define def_friend_operater(  result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, operater_symbol) \
	public :\
	friend result_type_ operator operater_symbol( left_param_type_ left_var_name_, right_param_type_ right_var_name_)

#define def_fr_op_c( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_) \
	def_friend_operater( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, += );\
	def_friend_operater( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, + ) = delete;\
	def_friend_operater( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, -= );\
	def_friend_operater( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, - ) = delete;\
	def_friend_operater( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, *= );\
	def_friend_operater( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, * ) = delete;\
	def_friend_operater( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, /= );\
	def_friend_operater( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, / ) = delete;\
	def_friend_operater( result_type_, left_param_type_, left_var_name_, right_param_type_, right_var_name_, = );\
	def_friend_operater( bool, left_param_type_, left_var_name_, right_param_type_, right_var_name_, == );\
	def_friend_operater( bool, left_param_type_, left_var_name_, right_param_type_, right_var_name_, > );\
	def_friend_operater( bool, left_param_type_, left_var_name_, right_param_type_, right_var_name_, < );\
	def_friend_operater( bool, left_param_type_, left_var_name_, right_param_type_, right_var_name_, >= );\
	def_friend_operater( bool, left_param_type_, left_var_name_, right_param_type_, right_var_name_, <= )

	def_operater_calcu( BaseVarType &, const BaseVarType&, set_string_var );
	def_operater_calcu( BaseVarType &, const QString&, set_string_var );
	def_operater_calcu( BaseVarType &, const std::string&, set_string_var );
	def_operater_calcu( BaseVarType &, const std::wstring&, set_string_var );
	def_operater_calcu( BaseVarType &, const int8_t&, set_string_var );
	def_operater_calcu( BaseVarType &, const int16_t&, set_string_var );
	def_operater_calcu( BaseVarType &, const int32_t&, set_string_var );
	def_operater_calcu( BaseVarType &, const int64_t&, set_string_var );
	def_operater_calcu( BaseVarType &, const uint8_t&, set_string_var );
	def_operater_calcu( BaseVarType &, const uint16_t&, set_string_var );
	def_operater_calcu( BaseVarType &, const uint32_t&, set_string_var );
	def_operater_calcu( BaseVarType &, const uint64_t&, set_string_var );
	def_operater_calcu( BaseVarType &, const bool&, set_string_var );
	def_operater_calcu( BaseVarType &, const float&, set_string_var );
	def_operater_calcu( BaseVarType &, const double&, set_string_var );

	del_fr_op_c( BaseVarType &, const BaseVarType &, const BaseVarType* );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const QString& );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const std::string& );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const std::wstring& );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const int8_t & );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const int16_t & );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const int32_t & );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const int64_t & );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const uint8_t & );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const uint16_t & );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const uint32_t & );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const uint64_t & );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const float & );
	del_fr_op_c( BaseVarType &, const BaseVarType &, const double & );

	del_fr_op_c( BaseVarType &, const BaseVarType*, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const QString&, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const std::string&, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const std::wstring&, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const int8_t &, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const int16_t &, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const int32_t &, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const int64_t &, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const uint8_t &, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const uint16_t &, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const uint32_t &, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const uint64_t &, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const float &, const BaseVarType & );
	del_fr_op_c( BaseVarType &, const double &, const BaseVarType & );
Q_SIGNALS:
	void releaseObj( BaseVarType *release );

};

#endif // BASEVARTYPE_H_H_HEAD__FILE__
