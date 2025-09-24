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
protected:
	/// @brief 生成代码
	size_t generateCode;
	/// @brief 记录当前类型
	std_shared_ptr< I_Type > varTypeInfo;
	/// @brief 记录对象自身类型
	std_shared_ptr< I_Type > objTypeInfo;
protected:
	virtual I_Type * initTypeInfo( );
public:
	BaseVarType( );
	BaseVarType( QObject *parent );
	BaseVarType( QObject *parent, const std_shared_ptr< I_Type > &var_type_info );
	BaseVarType( const BaseVarType &other );
	virtual void * getVarPtr( ) const { return nullptr; }
	virtual void * getVarPtr( const I_Type &type_info ) const;
	/// @brief 重置为默认
	virtual void resetVar( ) { }
	~BaseVarType( ) override;
	virtual bool setVar( const BaseVarType *target_data );
	virtual const I_Type & getVarTypeInfo( ) const;
	virtual const I_Type & getThisTypeInfo( ) const;
	virtual  I_Type * getVarTypeInfoPtr( ) const;
	virtual  I_Type * getThisTypeInfoPtr( ) const;
	template< typename type >
	type * getVarPtr( ) const {
		return ( type * ) getVarPtr( typeid( type ) );
	}
public:
	friend BaseVarType * operator +( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref );
	friend BaseVarType * operator -( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref );
	friend BaseVarType * operator *( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref );
	friend BaseVarType * operator /( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref );

	friend BaseVarType * operator +( const BaseVarType &left_type_var_ref, const BaseVarType &right_type_var_ref ) {
		return operator+( left_type_var_ref, &right_type_var_ref );
	}
	friend BaseVarType * operator -( const BaseVarType &left_type_var_ref, const BaseVarType &right_type_var_ref ) {

		return operator-( left_type_var_ref, &right_type_var_ref );
	}
	friend BaseVarType * operator *( const BaseVarType &left_type_var_ref, const BaseVarType &right_type_var_ref ) {
		return operator*( left_type_var_ref, &right_type_var_ref );
	}
	friend BaseVarType * operator /( const BaseVarType &left_type_var_ref, const BaseVarType &right_type_var_ref ) {
		return operator/( left_type_var_ref, &right_type_var_ref );
	}
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const int8_t&, BaseVarType *);
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const int16_t&, BaseVarType *);
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const int32_t&, BaseVarType *);
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const int64_t&, BaseVarType *);
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const uint8_t&, BaseVarType *);
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const uint16_t&, BaseVarType *);
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const uint32_t&, BaseVarType *);
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const uint64_t&, BaseVarType* );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const float&, BaseVarType* );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const BaseVarType &, const double&, BaseVarType* );
	STR_CALCU_OPERATOR( const BaseVarType&, BaseVarType* );

	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, BaseVarType );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, int8_t );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, int16_t );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, int32_t );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, int64_t );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, uint8_t );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, uint16_t );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, uint32_t );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, uint64_t );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, float );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_CALCULATE( BaseVarType, double );
	DEF_ASSIGN_OPERATOR_REF_AND_PTR_AT_STR_CALCULATE( BaseVarType );
Q_SIGNALS:
	void releaseObj( BaseVarType *release );

};

#endif // BASEVARTYPE_H_H_HEAD__FILE__
