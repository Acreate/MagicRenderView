#include "./INodeGeneraterItem.h"

INodeGeneraterItem::INodeGeneraterItem( const IFunctionDeclaration &function_declaration, QObject *parent ): QObject( parent ), functionDeclaration( function_declaration ) { }
QWidget * INodeGeneraterItem::createListNodeWidget( ) const {
	return nullptr;
}
INodeWidget * INodeGeneraterItem::createScriptNodeWidget( ) const {
	return nullptr;
}
std_shared_ptr< QImage > INodeGeneraterItem::createNodeImage( ) const {
	return nullptr;
}
