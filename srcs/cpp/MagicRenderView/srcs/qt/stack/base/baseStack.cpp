#include "baseStack.h"

BaseStack::BaseStack( ) { }
std_shared_ptr<ITypeObject> BaseStack::generateVar( const QString &type_name ) const {
	return { };
}
std_shared_ptr<ITypeObject> BaseStack::setStorageVar( const std_shared_ptr<ITypeObject> &storage_obj, const QString &storage_name ) {
	return { };
}
std_shared_ptr<ITypeObject> BaseStack::getStorageVar( const QString &storage_name ) const {
	return { };
}
std_shared_ptr<ITypeObject> BaseStack::removeStorageVar( const QString &storage_name ) const {
	return { };
}
