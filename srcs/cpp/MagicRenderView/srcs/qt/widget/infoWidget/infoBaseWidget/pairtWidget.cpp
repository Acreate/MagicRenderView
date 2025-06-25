#include "./pairtWidget.h"

#include <QLabel>
#include <QVBoxLayout>

#include <qt/stack/infoWidgetStack/IInfoWidgetStack.h>
#include <qt/stack/infoWidgetStack/base/baseInfoWidgetStack.h>

#include <qt/type/sequenceType/pairtTypeObject.h>
#include <qt/type/baseType/nullTypeObject.h>

#include "../../../stack/varStack/IVarStack.h"
#include "../../../stack/varStack/base/baseVarStackEx.h"
PairtWidget::PairtWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	IInfoWidget **infoWidget = new IInfoWidget *;
	*infoWidget = nullptr;
	first.reset( infoWidget );
	infoWidget = new IInfoWidget *;
	*infoWidget = nullptr;
	scond.reset( infoWidget );
	pairtTypeObject = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< PairtTypeObject >( );

	pairtTypeObject->setUiTypeName( title_msg );
}

void PairtWidget::setPlaceholderText( const QString &placeholder_text ) const {
}
QString PairtWidget::getPlaceholderText( ) const {
	return "";
}
bool PairtWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	auto typeObject = value.get( );
	if( typeObject == nullptr )
		return false;
	auto pairtTypeObject = qobject_cast< PairtTypeObject * >( typeObject );
	if( pairtTypeObject == nullptr )
		return false;

	auto first = pairtTypeObject->getFirst( );
	auto firstPtr = first.get( );
	if( *firstPtr == nullptr )
		return false;

	auto scond = pairtTypeObject->getScond( );
	auto scondPtr = scond.get( );
	if( *scondPtr == nullptr )
		return false;

	auto infoWidgetStack = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );

	auto charses = firstPtr->getUiTypeNames( );
	IInfoWidget *firstWidget = nullptr;
	for( auto uiType : charses ) {
		firstWidget = infoWidgetStack->generateInfoWidget( uiType );
		if( firstWidget != nullptr )
			break;
	}

	charses = scondPtr->getUiTypeNames( );
	IInfoWidget *scondWidget = nullptr;
	for( auto uiType : charses ) {
		scondWidget = infoWidgetStack->generateInfoWidget( uiType );
		if( scondWidget != nullptr )
			break;
	}

	if( firstWidget == nullptr || scondWidget == nullptr )
		return false;
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
	return true;
}
std_shared_ptr< ITypeObject > PairtWidget::getValue( ) const {
	if( *first )
		pairtTypeObject->setFirst( ( *first )->getValue( ) );
	else
		pairtTypeObject->setFirst( std_shared_ptr< ITypeObject >( new NullTypeObject( ) ) );
	if( *scond )
		pairtTypeObject->setScond( ( *scond )->getValue( ) );
	else
		pairtTypeObject->setScond( std_shared_ptr< ITypeObject >( new NullTypeObject( ) ) );
	return pairtTypeObject;
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
	bool cond = key == nullptr;
	if( cond )
		return false;
	ITypeObject *element = key.get( );
	if( firstVerify && firstVerify( element ) == false )
		return false;

	auto charses = key->getUiTypeNames( );
	auto infoWidgetStack = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	for( auto uiType : charses ) {
		auto widgetStack = infoWidgetStack->generateInfoWidget( uiType );
		if( widgetStack != nullptr ) {
			IInfoWidget **infoWidget = first.get( );
			widgetStack->setTitle( "键" );
			if( mainLayout->replaceWidget( *infoWidget, widgetStack ) == nullptr ) {
				if( *scond.get( ) )
					mainLayout->insertWidget( 1, widgetStack );
				else
					mainLayout->addWidget( widgetStack );
			}
			if( *infoWidget )
				delete *infoWidget;
			*infoWidget = widgetStack;
			return true;
		}
	}
	return false;
}
bool PairtWidget::setScond( const std_shared_ptr< ITypeObject > &value ) const {
	bool cond = value == nullptr;
	if( cond )
		return false;
	ITypeObject *element = value.get( );
	if( scondVerify && scondVerify( element ) == false )
		return false;
	auto charses = value->getUiTypeNames( );
	auto infoWidgetStack = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	for( auto uiType : charses ) {
		auto widgetStack = infoWidgetStack->generateInfoWidget( uiType );
		if( widgetStack != nullptr ) {
			IInfoWidget **infoWidget = scond.get( );
			widgetStack->setTitle( "值" );
			if( mainLayout->replaceWidget( *infoWidget, widgetStack ) == nullptr )
				mainLayout->addWidget( widgetStack );
			if( *infoWidget )
				delete *infoWidget;
			*infoWidget = widgetStack;
			return true;
		}
	}
	return false;
}
