#include "nodeFileInfo.h"

#include <QLabel>
#include <QVBoxLayout>

#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"
#include "qt/stack/varStack/base/baseVarStackEx.h"
#include "qt/type/baseType/nullTypeObject.h"
NodeFileInfo::NodeFileInfo( QWidget *parent, Qt::WindowFlags f ) : INodeWidget( nullptr, parent, f ) {
	auto declaration = new UserFunctionDeclaration(
		"file fileInfo(string); " );
	declaration->setCallFcuntion( [this,declaration]( ) {
		qDebug( ) << declaration->getDeclarationName( );
		emit this->finish( this, IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< NullTypeObject >( ), 0, __LINE__ );
	} );
	functionDeclaration.reset( declaration );

	QVBoxLayout *vBoxLayout = new QVBoxLayout( this );
	QLabel *title = new QLabel( declaration->getDeclarationName( ), this );
	vBoxLayout->addWidget( title );
}
void NodeFileInfo::connectNodeGraphWidget( NodeGraph *node_graph ) {
	INodeWidget::connectNodeGraphWidget( node_graph );
}
