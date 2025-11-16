#ifndef GENERATEVARNODEITEM_H_H_HEAD__FILE__
#define GENERATEVARNODEITEM_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class GenerateVarNodeItem : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenerateVarNodeItem( ) { }
	GenerateVarNodeItem( GenerateListScrollArea *node_info_scroll_area ) : NodeItem( node_info_scroll_area ) { }
public:
	size_t toBinData( std_vector< uint8_t > &result_data ) const override;
	size_t loadBinData( const uint8_t *source_data_ptr, const size_t &source_data_count ) override;
public:
	Def_Last_Mate_Node_Type( GenerateVar );
};
#endif // GENERATEVARNODEITEM_H_H_HEAD__FILE__
