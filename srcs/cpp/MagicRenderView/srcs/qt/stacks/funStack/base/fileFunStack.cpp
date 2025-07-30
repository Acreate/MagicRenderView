#include "./fileFunStack.h"

#include "../../../functionDeclaration/file/fileContent.h"
#include "../../../functionDeclaration/file/fileDir.h"
#include "../../../functionDeclaration/file/fileInfo.h"
FileFunStack::FileFunStack( ) {
	name = "文件系统";
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new FileInfo ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new FileDir ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new FileContent ) );
}
