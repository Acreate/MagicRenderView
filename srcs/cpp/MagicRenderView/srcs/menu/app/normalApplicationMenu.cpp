#include "normalApplicationMenu.h"

void NormalApplicationMenu::transpondTriggAction( NormalApplicationAction *action ) {
	emit trigg_action_signal( this, action );
}
void NormalApplicationMenu::clearResource( ) {
	TranspondTriggNormalActionMenu::clearResource( );
	size_t index;
	if( menuArrayCount ) {
		for( index = 0; index < menuArrayCount; ++index )
			delete menuArrayPtr[ index ];
		menuArrayPtr = nullptr;
		menuArrayCount = 0;
		allMenu.clear( );
	}
}
void NormalApplicationMenu::triggMenuActionSlot( NormalApplicationMenu *normal_application_menu, NormalApplicationAction *action ) {
	emit this->trigg_action_signal( this, action );
}
NormalApplicationMenu::NormalApplicationMenu( ) {
	menuArrayPtr = nullptr;
	menuArrayCount = 0;
}
bool NormalApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( application_menu_stack == nullptr )
		return false;
	if( TranspondTriggNormalActionMenu::init( ) == false )
		return false;
	return true;
}
bool NormalApplicationMenu::appendMenu( NormalApplicationMenu *append_menu ) {
	if( append_menu == nullptr )
		return false;
	size_t index = 0;
	for( ; index < actionArrayCount; ++index )
		if( menuArrayPtr[ index ] == append_menu )
			return false;
	allMenu.emplace_back( append_menu );
	menuArrayPtr = allMenu.data( );
	menuArrayCount = allMenu.size( );
	//append_menu->setParent( this );
	QMenu::addMenu( append_menu );
	connect( append_menu, &NormalApplicationMenu::trigg_action_signal, this, &NormalApplicationMenu::triggMenuActionSlot );
	return true;
}
NormalApplicationMenu::~NormalApplicationMenu( ) {
	emit release_signal( this );
}
