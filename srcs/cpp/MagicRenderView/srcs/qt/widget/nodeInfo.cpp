#include "nodeInfo.h"

#include <QVBoxLayout>

#include <alias/type_alias.h>

#include <qt/node/nodeComponent/INodeComponent.h>
#include <qt/node/nodeWidget/INodeWidget.h>

#include <qt/stack/infoWidgetStack/IInfoWidgetStack.h>
#include <qt/stack/infoWidgetStack/base/baseInfoWidgetStack.h>

#include <qt/type/baseType/dataTypeObject.h>
#include <qt/type/baseType/floatTypeObject.h>
#include <qt/type/baseType/intTypeObject.h>
#include <qt/type/baseType/stringTypeObject.h>
#include <qt/type/blendType/combinationTypeObject.h>
#include <qt/type/lineType/vectorTypeObject.h>

#include <qt/widget/infoWidget/infoBaseWidget/errorMsgWidget.h>

NodeInfo::NodeInfo( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
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
			std_vector< QString > uiTypeName = typeObject->getUiTypeNames( );
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
					connect( infoWidget, &IInfoWidget::valueChanged, [infoWidget, nodeComponent] {
						nodeComponent->setVar( infoWidget->getValue( ) );
					} );
					break;
				}
			}
			if( uiIndex == uiTypeCount ) {
				IInfoWidget *infoWidget = infoWidgetGen->generateInfoWidget( ErrorMsgWidget::staticMetaObject.className( ) );
				if( infoWidget == nullptr )
					continue;
				mainLayout->addWidget( infoWidget );
				QString name = nodeComponent->getNodeComponentName( );
				infoWidget->setTitle( name );

				ErrorMsgWidget *errorMsgWidget = qobject_cast< ErrorMsgWidget * >( infoWidget );
				if( errorMsgWidget == nullptr ) {
					infoWidget->setPlaceholderText( "无法匹配对应的信息小窗口，或许可以增加基本变量类型，并且修改其 ui 类型来实现信息面板的创建项" );
					continue;
				}
				errorMsgWidget->setText( "无法匹配对应的信息小窗口" );
				infoWidget->setPlaceholderText( "或许可以增加基本变量类型，并且修改其 ui 类型来实现信息面板的创建项" );
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
