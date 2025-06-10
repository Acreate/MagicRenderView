#include "nodeFileInfo.h"

#include <QLabel>
#include <QVBoxLayout>

#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"
#include "qt/node/nodeComponent/base/nodeInputLineText.h"
#include "qt/node/nodeComponent/base/nodePanel.h"
#include "qt/stack/varStack/base/baseVarStackEx.h"
#include "qt/type/baseType/nullTypeObject.h"
NodeFileInfo::NodeFileInfo( const QString &node_widget_name, QWidget *parent, Qt::WindowFlags f ) : INodeWidget( node_widget_name, nullptr, parent, f ) {
	UserFunctionDeclaration *declaration;
	declaration = new UserFunctionDeclaration(
		"文件信息 获取文件信息(字符串 文件路径); " );
	declaration->setCallFcuntion( [this,declaration]( ) {
		qDebug( ) << declaration->getDeclarationName( );
		emit this->finish( this, IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< NullTypeObject >( ), 0, __LINE__ );
	} );
	functionDeclaration.reset( declaration );
	auto declarationName = declaration->getDeclarationName( );
	title->setText( declarationName );
	setObjectName( declarationName );
	subPlan = new NodePanel( "节点面板", this );
	mainBoxLayout->addWidget( subPlan );

	NodeInputLineText *path = new NodeInputLineText( "路径", this );
	subPlan->appendInput( path );

	path = new NodeInputLineText( "全路径", this );
	subPlan->appendOutput( path );
	path = new NodeInputLineText( "大小", this );
	subPlan->appendOutput( path );
	path = new NodeInputLineText( "占用", this );
	subPlan->appendOutput( path );
	path = new NodeInputLineText( "创建日期", this );
	subPlan->appendOutput( path );
	path = new NodeInputLineText( "最后更改日期", this );
	subPlan->appendOutput( path );
	path = new NodeInputLineText( "拥有者", this );
	subPlan->appendOutput( path );
	path = new NodeInputLineText( "内容", this );
	subPlan->appendOutput( path );

	mainBoxLayout->addSpacerItem( new QSpacerItem( 0, 100, QSizePolicy::Ignored, QSizePolicy::Expanding ) );
	subPlan->repaint( );
	repaint( );
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
void NodeFileInfo::setNodeWidgetName( const QString &node_widget_name ) {
	INodeWidget::setNodeWidgetName( node_widget_name );
	title->setText( node_widget_name );
	setObjectName( node_widget_name );
}


void NodeFileInfo::updateSize( ) {
	size_t leftHeight = 0, width = 0;

	int count = mainBoxLayout->count( );
	int index = 0;
	for( ; index < count; ++index ) {
		QWidget *widget = mainBoxLayout->itemAt( index )->widget( );
		if( widget ) {
			leftHeight += widget->height( );
			int compWidget = widget->width( );
			if( compWidget > width )
				width = compWidget;
		}
	}
	setFixedSize( width, leftHeight );
}
void NodeFileInfo::showEvent( QShowEvent *event ) {
	INodeWidget::showEvent( event );
	updateSize( );
}
