#include "colorCreateUnityNodeEditorScrollArea.h"

#include <define/castMacro.h>
#include <qcoreevent.h>
#include <QLabel>
#include <QColorDialog>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPainter>

void ColorCreateUnityNodeEditorScrollArea::colorDialogFinished_Slot( QColor var ) {
	currentVar = var;
	repaint( );
	emit editingFinished_Signal( var );
}
ColorCreateUnityNodeEditorScrollArea::ColorCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, QColor current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainWidget->installEventFilter( this );
	colorDialog = new QColorDialog( this );
	colorDialog->setWindowTitle( tr( "选择颜色" ) );
	connect( colorDialog, &QColorDialog::currentColorChanged, this, &ColorCreateUnityNodeEditorScrollArea::colorDialogFinished_Slot );
}
ColorCreateUnityNodeEditorScrollArea::~ColorCreateUnityNodeEditorScrollArea( ) {
	delete colorDialog;
}
void ColorCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}
bool ColorCreateUnityNodeEditorScrollArea::eventFilter( QObject *watched, QEvent *event ) {
	if( watched != mainWidget )
		return EditorNodeInfoScrollArea::eventFilter( watched, event );
	QPainter *painter;
	QMouseEvent *mouseEvent;
	switch( event->type( ) ) {
		case QEvent::Paint :
			painter = new QPainter( );
			painter->begin( mainWidget );
			painter->setPen( currentVar );
			painter->fillRect( 0, 0, mainWidget->width( ), mainWidget->height( ), currentVar );
			painter->end( );
			delete painter;
			return true;
		case QEvent::MouseButtonRelease :
			Reinterpret_Cast( mouseEvent, event );
			if( mouseEvent == nullptr )
				return false;
			switch( mouseEvent->button( ) ) {
				case Qt::LeftButton :
					colorDialog->setCurrentColor( currentVar );
					colorDialog->move( this->mapToGlobal( QPoint( 0, 0 ) ) );
					colorDialog->show( );
					colorDialog->raise( );
					break;
			}
			return true;
	}
	return false;
}
bool ColorCreateUnityNodeEditorScrollArea::event( QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::Show :
			colorDialog->setFixedSize( this->size( ) );
			break;
	}
	return EditorNodeInfoScrollArea::event( event );
}

bool ColorCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
void ColorCreateUnityNodeEditorScrollArea::setCurrentVar( QColor current_var ) {
	currentVar = current_var;
}
