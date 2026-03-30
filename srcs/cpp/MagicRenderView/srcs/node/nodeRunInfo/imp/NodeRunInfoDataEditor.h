#ifndef NODERUNINFODATAEDITOR_H_H_HEAD__FILE__
#define NODERUNINFODATAEDITOR_H_H_HEAD__FILE__
#include <qtmetamacros.h>

#include "NodeRunInfoDataOnlyRead.h"

class NodeRunInfoDataEditor : public NodeRunInfoDataOnlyRead {
	Q_OBJECT;
public:
	bool copyNodeRunInfoDataToThis( const NodeRunInfoData *const copy_target_ptr ) override;
	void setBrforeRunDataTime( QDateTime *brfore_run_data_time ) override;
	void setBuffNode( Node *buff_node ) override;
	void setBuilderBeginList( const std::vector< Node * > &builder_begin_list ) override;
	void setBuilderDataTime( QDateTime *builder_data_time ) override;
	void setBuilderNodeVector( const std::vector< Node * > &builder_node_vector ) override;
	void setBuilderReferenceSortVector( const std::vector< Node * > &builder_reference_sort_vector ) override;
	void setCurrentFrame( size_t current_frame ) override;
	void setCurrentNode( Node *current_node ) override;
	void setCurrentRunDataTime( QDateTime *current_run_data_time ) override;
	void setMaxFrame( size_t max_frame ) override;
	void setNextRunNodeTime( qint64 next_run_node_time ) override;
	void setOldNode( Node *old_node ) override;
	void setReady( bool ready ) override;
	void setRunOverNodeVector( const std::vector< Node * > &run_over_node_vector ) override;
	void setRunStop( bool run_stop ) override;
};

#endif // NODERUNINFODATAEDITOR_H_H_HEAD__FILE__
