#ifndef STACKMANAGEMENT_H_H_HEAD__FILE__
#define STACKMANAGEMENT_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../alias/type_alias.h"

class IFunStack;
class IVarStack;
class StackManagement : public QObject {
	Q_OBJECT;
protected:
	std_shared_ptr< std_mutex > stdMutex;
	std_vector< std_shared_ptr< IFunStack > > funStacks;
	std_vector< std_shared_ptr< IVarStack > > varStacks;
	bool initReady;
public:
	StackManagement( );
	/// @brief 对象初始化
	/// @return 0 表示成功
	virtual size_t init( );
	virtual bool isInitReady() const {
		return initReady;
	}
	virtual bool appendFunctionStack( const std_shared_ptr< IFunStack > &new_function_stack );
	template< typename IFunctionStack >
		requires requires ( IFunStack *a, IFunctionStack *b ) {
			a = b;
		}
	bool appendFunctionStack( ) {
		return appendFunctionStack( std_shared_ptr< IFunStack >( new IFunctionStack ) );
	}

	virtual bool removeFunctionStack( const std_shared_ptr< IFunStack > &new_function_stack );
	virtual bool removeFunctionStackAtType( const QString &function_stack_class_name, const QString &function_stack_name );
	virtual bool removeFunctionStackAtType( const std_shared_ptr< IFunStack > &new_function_stack );
	virtual std_vector< std_shared_ptr< IFunStack > > removeFunctionStackAtClassName( const QString &function_stack_class_name );
	virtual std_vector< std_shared_ptr< IFunStack > > removeFunctionStackAtStackName( const QString &function_stack_name );
	virtual std_vector< std_shared_ptr< IFunStack > > findFunStacksAtType( const QString &fun_stack_type_name ) const;

	template< typename IFunTypeStack >
		requires requires ( IFunStack *a, IFunTypeStack *b ) {
			a = b;
		}
	std_vector< std_shared_ptr< IVarStack > > findFunStacksAtType( ) const {
		return findFunStacksAtType( IFunTypeStack::staticMetaObject.className( ) );
	}
	virtual std_vector< std_shared_ptr< IFunStack > > findFunStacksAtName( const QString &fun_stack_name ) const;
	virtual std_shared_ptr< IFunStack > findFunStack( const QString &fun_stack_type_name, const QString &fun_stack_name ) const;
	virtual const std_vector< std_shared_ptr< IFunStack > > & getFunStacks( ) const {
		std_lock_grad_mutex lock( *stdMutex.get( ) );
		return funStacks;
	}
	virtual void setFunStacks( const std_vector< std_shared_ptr< IFunStack > > &fun_stacks ) {
		std_lock_grad_mutex lock( *stdMutex.get( ) );
		funStacks = fun_stacks;
	}
	virtual bool appendVarStacks( const std_shared_ptr< IVarStack > &new_var_stack );
	template< typename IFunctionStack >
		requires requires ( IVarStack *a, IFunctionStack *b ) {
			a = b;
		}
	bool appendVarStacks( ) {
		return appendVarStacks( std_shared_ptr< IVarStack >( new IFunctionStack ) );
	}

	virtual bool removeVarStack( const std_shared_ptr< IVarStack > &new_var_stack );
	virtual std_vector< std_shared_ptr< IVarStack > > removeVarStackAtType( const QString &var_type_name );
	virtual std_vector< std_shared_ptr< IVarStack > > removeVarStackAtName( const QString &var_stack_name );
	virtual std_vector< std_shared_ptr< IVarStack > > findVarStacksAtType( const QString &var_stack_type_name ) const;
	template< typename IVarTypeStack >
		requires requires ( IVarStack *a, IVarTypeStack *b ) {
			a = b;
		}
	std_vector< std_shared_ptr< IVarStack > > findVarStacksAtType( ) const {
		return findVarStacksAtType( IVarTypeStack::staticMetaObject.className( ) );
	}
	virtual std_vector< std_shared_ptr< IVarStack > > findVarStacksAtName( const QString &var_stack_name ) const;
	virtual std_shared_ptr< IVarStack > findVarStack( const QString &var_stack_type_name, const QString &var_stack_name ) const;
	virtual const std_vector< std_shared_ptr< IVarStack > > & getVarStacks( ) const {
		std_lock_grad_mutex lock( *stdMutex.get( ) );
		return varStacks;
	}
	virtual void setVarStacks( const std_vector< std_shared_ptr< IVarStack > > &var_Stacks ) {
		std_lock_grad_mutex lock( *stdMutex.get( ) );
		varStacks = var_Stacks;
	}
	virtual const std_mutex & getStdMutex( ) const {
		std_lock_grad_mutex lock( *stdMutex.get( ) );
		return *stdMutex;
	}
};

#endif // STACKMANAGEMENT_H_H_HEAD__FILE__
