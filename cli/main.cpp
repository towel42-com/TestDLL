#include "Library.h"

#ifdef _WIN32
#include "wrapper_win.h"
#define _CSharedLibraryWrapper CSharedLibraryWrapperWin
#else
#include "wrapper_linux.h"
#define _CSharedLibraryWrapper CSharedLibraryWrapperLinux
#endif

//##include "StubbedSharedLibrary.h"
//##include "ProperSharedLibrary.h"

class CStubbedSharedLibrary;
class CProperSharedLibrary;

#include <iostream>
#include <memory>

int main( int argc, char ** argv )
{
#ifdef _WIN32
    SetDefaultDllDirectories( LOAD_LIBRARY_SEARCH_DEFAULT_DIRS );
    if( !SymInitialize( GetCurrentProcess(), NULL, TRUE ) )
    {
        std::cerr << "could not initialize symbols" << std::endl;
        std::cerr << "    " << getLastError( "SymInitialize" ) << std::endl;
        return -1;
    }
#endif

    std::cout << "Running from: " << getCWD() << "\n";

    for( int ii = 0; ii < argc; ++ii )
    {
        auto stubbedLibWrapper = std::make_shared< _CSharedLibraryWrapper< CStubbedSharedLibrary > >( "StubbedSharedLibrary" );
        auto properLibWrapper = std::make_shared< _CSharedLibraryWrapper< CProperSharedLibrary > >( "ProperSharedLibrary" );

        if( ii == 0 )
        {
            std::cout
                << "Found Stubbed Shared Library at '" << stubbedLibWrapper->path() << std::endl
                << "Found Proper Shared Library at '" << properLibWrapper->path() << std::endl
                << "===================================================\n"
                ;
        }

        std::cout << "Original String: '" << argv[ ii ] << "\n";

        stubbedLibWrapper->create( argv[ ii ] );
        std::cout << "    Dynamically Loaded Stubbed Library Results: '" << stubbedLibWrapper->string() << "'\n";

        properLibWrapper->create( argv[ ii ] );
        std::cout << "    Dynamically Loaded Proper Library Results: '" << properLibWrapper->string() << "'\n";

        //auto stubbedLibStaticBound = new CStubbedSharedLibrary( argv[ ii ] );
        //std::cout << "    Statically bound Stubbed Library Results: '" << stubbedLibStaticBound->string() << "'\n";

        //auto properLibStaticBound = new CProperSharedLibrary( argv[ ii ] );
        //std::cout << "    Statically bound Proper Library Results: '" << properLibStaticBound->string() << "'\n";
    }

}
