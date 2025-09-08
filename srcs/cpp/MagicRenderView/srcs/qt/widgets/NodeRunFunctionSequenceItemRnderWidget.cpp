#include "./NodeRunFunctionSequenceItemRnderWidget.h"

#include "nodeRunSequenceWidget.h"

#include "../items/nodeRunFunctionSequenceItem.h"
NodeRunFunctionSequenceItemRnderWidget::NodeRunFunctionSequenceItemRnderWidget( NodeRunFunctionSequenceItem *run_function_sequence_item ) : QWidget( run_function_sequence_item->runMainSequenceWidget ), runSequenceWidget( run_function_sequence_item->runMainSequenceWidget ), runFunctionSequenceItem( run_function_sequence_item ) {
}
