/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

#include "ImplicitBoolConversionCheck.h"
#include "IntegerLiteralConversion.h"

namespace clang::tidy::misra {
class CMakeClangTidyModule : public ClangTidyModule
{
  public:
    void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override
    {
        CheckFactories.registerCheck<ImplicitBoolConversionCheck>("mchp-misra-c-implicit-bool");
        CheckFactories.registerCheck<IntegerLiteralConversion>("mchp-misra-c-integer-literal");
    }
};

static ClangTidyModuleRegistry::Add<CMakeClangTidyModule> X1(
    "mchp-misra-c-implicit-bool",
    "Adds lint checks for the CMake code base.");

static ClangTidyModuleRegistry::Add<CMakeClangTidyModule> X2("mchp-misra-c-integer-literal",
                                                             "Add 'U' to integer literals");
} // namespace clang::tidy::misra
