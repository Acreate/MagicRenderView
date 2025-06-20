#include "nodeInfo.h"

#include <QVBoxLayout>

#include <alias/type_alias.h>

#include "../node/nodeComponent/INodeComponent.h"
#include "../node/nodeWidget/INodeWidget.h"

#include "../type/baseType/dataTypeObject.h"
#include "../type/baseType/floatTypeObject.h"
#include "../type/baseType/intTypeObject.h"
#include "../type/baseType/stringTypeObject.h"
#include "../type/blendType/combinationTypeObject.h"
#include "../type/lineType/vectorTypeObject.h"

#include "infoWidget/infoBaseWidget/errorMsgWidget.h"
#include "infoWidget/infoBaseWidget/textWidget.h"

NodeInfo::NodeInfo( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
	currentNodeWidget = nullptr;
}
void NodeInfo::setNodeWidget( INodeWidget *node_widget ) {
	if( currentNodeWidget == node_widget )
		return;
	clearInfoPanel( );
	currentNodeWidget = node_widget;
	if( node_widget == nullptr )
		return;

	auto nodeComponents = currentNodeWidget->getNodeComponents( );
	size_t count = nodeComponents.size( );
	if( count == 0 )
		return;

	// 匹配字符串输入
	QString stringTypeName = StringTypeObject::staticMetaObject.className( );
	// 匹配整数输入
	QString intTypeName = IntTypeObject::staticMetaObject.className( );
	// 匹配浮点输入
	QString floatTypeName = FloatTypeObject::staticMetaObject.className( );
	// 匹配浮点输入
	QString dataTypeName = DataTypeObject::staticMetaObject.className( );
	// 序列
	QString vectorTypeName = VectorTypeObject::staticMetaObject.className( );
	// 结构体
	QString combinationTypeName = CombinationTypeObject::staticMetaObject.className( );

	auto data = nodeComponents.data( );
	for( size_t index = 0; index < count; ++index ) {
		auto nodeComponent = data[ index ];
		if( nodeComponent->getComponentChannel( ) != INodeComponent::Channel_Type::Input_Read )
			continue;
		auto typeObject = nodeComponent->getVarObject( );
		if( typeObject == nullptr )
			continue;
		std_vector< QString > types = typeObject->typeNames( );
		// 字符串
		if( tools::vector::has( types, stringTypeName ) == true ) {
			QString name = nodeComponent->getNodeComponentName( );
			TextWidget *textWidget = new TextWidget( this, name );
			textWidget->setTitle( name );
			textWidget->setPlaceholderText( name );
			mainLayout->addWidget( textWidget );
		} else if( tools::vector::has( types, intTypeName ) == true ) {
		} else if( tools::vector::has( types, floatTypeName ) == true ) {
		} else if( tools::vector::has( types, dataTypeName ) == true ) {
		} else if( tools::vector::has( types, vectorTypeName ) == true ) {
		} else if( tools::vector::has( types, combinationTypeName ) == true ) {
		} else {
			tools::debug::printError( "没有匹配的类型，请配置有效类型" );
			mainLayout->addWidget( new ErrorMsgWidget( this, "错误标签" ) );
		}
	}
	mainLayout->addSpacerItem( new QSpacerItem( 0, 100, QSizePolicy::Ignored, QSizePolicy::Expanding ) );
}
void NodeInfo::clearInfoPanel( ) {
	int count = mainLayout->count( );
	int index = 0;
	std_vector< QWidget * > removeWidget;
	for( ; index < count; ++index ) {
		auto layoutItem = mainLayout->itemAt( index );
		if( layoutItem->isEmpty( ) )
			continue;
		auto widget = layoutItem->widget( );
		if( widget )
			removeWidget.emplace_back( widget );
	}
	for( auto item : removeWidget ) {
		mainLayout->removeWidget( item );
		delete item;
	}
}
