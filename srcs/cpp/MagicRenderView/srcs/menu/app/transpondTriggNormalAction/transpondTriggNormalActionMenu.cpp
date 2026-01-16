#include "../action/normalApplicationAction.h"
#include "../normalApplicationMenu.h"
#include "TranspondTriggNormalActionMenu.h"
void TranspondTriggNormalActionMenu::clearResource( ) {
	size_t index;
	for( index = 0; index < actionArrayCount; ++index )
		delete actionArrayPtr[ index ];
	actionArrayPtr = nullptr;
	actionArrayCount = 0;
	allAction.clear( );
	
	disconnect( this, &QMenu::triggered, this, &TranspondTriggNormalActionMenu::triggAction );
}
void TranspondTriggNormalActionMenu::triggAction( QAction *transpond_action_ptr ) {
	if( isThisNodemalAction( transpond_action_ptr ) == false )
		return;
	transpondTriggAction( ( NormalApplicationAction * ) transpond_action_ptr );
}
bool TranspondTriggNormalActionMenu::appendAction( NormalApplicationAction *append_action ) {
	if( append_action == nullptr )
		return false;
	size_t index = 0;
	for( ; index < actionArrayCount; ++index )
		if( actionArrayPtr[ index ] == append_action )
			return false;
	allAction.emplace_back( append_action );
	actionArrayPtr = allAction.data( );
	actionArrayCount = allAction.size( );
	append_action->setParent( this );
	QMenu::addAction( append_action );
	return true;
}
bool TranspondTriggNormalActionMenu::isThisNodemalAction( QAction *check_action ) {
	size_t index = 0;
	for( ; index < actionArrayCount; ++index )
		if( actionArrayPtr[ index ] == check_action )
			return true;
	return false;
}
bool TranspondTriggNormalActionMenu::init( ) {
	clearResource( );
	connect( this, &QMenu::triggered, this, &TranspondTriggNormalActionMenu::triggAction );
	return true;
}
TranspondTriggNormalActionMenu::TranspondTriggNormalActionMenu( ) {
	actionArrayCount = 0;
	actionArrayPtr = nullptr;
}
TranspondTriggNormalActionMenu::~TranspondTriggNormalActionMenu( ) {
}
