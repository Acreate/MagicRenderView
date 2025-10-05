#include "varGenerateWidget.h"

#include <QPainter>
#include <qboxlayout.h>

#include "mainWidget.h"

#include <qt/varType/I_Var.h>

#include <qt/application/application.h>

#include "varGenerateWidgetItem/varAddPanleItemWidget.h"
#include "varGenerateWidgetItem/varEditorItemWidget.h"

VarGenerateWidget::~VarGenerateWidget( ) {
	size_t count = mainWidgetGenerateVar.size( );
	auto dataPtr = mainWidgetGenerateVar.data( );
	size_t index = 0;

	for( ; index < count; ++index )
		for( auto item : dataPtr[ index ].second )
			delete item;
}
VarGenerateWidget::VarGenerateWidget( QWidget *parent_widget ) : QWidget( parent_widget ) {
	appInstance = Application::getApplicationInstancePtr( );
	varGenerate = appInstance->getVarGenerate( );
	keyFirst = "Application/MainWindow/MainWidget/VarGenerateWidget";

	mainLayout = new QVBoxLayout( this );
	varAddPanleItemWidget = new VarAddPanleItemWidget( this );
	// 添加添加功能的项
	mainLayout->addWidget( varAddPanleItemWidget );
	connect( varAddPanleItemWidget, &VarAddPanleItemWidget::addClick, this, &VarGenerateWidget::addVarEditorPanle );
	// 顶针
	mainLayout->addSpacerItem( new QSpacerItem( 100, 100, QSizePolicy::Expanding, QSizePolicy::Expanding ) );
}

VarGenerateWidget::VarGenerateWidget( ) : VarGenerateWidget( nullptr ) {
}
void VarGenerateWidget::setMainWidget( MainWidget *const main_widget ) { mainWidget = main_widget; }
void VarGenerateWidget::addVarEditorPanle( VarEditorItemWidget *add_target_widget_ptr ) {
	mainLayout->insertWidget( mainLayout->count( ) - 2, add_target_widget_ptr );
	
	size_t count = editorItemWidgets.size( );
	if( count != 0 ) {
		auto dataPtr = editorItemWidgets.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( dataPtr[ index ] == nullptr ) {
				dataPtr[ index ] = add_target_widget_ptr;
				break;
			}
		if( index == count )
			editorItemWidgets.emplace_back( add_target_widget_ptr );
	} else
		editorItemWidgets.emplace_back( add_target_widget_ptr );
}
void VarGenerateWidget::delVarEditorPanle( VarEditorItemWidget *remove_widget_item ) {
	delete remove_widget_item;
	size_t count = editorItemWidgets.size( );
	auto dataPtr = editorItemWidgets.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( dataPtr[ index ] == remove_widget_item ) {
			dataPtr[ index ] = nullptr;
			break;
		}
}
void VarGenerateWidget::resetSizeVarEditorPanle( VarEditorItemWidget *remove_widget_item, const QSize &old_size, const QSize &new_size ) {
	//auto size = this->size( );
	//int currentWidth = size.width( );
	//int compWidth;
	//size_t count = editorItemWidgets.size( );
	//auto dataPtr = editorItemWidgets.data( );
	//size_t index = 0;
	//for( ; index < count; ++index )
	//	if( compWidth = dataPtr[ index ]->width( ), compWidth > currentWidth )
	//		currentWidth = compWidth;
}
void VarGenerateWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	//QPainter painter( this );
	//painter.fillRect( contentsRect( ), QColor( 107, 113, 111 ) );
}
