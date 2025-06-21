#include "./pairtWidget.h"

#include "../../../stack/infoWidgetStack/IInfoWidgetStack.h"
#include "../../../stack/infoWidgetStack/base/baseInfoWidgetStack.h"

#include "../../../type/baseType/nullTypeObject.h"
PairtWidget::PairtWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	first.reset( new IInfoWidget * );
	scond.reset( new IInfoWidget * );
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
			if( *infoWidget )
				delete *infoWidget;
			*infoWidget = widgetStack;
			return true;
		}
	}
	return false;
}
