#include "binCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

#include "validator/uint8Validator.h"

void BinCreateUnityNodeEditorScrollArea::editingFinished_Slot( ) {
	if( lineEdit != sender( ) )
		return;
	bool isOk;
	ulong uLong = lineEdit->text( ).toULong( &isOk );
	if( isOk == false )
		return;
	emit editingFinished_Signal( uLong );
}
BinCreateUnityNodeEditorScrollArea::BinCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint8_t current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {

	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	auto mainLayout = new QVBoxLayout( mainWidget );

	auto eidtorWidget = new QWidget( mainWidget );
	auto editorLayout = new QHBoxLayout( eidtorWidget );
	mainLayout->addWidget( eidtorWidget );

	auto title = new QLabel( tr( "值:" ), eidtorWidget );
	editorLayout->addWidget( title );

	lineEdit = new QLineEdit( eidtorWidget );
	editorLayout->addWidget( lineEdit );
	Uint8Validator *uint8Validator = new Uint8Validator( this );
	lineEdit->setValidator( uint8Validator );
	connect( lineEdit, &QLineEdit::editingFinished, this, &BinCreateUnityNodeEditorScrollArea::editingFinished_Slot );
}
void BinCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool BinCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
BinCreateUnityNodeEditorScrollArea::~BinCreateUnityNodeEditorScrollArea( ) {

}
