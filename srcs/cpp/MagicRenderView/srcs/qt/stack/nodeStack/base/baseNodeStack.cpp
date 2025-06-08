#include "./baseNodeStack.h"
INodeWidget * BaseNodeStack::_newNode( const QString &type_name ) const {
	return _newNode( type_name );
}
INodeWidget * BaseNodeStack::generateNode( const QString &type_name, QWidget *parnet ) const {
	INodeWidget *newNode = _newNode( type_name );
	if( newNode )
		newNode->setParent( parnet );
	return newNode;
}

INodeWidget * BaseNodeStack::setStorageNode( INodeWidget *storage_obj, const QString &storage_name ) {
	return nullptr;
}
INodeWidget * BaseNodeStack::getStorageNode( const QString &storage_name ) const {
	return nullptr;
}
INodeWidget * BaseNodeStack::removeStorageNode( const QString &storage_name ) {
	return nullptr;
}
std_vector< std_pairt< QString, std_vector< QString > > > BaseNodeStack::permissionNodeType( ) const {
	return { };
}
