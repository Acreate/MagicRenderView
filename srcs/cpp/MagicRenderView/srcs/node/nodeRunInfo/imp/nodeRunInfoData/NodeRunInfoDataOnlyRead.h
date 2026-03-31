#ifndef NODERUNINFODATAONLYREAD_H_H_HEAD__FILE__
#define NODERUNINFODATAONLYREAD_H_H_HEAD__FILE__
#include "../../nodeRunInfoData.h"

class NodeRunInfoDataOnlyRead : public NodeRunInfoData {
	Q_OBJECT;
public:
	bool isReady( ) const override;
	bool isRunStop( ) const override;
	QDateTime * getBrforeRunDataTime( ) const override;
	Node * getBuffNode( ) const override;
	const std::vector< Node * > & getBuilderBeginVector( ) const override;
	QDateTime * getBuilderDataTime( ) const override;
	const std::vector< Node * > & getBuilderNodeVector( ) const override;
	size_t getCurrentFrame( ) const override;
	Node * getCurrentNode( ) const override;
	QDateTime * getCurrentRunDataTime( ) const override;
	size_t getMaxFrame( ) const override;
	qint64 getNextRunNodeTime( ) const override;
	Node * getOldNode( ) const override;
	const std::vector< Node * > & getRunOverNodeVector( ) const override;

	const std::list<Node *> & getAwaitNodeList( ) const override;
	const std::list<Node *> & getCreateNodeList( ) const override;
	const std::list<Node *> & getFunctionNodeList( ) const override;
	const std::list<Node *> & getJumpNodeList( ) const override;
};

#endif // NODERUNINFODATAONLYREAD_H_H_HEAD__FILE__
