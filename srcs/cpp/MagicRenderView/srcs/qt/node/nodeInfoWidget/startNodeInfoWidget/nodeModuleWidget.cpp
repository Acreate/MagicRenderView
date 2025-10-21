#include "nodeModuleWidget.h"
NodeModuleWidget::NodeModuleWidget( const std_vector< std_vector< NodeItemInfo * > > *run_list, QWidget *parent ) : QWidget( parent ), runList( run_list ) { }
const std_vector< std_vector< NodeItemInfo * > > * NodeModuleWidget::getRunList( ) const { return runList; }
void NodeModuleWidget::setRunList( const std_vector< std_vector< NodeItemInfo * > > *run_list ) { runList = run_list; }
