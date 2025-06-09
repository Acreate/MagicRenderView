#include "./nodePanel.h"

#include <qboxlayout.h>
void NodePanel::updateSize( ) {
	size_t leftHeight = 0, rightHeight = 0;

	int count = leftVectorBoxLayout->count( );
	int index = 0;
	for( ; index < count; ++index ) {
		QWidget *widget = leftVectorBoxLayout->itemAt( index )->widget( );
		if( widget )
			leftHeight += widget->height( );
	}

	count = rightVectorBoxLayout->count( );
	for( index = 0; index < count; ++index ) {
		QWidget *widget = rightVectorBoxLayout->itemAt( index )->widget( );
		if( widget )
			rightHeight += widget->height( );
	}
	leftHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
	setNewSize( QSize( this->width( ), leftHeight ) );
}
bool NodePanel::appendInput( QWidget *input_component ) {
	int count = leftVectorBoxLayout->count( );
	leftVectorBoxLayout->insertWidget( count - 1, input_component, 0, Qt::AlignLeft | Qt::AlignTop );
	repaint( );
	return true;
}
bool NodePanel::removeInputItem( QWidget *output_component ) {
	int count = leftVectorBoxLayout->count( );
	for( int index = 0; index < count; ++index )
		if( leftVectorBoxLayout->itemAt( index )->widget( ) == output_component ) {
			leftVectorBoxLayout->removeWidget( output_component );
			repaint( );
			return true;
		}
	return false;
}
QWidget * NodePanel::removeInputItem( size_t index ) {
	int count = leftVectorBoxLayout->count( );
	if( count > index ) {
		auto widget = leftVectorBoxLayout->itemAt( index )->widget( );
		leftVectorBoxLayout->removeWidget( widget );
		repaint( );
		return widget;
	}
	return nullptr;
}
QWidget * NodePanel::getInputItem( size_t index ) const {
	int count = leftVectorBoxLayout->count( );
	if( count > index ) {
		auto widget = leftVectorBoxLayout->itemAt( index )->widget( );
		return widget;
	}
	return nullptr;
}
bool NodePanel::appendOutput( QWidget *output_component ) {
	int count = rightVectorBoxLayout->count( );
	rightVectorBoxLayout->insertWidget( count - 1, output_component, 0, Qt::AlignRight | Qt::AlignTop );
	repaint( );
	return true;
}
bool NodePanel::removeOutputItem( QWidget *output_component ) {
	int count = rightVectorBoxLayout->count( );
	for( int index = 0; index < count; ++index )
		if( rightVectorBoxLayout->itemAt( index )->widget( ) == output_component ) {
			rightVectorBoxLayout->removeWidget( output_component );
			repaint( );
			return true;
		}
	return false;
}
QWidget * NodePanel::removeOutputItem( size_t index ) {
	int count = rightVectorBoxLayout->count( );
	if( count > index ) {
		auto widget = rightVectorBoxLayout->itemAt( index )->widget( );
		repaint( );
		return widget;
	}
	return nullptr;
}
QWidget * NodePanel::getOutputItem( size_t index ) const {
	int count = rightVectorBoxLayout->count( );
	if( count > index ) {
		auto widget = rightVectorBoxLayout->itemAt( index )->widget( );
		return widget;
	}
	return nullptr;
}

NodePanel::NodePanel( QWidget *parent, Qt::WindowFlags f ): INodeComponent( parent, f ) {
	mainLayout = new QHBoxLayout( this );
	auto leftWidget = new QWidget( this );
	leftVectorBoxLayout = new QVBoxLayout( leftWidget );
	auto rightWidget = new QWidget( this );
	rightVectorBoxLayout = new QVBoxLayout( rightWidget );

	mainLayout->addWidget( leftWidget );
	mainLayout->addSpacerItem( new QSpacerItem( 100, 0, QSizePolicy::Expanding, QSizePolicy::Ignored ) );
	mainLayout->addWidget( rightWidget );

	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	
	leftVectorBoxLayout->setContentsMargins( 0, 0, 0, 0 );
	leftVectorBoxLayout->setSpacing( 0 );
	leftVectorBoxLayout->addSpacerItem( new QSpacerItem( 0, 100, QSizePolicy::Ignored, QSizePolicy::Expanding ) );
	
	rightVectorBoxLayout->setContentsMargins( 0, 0, 0, 0 );
	rightVectorBoxLayout->setSpacing( 0 );
	rightVectorBoxLayout->addSpacerItem( new QSpacerItem( 0, 100, QSizePolicy::Ignored, QSizePolicy::Expanding ) );
}
void NodePanel::showEvent( QShowEvent *event ) {
	//INodeComponent::showEvent( event );
	QWidget::showEvent( event );
	updateSize( );
}
