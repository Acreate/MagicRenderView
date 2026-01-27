#include "imageCreateUnityNodeEditorScrollArea.h"

#include <app/application.h>
#include <QDir>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <qpushbutton.h>
#include <QVBoxLayout>

ImageCreateUnityNodeEditorScrollArea::ImageCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, const QImage &current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	fileDialog = new QFileDialog( this );
	fileDialog->setWindowTitle( tr( "选择加载图像..." ) );
	fileDialog->setNameFilter( tr( "图像 (*.png)" ) );
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );

	buttonCompoentWidget = new QWidget( mainWidget );
	QHBoxLayout *buttonCompoentLayout = new QHBoxLayout( buttonCompoentWidget );
	pathLoadFileButton = new QPushButton( tr( "加载图像" ), buttonCompoentWidget );
	buttonCompoentLayout->addWidget( pathLoadFileButton );
	connect( pathLoadFileButton, &QPushButton::clicked, this, &ImageCreateUnityNodeEditorScrollArea::onLoadPng );
	mainLayout->addWidget( buttonCompoentWidget );

	showImageLabel = new QLabel( mainWidget );
	mainLayout->addWidget( showImageLabel );
}
void ImageCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}
bool ImageCreateUnityNodeEditorScrollArea::eventFilter( QObject *watched, QEvent *event ) {
	return EditorNodeInfoScrollArea::eventFilter( watched, event );
}
void ImageCreateUnityNodeEditorScrollArea::onLoadPng( ) {
	if( lastLoadFilePath.isEmpty( ) )
		lastLoadFilePath = QDir::currentPath( );
	fileDialog->exec( );
	auto selectedFiles = fileDialog->selectedFiles( );
	if( selectedFiles.size( ) == 0 )
		return;
	lastLoadFilePath = selectedFiles.first( );
	if( currentVar.load( lastLoadFilePath ) == false )
		return;
	auto fromImage = QPixmap::fromImage( currentVar );
	showImageLabel->setPixmap( fromImage );
	emit editingFinished_Signal( currentVar );
}

bool ImageCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
ImageCreateUnityNodeEditorScrollArea::~ImageCreateUnityNodeEditorScrollArea( ) {

}
void ImageCreateUnityNodeEditorScrollArea::setCurrentVar( const QImage &current_var ) {
	currentVar = current_var.copy( );
	auto fromImage = QPixmap::fromImage( currentVar );
	showImageLabel->setPixmap( fromImage );
}
