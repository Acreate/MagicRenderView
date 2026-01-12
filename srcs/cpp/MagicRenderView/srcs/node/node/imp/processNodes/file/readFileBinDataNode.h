#ifndef READFILEBINDATANODE_H_H_HEAD__FILE__
#define READFILEBINDATANODE_H_H_HEAD__FILE__
#pragma once

#include "../../../processNode.h"
class UIntOutputPort;
class BinVectorOutputPort;
class StringInputPort;
class ReadFileBinDataNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort* filePathInputPort;
	BinVectorOutputPort* outBinVectorPort;
	UIntOutputPort* outVectorCountPort;
	std::vector<uint8_t>* outVectorPtr;
	uint64_t* outVectorCountPtr;
public:
	ReadFileBinDataNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "文件/读取/二进制" ) );
};
#endif // READFILEBINDATANODE_H_H_HEAD__FILE__
