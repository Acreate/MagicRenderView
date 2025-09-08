#include "./NodeRunSequenceItemFunctionWidget.h"

#include "nodeRunSequenceWidget.h"
NodeRunSequenceItemFunctionWidget::NodeRunSequenceItemFunctionWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item ) : QWidget( node_run_function_sequence_item->runMainSequenceWidget ), nodeRunFunctionSequenceItem( node_run_function_sequence_item ) {
}
