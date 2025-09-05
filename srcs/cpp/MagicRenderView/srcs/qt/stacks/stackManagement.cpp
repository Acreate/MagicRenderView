#include "./stackManagement.h"

#include "../application/application.h"

#include "funStack/base/calculateFunStack.h"
#include "funStack/base/fileFunStack.h"
#include "funStack/base/logicFunStack.h"
#include "funStack/base/rebuilerFunStack.h"
#include "funStack/base/stringFunStack.h"

#include "varStack/base/baseVarStack.h"
StackManagement::StackManagement( ) : stdMutex( new std_mutex ), initReady( false ) {
}
size_t StackManagement::init( ) {
	if( initReady == true )
		return 0;
	appendFunctionStack< LogicFunStack >( );
	
	appendFunctionStack< CalculateFunStack >( );
	appendFunctionStack< StringFunStack >( );
	appendFunctionStack< FileFunStack >( );
	appendFunctionStack< RebuilerFunStack >( );

	appendVarStacks< BaseVarStack >( );
	initReady = true;
	return 0;
}

bool StackManagement::appendFunctionStack( const std_shared_ptr< IFunStack > &new_function_stack ) {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	auto funStack = new_function_stack.get( );
	auto name = funStack->getName( );
	auto className = funStack->metaObject( )->className( );
	for( auto &item : funStacks )
		if( item.get( ) == funStack || item->getName( ) == name && item->metaObject( )->className( ) == className )
			return false;
	funStacks.emplace_back( new_function_stack );
	return true;
}
bool StackManagement::removeFunctionStack( const std_shared_ptr< IFunStack > &new_function_stack ) {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	auto removeExtent = new_function_stack.get( );
	auto iterator = funStacks.begin( );
	auto end = funStacks.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->get( ) == removeExtent ) {
			funStacks.erase( iterator );
			return true;
		}
	return false;
}
bool StackManagement::removeFunctionStackAtType( const QString &function_stack_class_name, const QString &function_stack_name ) {

	std_lock_grad_mutex lock( *stdMutex.get( ) );
	auto iterator = funStacks.begin( );
	auto end = funStacks.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->get( )->metaObject( )->className( ) == function_stack_class_name && iterator->get( )->getName( ) == function_stack_name ) {
			funStacks.erase( iterator );
			return true;
		}
	return false;

	return false;
}
bool StackManagement::removeFunctionStackAtType( const std_shared_ptr< IFunStack > &new_function_stack ) {
	return removeFunctionStackAtType( new_function_stack->metaObject( )->className( ), new_function_stack->getName( ) );
}
std_vector< std_shared_ptr< IFunStack > > StackManagement::removeFunctionStackAtClassName( const QString &function_stack_class_name ) {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IFunStack > > result;

	std::vector< std::shared_ptr< IFunStack > >::iterator iterator, end;
	while( true ) {
		iterator = funStacks.begin( );
		end = funStacks.end( );
		for( ; iterator != end; ++iterator )
			if( iterator->get( )->metaObject( )->className( ) == function_stack_class_name ) {
				result.emplace_back( *iterator );
				funStacks.erase( iterator );
				break;
			}
		if( iterator == end )
			break;
	}
	return result;
}
std_vector< std_shared_ptr< IFunStack > > StackManagement::removeFunctionStackAtStackName( const QString &function_stack_name ) {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IFunStack > > result;

	std::vector< std::shared_ptr< IFunStack > >::iterator iterator, end;
	while( true ) {
		iterator = funStacks.begin( );
		end = funStacks.end( );
		for( ; iterator != end; ++iterator )
			if( iterator->get( )->getName( ) == function_stack_name ) {
				result.emplace_back( *iterator );
				funStacks.erase( iterator );
				break;
			}
		if( iterator == end )
			break;
	}
	return result;
}
std_vector< std_shared_ptr< IFunStack > > StackManagement::findFunStacksAtType( const QString &fun_stack_type_name ) const {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IFunStack > > result;
	for( auto &item : funStacks )
		if( item->metaObject( )->className( ) == fun_stack_type_name )
			result.emplace_back( item );
	return result;
}
std_vector< std_shared_ptr< IFunStack > > StackManagement::findFunStacksAtName( const QString &fun_stack_name ) const {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IFunStack > > result;
	for( auto &item : funStacks )
		if( item->getName( ) == fun_stack_name )
			result.emplace_back( item );
	return result;
}
std_shared_ptr< IFunStack > StackManagement::findFunStack( const QString &fun_stack_type_name, const QString &fun_stack_name ) const {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	for( auto &item : funStacks )
		if( item->metaObject( )->className( ) == fun_stack_type_name && item->getName( ) == fun_stack_name )
			return item;
	return nullptr;
}
bool StackManagement::appendVarStacks( const std_shared_ptr< IVarStack > &new_var_stack ) {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	auto newStackPtr = new_var_stack.get( );
	auto newStackType = newStackPtr->metaObject( )->className( );
	auto newStackName = newStackPtr->getStackTypeName( );
	for( auto &item : varStacks )
		if( item.get( ) == newStackPtr || item->getStackTypeName( ) == newStackName && item->metaObject( )->className( ) == newStackType )
			return false;
	varStacks.emplace_back( new_var_stack );
	return true;
}
bool StackManagement::removeVarStack( const std_shared_ptr< IVarStack > &new_var_stack ) {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	auto removeExtent = new_var_stack.get( );
	auto iterator = varStacks.begin( );
	auto end = varStacks.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->get( ) == removeExtent ) {
			varStacks.erase( iterator );
			return true;
		}
	return false;
}
std_vector< std_shared_ptr< IVarStack > > StackManagement::removeVarStackAtType( const QString &var_type_name ) {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;

	std::vector< std::shared_ptr< IVarStack > >::iterator iterator, end;
	while( true ) {
		iterator = varStacks.begin( );
		end = varStacks.end( );
		for( ; iterator != end; ++iterator )
			if( iterator->get( )->metaObject( )->className( ) == var_type_name ) {
				result.emplace_back( *iterator );
				varStacks.erase( iterator );
				break;
			}
		if( iterator == end )
			break;
	}
	return result;
}
std_vector< std_shared_ptr< IVarStack > > StackManagement::removeVarStackAtName( const QString &var_stack_name ) {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;

	std::vector< std::shared_ptr< IVarStack > >::iterator iterator, end;
	while( true ) {
		iterator = varStacks.begin( );
		end = varStacks.end( );
		for( ; iterator != end; ++iterator )
			if( iterator->get( )->getStackTypeName( ) == var_stack_name ) {
				result.emplace_back( *iterator );
				varStacks.erase( iterator );
				break;
			}
		if( iterator == end )
			break;
	}
	return result;
}
std_vector< std_shared_ptr< IVarStack > > StackManagement::findVarStacksAtType( const QString &var_stack_type_name ) const {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;
	for( auto &item : varStacks )
		if( item.get( )->metaObject( )->className( ) == var_stack_type_name )
			result.emplace_back( item );

	return result;
}
std_vector< std_shared_ptr< IVarStack > > StackManagement::findVarStacksAtName( const QString &var_stack_name ) const {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;
	for( auto &item : varStacks )
		if( item.get( )->getStackTypeName( ) == var_stack_name )
			result.emplace_back( item );

	return result;
}
std_shared_ptr< IVarStack > StackManagement::findVarStack( const QString &var_stack_type_name, const QString &var_stack_name ) const {
	std_lock_grad_mutex lock( *stdMutex.get( ) );
	std_vector< std_shared_ptr< IVarStack > > result;
	for( auto &item : varStacks )
		if( item.get( )->getStackTypeName( ) == var_stack_name && item.get( )->metaObject( )->className( ) == var_stack_type_name )
			return item;
	return nullptr;
}
