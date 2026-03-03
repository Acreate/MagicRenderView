#include "nodeRunInfoData.h"
NodeRunInfoData::NodeRunInfoData( ) : QObject( ), builderDataTime( nullptr ), brforeRunDataTime( nullptr ), currentRunDataTime( nullptr ) { }
bool NodeRunInfoData::copyTargetToThis( const NodeRunInfoData *const other ) {
	if( this == nullptr || other == nullptr )
		return false;
	if( this == other )
		return true;
	currentFrame = other->currentFrame;
	maxFrame = other->maxFrame;
	runStop = other->runStop;
	ready = other->ready;
	nextRunNodeTime = other->nextRunNodeTime;
	builderDataTime = other->builderDataTime;
	brforeRunDataTime = other->brforeRunDataTime;
	currentRunDataTime = other->currentRunDataTime;
	buffNode = other->buffNode;
	currentNode = other->currentNode;
	oldNode = other->oldNode;
	builderNodeVector = other->builderNodeVector;
	builderBeginList = other->builderBeginList;
	builderReferenceSortVector = other->builderReferenceSortVector;
	runOverNodeVector = other->runOverNodeVector;
	createVector = other->createVector;
	pointVector = other->pointVector;
	functionVector = other->functionVector;
	nodeRunLinkVector = other->nodeRunLinkVector;
	functionStack = other->functionStack;
	createStack = other->createStack;
	pointStack = other->pointStack;
	return this;
}
