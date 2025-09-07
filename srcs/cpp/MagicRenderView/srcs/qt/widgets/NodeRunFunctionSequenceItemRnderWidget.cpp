#include "./NodeRunFunctionSequenceItemRnderWidget.h"

#include "nodeRunSequenceWidget.h"

#include "../items/nodeRunFunctionSequenceItem.h"
NodeRunFunctionSequenceItemRnderWidget::NodeRunFunctionSequenceItemRnderWidget( NodeRunSequenceWidget *run_sequence_widget, NodeRunFunctionSequenceItem *run_function_sequence_item ) : QWidget( run_sequence_widget ), runSequenceWidget( run_sequence_widget ), runFunctionSequenceItem( run_function_sequence_item ) {
}
NodeRunFunctionSequenceItem * NodeRunFunctionSequenceItemRnderWidget::setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr<IFunctionDeclaration> &function_declaration, const QPoint &glob_point, const QPoint &set_point ) {

	// todo 实现匹配项的查找，插入新的项，创建新的ui

	NodeRunFunctionSequenceItem *  result = nullptr;

	return result;
}
