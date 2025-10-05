#include "varAddPanleItemWidget.h"

#include <qboxlayout.h>
#include <QLabel.h>
#include <QMouseEvent>
#include <QPainter>
#include <qmenu.h>

#include "varEditorItemWidget.h"

#include "../varGenerateWidget.h"

#include "../../application/application.h"

#include "varEditorTypeItem/floatTypeItemWidget.h"
#include "varEditorTypeItem/intTypeItemWidget.h"
#include "varEditorTypeItem/stringTypeItemWidget.h"
#include "varEditorTypeItem/uIntTypeItemWidget.h"

#define emplace_editor_type_item_widget( item_type_ ) \
	appendType(item_type_::getStaticMetaObjectDir(  ), item_type_::getStaticMetaObjectName(  ), [] ( QWidget *parent ) {\
		return new item_type_( parent );\
	} )

bool VarAddPanleItemWidget::appendType( const QString &dir_name, const QString &class_name, const std_function< VarEditorItemWidget *( QWidget * ) > &create_fucntion ) {
	size_t count = createVector.size( );
	if( count == 0 ) {
		auto creatPairt = std_pairt( class_name, create_fucntion );
		auto createVectorPairt = std_vector_pairt< QString, std_function< VarEditorItemWidget *( QWidget * ) > >( 1 );
		createVectorPairt.data( )[ 0 ] = creatPairt;
		auto first = std_pairt( dir_name, createVectorPairt );
		createVector.emplace_back( first );
		return true;
	}

	size_t index = 0;
	auto pair = createVector.data( );
	for( ; index < count; ++index )
		if( pair[ index ].first == dir_name ) {
			// 是否存在
			size_t nameCount = pair[ index ].second.size( );
			if( nameCount != 0 ) {
				size_t nameIndex = 0;
				auto nameData = pair[ index ].second.data( );
				for( ; nameIndex < nameCount; ++nameIndex )
					if( nameData[ nameIndex ].first == class_name ) {
						nameData[ nameIndex ].second = create_fucntion;
						return true;
					}
			}
			pair[ index ].second.emplace_back( class_name, create_fucntion );
			return true;
		}

	return true;
}
VarAddPanleItemWidget::VarAddPanleItemWidget( VarGenerateWidget *parent ) : QWidget( parent ) {
	createMenu = nullptr;
	mainLayout = new QHBoxLayout( this );
	varGenerateWidget = parent;
	QLabel *titile;
	QLabel *ico;
	titile = new QLabel( tr( "添加变量组" ), this );
	mainLayout->addWidget( titile, 0, Qt::AlignCenter );
	ico = new QLabel( this );
	ico->setPixmap( QPixmap::fromImage( QImage( ":/ico/item_add.png" ) ) );
	mainLayout->addWidget( ico, 0, Qt::AlignCenter );

	emplace_editor_type_item_widget( UIntTypeItemWidget );
	emplace_editor_type_item_widget( IntTypeItemWidget );
	emplace_editor_type_item_widget( FloatTypeItemWidget );
	emplace_editor_type_item_widget( StringTypeItemWidget );
	updateInfo( );
}
bool VarAddPanleItemWidget::updateInfo( ) {
	if( createMenu != nullptr ) {
		createMenu->clear( );
		delete createMenu;
	}
	createMenu = new QMenu( this );
	size_t count = createVector.size( );

	size_t index = 0;
	auto pair = createVector.data( );
	for( ; index < count; ++index ) {
		QMenu *nameMenu = new QMenu( createMenu );
		QString &nameNenuTitle = pair[ index ].first;
		nameMenu->setTitle( nameNenuTitle );
		createMenu->addMenu( nameMenu );
		auto data = pair[ index ].second.data( );
		auto nameCount = pair[ index ].second.size( );
		size_t nameIndex = 0;
		for( ; nameIndex < nameCount; ++nameIndex ) {
			QString &actionTitleName = data[ nameIndex ].first;
			auto addAction = nameMenu->addAction( actionTitleName );
			auto function = data[ nameIndex ].second;
			connect( addAction, &QAction::triggered, [this, function]( ) {
				auto varEditorItemWidget = function( this );
				emit addClick( varEditorItemWidget );
			} );
		}
	}
	return true;
}
void VarAddPanleItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	auto pen = painter.pen( );
	int width = 5;
	pen.setWidth( width );
	pen.setColor( QColor( 190, 78, 32 ) );
	painter.setPen( pen );
	int doubleWidth = width * 2;
	painter.drawRect( width, width, this->width( ) - doubleWidth, this->height( ) - doubleWidth );
}
void VarAddPanleItemWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	createMenu->move( QCursor::pos( ) );
	createMenu->show( );
}
