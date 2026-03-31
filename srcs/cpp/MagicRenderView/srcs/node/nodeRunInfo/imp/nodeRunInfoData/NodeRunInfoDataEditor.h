#ifndef NODERUNINFODATAEDITOR_H_H_HEAD__FILE__
#define NODERUNINFODATAEDITOR_H_H_HEAD__FILE__
#include <qtmetamacros.h>

#include "NodeRunInfoDataOnlyRead.h"

class NodeRunInfoDataEditor : public NodeRunInfoDataOnlyRead {
	Q_OBJECT;
public:
	bool copyNodeRunInfoDataToThis( const NodeRunInfoData *const copy_target_ptr ) override;
	bool copyNodeRunInfoDataToThis( const NodeRunInfoData &copy_target_instance ) override;
	void clear( ) override;
};

#endif // NODERUNINFODATAEDITOR_H_H_HEAD__FILE__
