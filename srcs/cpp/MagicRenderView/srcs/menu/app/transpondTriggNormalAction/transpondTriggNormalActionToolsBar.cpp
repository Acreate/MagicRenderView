#include "transpondTriggNormalActionToolsBar.h"

#include "../action/normalApplicationAction.h"
void TranspondTriggNormalActionToolsBar::clearResource( ) {
	size_t index = 0;
	for( ; index < actionArrayCount; ++index )
		delete actionArrayPtr[ index ];
	actionArrayPtr = nullptr;
	actionArrayCount = 0;
	allAction.clear( );
	disconnect( this, &QToolBar::actionTriggered, this, &TranspondTriggNormalActionToolsBar::triggAction );
}
void TranspondTriggNormalActionToolsBar::triggAction( QAction *transpond_action_ptr ) {
	if( isThisNodemalAction( transpond_action_ptr ) == false )
		return;
	transpondTriggAction( ( NormalApplicationAction * ) transpond_action_ptr );
}
bool TranspondTriggNormalActionToolsBar::appendAction( NormalApplicationAction *append_action ) {
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
	QToolBar::addAction( append_action );
	return true;
}
bool TranspondTriggNormalActionToolsBar::isThisNodemalAction( QAction *check_action ) {
	size_t index = 0;
	for( ; index < actionArrayCount; ++index )
		if( actionArrayPtr[ index ] == check_action )
			return true;
	return false;
}
bool TranspondTriggNormalActionToolsBar::init( ) {
	clearResource( );
	connect( this, &QToolBar::actionTriggered, this, &TranspondTriggNormalActionToolsBar::triggAction );
	return true;
}
TranspondTriggNormalActionToolsBar::TranspondTriggNormalActionToolsBar( ) {
	actionArrayCount = 0;
	actionArrayPtr = nullptr;
}
TranspondTriggNormalActionToolsBar::~TranspondTriggNormalActionToolsBar( ) {

}
