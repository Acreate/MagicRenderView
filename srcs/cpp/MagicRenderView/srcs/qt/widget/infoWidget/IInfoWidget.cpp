#include "./IInfoWidget.h"

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

#include "../../stack/infoWidgetStack/IInfoWidgetStack.h"
#include "../../stack/infoWidgetStack/base/baseInfoWidgetStack.h"
#include "../../stack/varStack/IVarStack.h"
#include "../../stack/varStack/base/baseVarStackEx.h"

#include "../../type/baseType/nullTypeObject.h"

void IInfoWidget::synValue( const std_shared_ptr< ITypeObject > &value ) const {
	auto element = synObjPtr.get( );
	if( *element == nullptr )
		return;
	auto typeObject = value.get( );
	if( *typeObject == nullptr )
		return;
	auto uiTypeNames = element->getUiTypeNames( );
	auto getStackFunction = element->getGetStackFunction(  );
	*element = *typeObject;
	element->setUiTypeNames( uiTypeNames );
	element->setGetStackFunction( getStackFunction );
}
IInfoWidget::IInfoWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): QWidget( parent ), getStackFunction( get_stack_function ) {
	if( !getStackFunction )
		getStackFunction = [] {
			return IInfoWidgetStack::getStdSharedPtrInstance< BaseInfoWidgetStack >( );
		};
	infoWidgetSharedStack = getStackFunction( );
	mainLayout = new QVBoxLayout( this );
	mainLayout->setSpacing( 0 );
	title = new QLabel( this );
	mainLayout->addWidget( title, 0, Qt::AlignRight | Qt::AlignVCenter );
	title->setText( title_msg );
}
QString IInfoWidget::getTitle( ) const {
	return title->text( );
}

void IInfoWidget::setTitle( const QString &new_title ) const {
	title->setText( new_title );
}
void IInfoWidget::setPlaceholderText( const QString &placeholder_text ) const {
	title->setToolTip( placeholder_text );
}
QString IInfoWidget::getPlaceholderText( ) const {
	return title->toolTip( );
}
std_shared_ptr< ITypeObject > IInfoWidget::getValue( ) const { return IVarStack::getInstance< BaseVarStack >( )->generateTVar< NullTypeObject >( ); }
void IInfoWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	QPen pen = painter.pen( );
	int penWidth = 3;
	pen.setWidth( penWidth );
	painter.setPen( pen );
	int mol = ( penWidth - penWidth / 2 ) + 1 + penWidth;
	painter.drawRect( penWidth, penWidth, this->width( ) - mol, this->height( ) - mol );
}
