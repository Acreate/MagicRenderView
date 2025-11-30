#include "srackInfo.h"

#include "../tools/path.h"
SrackInfo::SrackInfo( const QString &file_source_name, const QString &call_function_name, size_t file_line ) : fileSourceName( path::relativeRootFilePath( file_source_name ) ), callFunctionName( call_function_name ), fileLine( file_line ) {
}
