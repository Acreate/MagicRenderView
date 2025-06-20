﻿#include "./pairtWidget.h"

#include <QVBoxLayout>

#include "../../../stack/infoWidgetStack/IInfoWidgetStack.h"
#include "../../../stack/infoWidgetStack/base/baseInfoWidgetStack.h"

#include "../../../type/baseType/nullTypeObject.h"
#include "../../../type/sequenceType/pairtTypeObject.h"
PairtWidget::PairtWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	IInfoWidget **infoWidget = new IInfoWidget *;
	*infoWidget = nullptr;
	first.reset( infoWidget );
	infoWidget = new IInfoWidget *;
	*infoWidget = nullptr;
	scond.reset( infoWidget );
}
QString PairtWidget::getText( ) const {
	return "";
}
void PairtWidget::setText( const QString &new_text ) const {
}

void PairtWidget::setPlaceholderText( const QString &placeholder_text ) const {
}
QString PairtWidget::getPlaceholderText( ) const {
	return "";
}
void PairtWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	auto typeObject = value.get( );
	if( typeObject == nullptr )
		return;
	auto pairtTypeObject = qobject_cast< PairtTypeObject * >( typeObject );
	if( pairtTypeObject == nullptr )
		return;

	auto first = pairtTypeObject->getFirst( );
	auto firstPtr = first.get( );
	if( *firstPtr == nullptr )
		return;

	auto scond = pairtTypeObject->getScond( );
	auto scondPtr = scond.get( );
	if( *scondPtr == nullptr )
		return;

	auto infoWidgetStack = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );

	auto charses = firstPtr->getUiTypeName( );
	IInfoWidget *firstWidget = nullptr;
	for( auto uiType : charses ) {
		firstWidget = infoWidgetStack->generateInfoWidget( uiType );
		if( firstWidget != nullptr )
			break;
	}

	charses = scondPtr->getUiTypeName( );
	IInfoWidget *scondWidget = nullptr;
	for( auto uiType : charses ) {
		scondWidget = infoWidgetStack->generateInfoWidget( uiType );
		if( scondWidget != nullptr )
			break;
	}

	if( firstWidget == nullptr || scondWidget == nullptr )
		return;
	IInfoWidget **thisFirstWidget = this->first.get( );
	IInfoWidget **thisScondWidget = this->scond.get( );
	if( *thisFirstWidget )
		delete *thisFirstWidget;
	if( *thisScondWidget )
		delete *thisScondWidget;
	*thisFirstWidget = firstWidget;
	*thisScondWidget = scondWidget;

	mainLayout->addWidget( *thisFirstWidget );
	mainLayout->addWidget( *thisScondWidget );
}
std_shared_ptr< ITypeObject > PairtWidget::getFirst( ) const {
	if( *first == nullptr )
		return std_shared_ptr< ITypeObject >( new NullTypeObject );
	IInfoWidget **widget = first.get( );
	return ( *widget )->getValue( );
}
std_shared_ptr< ITypeObject > PairtWidget::getScond( ) const {
	if( *scond == nullptr )
		return std_shared_ptr< ITypeObject >( new NullTypeObject );
	IInfoWidget **widget = scond.get( );
	return ( *widget )->getValue( );
}
bool PairtWidget::setFirst( const std_shared_ptr< ITypeObject > &key ) const {
	bool cond = firstVerify == nullptr;
	if( cond )
		return false;
	ITypeObject *element = key.get( );
	if( firstVerify( element ) == false )
		return false;

	auto charses = key->getUiTypeName( );
	auto infoWidgetStack = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	for( auto uiType : charses ) {
		auto widgetStack = infoWidgetStack->generateInfoWidget( uiType );
		if( widgetStack != nullptr ) {
			IInfoWidget **infoWidget = first.get( );
			widgetStack->setTitle( "键" );
			mainLayout->replaceWidget( *infoWidget, widgetStack );
			if( *infoWidget )
				delete *infoWidget;
			*infoWidget = widgetStack;
			return true;
		}
	}
	return false;
}
bool PairtWidget::setScond( const std_shared_ptr< ITypeObject > &value ) const {
	bool cond = scondVerify == nullptr;
	if( cond )
		return false;
	ITypeObject *element = value.get( );
	if( scondVerify( element ) == false )
		return false;
	auto charses = value->getUiTypeName( );
	auto infoWidgetStack = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	for( auto uiType : charses ) {
		auto widgetStack = infoWidgetStack->generateInfoWidget( uiType );
		if( widgetStack != nullptr ) {
			IInfoWidget **infoWidget = scond.get( );
			widgetStack->setTitle( "值" );
			mainLayout->replaceWidget( *infoWidget, widgetStack );
			if( *infoWidget )
				delete *infoWidget;
			*infoWidget = widgetStack;
			return true;
		}
	}
	return false;
}
