#include "nodeInfo.h"

#include <QVBoxLayout>

#include <alias/type_alias.h>

#include "../node/nodeComponent/INodeComponent.h"
#include "../node/nodeWidget/INodeWidget.h"

#include "../stack/infoWidgetStack/IInfoWidgetStack.h"
#include "../stack/infoWidgetStack/base/baseInfoWidgetStack.h"

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
	auto infoWidgetGen = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
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
			std_vector< QString > uiTypeName = typeObject->getUiTypeName( );
			size_t uiTypeCount = uiTypeName.size( );
			QString *uiTypeDataPtr = uiTypeName.data( );
			size_t uiIndex = 0;
			for( ; uiIndex < uiTypeCount; ++uiIndex ) {
				IInfoWidget *infoWidget = infoWidgetGen->generateInfoWidget( uiTypeDataPtr[ uiIndex ] );
				if( infoWidget ) {
					QString name = nodeComponent->getNodeComponentName( );
					infoWidget->setTitle( name );
					infoWidget->setPlaceholderText( name );
					mainLayout->addWidget( infoWidget );
					break;
				}
			}
			if( uiIndex == uiTypeCount ) {
				IInfoWidget *infoWidget = infoWidgetGen->generateInfoWidget( ErrorMsgWidget::staticMetaObject.className( ) );
				if( infoWidget ) {
					QString name = nodeComponent->getNodeComponentName( );
					infoWidget->setTitle( name );
					infoWidget->setText( "无法匹配对应的信息小窗口" );
					infoWidget->setPlaceholderText( "或许可以增加基本变量类型，并且修改其 ui 类型来实现信息面板的创建项" );
					mainLayout->addWidget( infoWidget );
				}
			}
		} else if( tools::vector::has( types, intTypeName ) == true ) {
		} else if( tools::vector::has( types, floatTypeName ) == true ) {
		} else if( tools::vector::has( types, dataTypeName ) == true ) {
		} else if( tools::vector::has( types, vectorTypeName ) == true ) {
		} else if( tools::vector::has( types, combinationTypeName ) == true ) {
		} else {
			tools::debug::printError( "没有匹配的类型，请配置有效类型" );
			IInfoWidget *infoWidget = infoWidgetGen->generateInfoWidget( ErrorMsgWidget::staticMetaObject.className( ) );
			if( infoWidget ) {
				infoWidget->setTitle( "错误标签" );
				infoWidget->setPlaceholderText( "或许可以增加基本变量类型，并且修改其 ui 类型来实现信息面板的创建项" );
				mainLayout->addWidget( infoWidget );
			}
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
