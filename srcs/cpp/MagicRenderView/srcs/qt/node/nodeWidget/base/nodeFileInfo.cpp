#include "nodeFileInfo.h"

#include <QLabel>
#include <QVBoxLayout>

#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"
#include "qt/stack/varStack/base/baseVarStackEx.h"
#include "qt/type/baseType/nullTypeObject.h"
NodeFileInfo::NodeFileInfo( QWidget *parent, Qt::WindowFlags f ) : INodeWidget( nullptr, parent, f ) {
	UserFunctionDeclaration *declaration;
	declaration = new UserFunctionDeclaration(
		"file fileInfo(string file_path); " );
	declaration->setCallFcuntion( [this,declaration]( ) {
		qDebug( ) << declaration->getDeclarationName( );
		emit this->finish( this, IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< NullTypeObject >( ), 0, __LINE__ );
	} );
	functionDeclaration.reset( declaration );
	title->setText( declaration->getDeclarationName( ) );
}
void NodeFileInfo::connectNodeGraphWidget( NodeGraph *node_graph ) {
	INodeWidget::connectNodeGraphWidget( node_graph );
}
std_shared_ptr< ITypeObject > NodeFileInfo::getResult( ) const {
	return { };
}
std_vector_unity_shared< ITypeObject > NodeFileInfo::getParams( ) const {
	return { };
}
std_vector_unity_shared< ITypeObject > NodeFileInfo::setParams( const std_vector_unity_shared< ITypeObject > &params ) const {
	return { };
}
bool NodeFileInfo::setParam( const std_shared_ptr< ITypeObject > &param, size_t param_index ) const {
	return false;
}
void NodeFileInfo::resizeEvent( QResizeEvent *event ) {
	INodeWidget::resizeEvent( event );
	QRect contentsRect = mainBoxLayout->contentsRect( );
	auto contentSize = contentsRect.size( );
	int contentWidth = contentSize.width( );
	int contentHeight = contentsRect.height( );
	int titleWidth = title->size( ).width( );
	int newX = titleWidth + ( contentWidth - titleWidth ) / 2;
}
