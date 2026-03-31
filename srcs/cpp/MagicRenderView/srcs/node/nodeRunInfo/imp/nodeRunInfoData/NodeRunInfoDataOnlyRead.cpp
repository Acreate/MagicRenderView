#include "NodeRunInfoDataOnlyRead.h"
bool NodeRunInfoDataOnlyRead::isReady( ) const {
	return NodeRunInfoData::isReady( );
}
bool NodeRunInfoDataOnlyRead::isRunStop( ) const {
	return NodeRunInfoData::isRunStop( );
}
QDateTime * NodeRunInfoDataOnlyRead::getBrforeRunDataTime( ) const {
	return NodeRunInfoData::getBrforeRunDataTime( );
}
Node * NodeRunInfoDataOnlyRead::getBuffNode( ) const {
	return NodeRunInfoData::getBuffNode( );
}
const std::vector<Node *> & NodeRunInfoDataOnlyRead::getBuilderBeginVector( ) const {
	return NodeRunInfoData::getBuilderBeginVector( );
}
QDateTime * NodeRunInfoDataOnlyRead::getBuilderDataTime( ) const {
	return NodeRunInfoData::getBuilderDataTime( );
}
const std::vector<Node *> & NodeRunInfoDataOnlyRead::getBuilderNodeVector( ) const {
	return NodeRunInfoData::getBuilderNodeVector( );
}
size_t NodeRunInfoDataOnlyRead::getCurrentFrame( ) const {
	return NodeRunInfoData::getCurrentFrame( );
}
Node * NodeRunInfoDataOnlyRead::getCurrentNode( ) const {
	return NodeRunInfoData::getCurrentNode( );
}
QDateTime * NodeRunInfoDataOnlyRead::getCurrentRunDataTime( ) const {
	return NodeRunInfoData::getCurrentRunDataTime( );
}
size_t NodeRunInfoDataOnlyRead::getMaxFrame( ) const {
	return NodeRunInfoData::getMaxFrame( );
}
qint64 NodeRunInfoDataOnlyRead::getNextRunNodeTime( ) const {
	return NodeRunInfoData::getNextRunNodeTime( );
}
Node * NodeRunInfoDataOnlyRead::getOldNode( ) const {
	return NodeRunInfoData::getOldNode( );
}
const std::vector<Node *> & NodeRunInfoDataOnlyRead::getRunOverNodeVector( ) const {
	return NodeRunInfoData::getRunOverNodeVector( );
}
const std::list<Node *> & NodeRunInfoDataOnlyRead::getAwaitNodeList( ) const {
	return NodeRunInfoData::getAwaitNodeList( );
}
const std::list<Node *> & NodeRunInfoDataOnlyRead::getCreateNodeList( ) const {
	return NodeRunInfoData::getCreateNodeList( );
}
const std::list<Node *> & NodeRunInfoDataOnlyRead::getFunctionNodeList( ) const {
	return NodeRunInfoData::getFunctionNodeList( );
}
const std::list<Node *> & NodeRunInfoDataOnlyRead::getJumpNodeList( ) const {
	return NodeRunInfoData::getJumpNodeList( );
}
