#ifndef COLORGENERATENODE_H_H_HEAD__FILE__
#define COLORGENERATENODE_H_H_HEAD__FILE__
#pragma once

#include "../../generateNode.h"

class UIntOutputPort;
class ColorOutputPort;
class GenerateInputPort;
class GenerateIntOutputPort;
class ColorGenerateNode : public GenerateNode {
	Q_OBJECT;
private:
	using TGenerateType = QColor;
protected:
	GenerateInputPort *generateInputPort;
	ColorOutputPort *outputVarPort;
	UIntOutputPort *outputIndexPort;
	UIntOutputPort *outputCountPort;
	size_t *arrayCount;
	size_t *arrayIndex;
	TGenerateType *currentIndexVar;
protected:
	std::vector< TGenerateType > *overVarPtr;
public:
	ColorGenerateNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool initArrayUintyTypeName( QString &change_array_unty_type_name ) override;
	bool updateLayout( ) override;
	virtual std::vector< TGenerateType > * getGenerateVarPtr( ) const;
	bool formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) override;
	bool toUint8VectorData( std::vector< uint8_t > &result_vector_data ) override;
protected:
	bool initVarPtr( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "生成/生成颜色" ) );
};

#endif // COLORGENERATENODE_H_H_HEAD__FILE__
