#include "./pathWidget.h"

#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <qboxlayout.h>
#include <qcoreapplication.h>

#include "../../../stack/varStack/IVarStack.h"
#include "../../../stack/varStack/base/baseVarStackEx.h"

#include "../../../type/ITypeObject.h"
#include "../../../type/baseType/nullTypeObject.h"
#include "../../../type/baseType/stringTypeObject.h"
PathWidget::PathWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	stringTypeObject = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< StringTypeObject >( );
	QWidget *subItem = new QWidget( this );
	mainLayout->addWidget( subItem );
	QHBoxLayout *subItemLayout = new QHBoxLayout( subItem );
	QPushButton *selectPath = new QPushButton( "路径", subItem );

	pathText = new QLineEdit( subItem );
	pathText->setPlaceholderText( "路径" );
	subItemLayout->addWidget( selectPath, 1 );
	subItemLayout->addWidget( pathText, 99 );
	connect( selectPath, &QPushButton::clicked, [subItem, this] {
		auto path = QFileDialog::getExistingDirectory( subItem, "路径", qApp->applicationDirPath( ) );
		if( path.isEmpty( ) )
			return;
		pathText->setText( QDir::cleanPath( path ) );
	} );

	subItem = new QWidget( this );
	mainLayout->addWidget( subItem );
	subItemLayout = new QHBoxLayout( subItem );
	selectPath = new QPushButton( "添加路径", this );

	appendPathText = new QLineEdit( subItem );
	appendPathText->setPlaceholderText( "路径" );
	subItemLayout->addWidget( selectPath, 1 );
	subItemLayout->addWidget( appendPathText, 99 );
	connect( selectPath, &QPushButton::clicked, [ this] {
		QFileInfo info( pathText->text( ) + "/" + appendPathText->text( ) );
		pathText->setText( QDir::cleanPath( info.absoluteFilePath( ) ) );
		setPath( QDir::cleanPath( info.absoluteFilePath( ) ) );
		emit pathText->editingFinished( );
	} );

	selectPath = new QPushButton( "清除路径", this );
	mainLayout->addWidget( selectPath );
	connect( selectPath, &QPushButton::clicked, [ this] {
		setPath( "" );
	} );

	connect( appendPathText, &QLineEdit::editingFinished, [this] {
		emit pathAppendNameChanged( QDir::cleanPath( appendPathText->text( ) ) );
	} );

	connect( pathText, &QLineEdit::editingFinished, [this] {
		setPath( pathText->text( ) );
		emit valueChanged( );
	} );
}
QString PathWidget::getPath( ) const {
	return pathText->text( );
}
bool PathWidget::setPath( const QString &new_text ) const {
	QFileInfo info( new_text + "/" );
	QString absoluteFilePath = QDir::cleanPath( info.absoluteFilePath( ) );
	pathText->setText( absoluteFilePath );
	stringTypeObject->setString( absoluteFilePath );
	if( *synObjPtr != nullptr )
		*synObjPtr = *stringTypeObject;
	return true;
}

void PathWidget::setPlaceholderText( const QString &placeholder_text ) const {
	pathText->setPlaceholderText( placeholder_text );
}
QString PathWidget::getPlaceholderText( ) const {
	return pathText->placeholderText( );
}
std_shared_ptr< ITypeObject > PathWidget::getValue( ) const {
	return stringTypeObject;
}
bool PathWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	if( *value == nullptr )
		return false;
	return setPath( value->toString( ) );
}
