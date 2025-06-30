//===--- IntegerLiteralConversion.cpp - clang-tidy----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "IntegerLiteralConversion.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"
#include "clang/Tooling/FixIt.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

IntegerLiteralConversion::IntegerLiteralConversion(StringRef Name, ClangTidyContext *Context)
    : ClangTidyCheck(Name, Context)
{
}

void IntegerLiteralConversion::registerMatchers(MatchFinder *Finder)
{

    Finder
        ->addMatcher(traverse(TK_AsIs,
                              integerLiteral(hasType(asString("int")),
                                             hasParent(implicitCastExpr(anyOf(
                                                 hasType(hasCanonicalType(asString("unsigned int"))),
                                                 hasType(hasCanonicalType(asString("size_t")))))))
                                  .bind("intLitToUnsigned")),
                     this);

    Finder
        ->addMatcher(traverse(TK_AsIs,
                              integerLiteral(hasType(asString("int")),
                                             anyOf(hasParent(binaryOperator(hasOperatorName("<<"))),
                                                   hasParent(binaryOperator(hasOperatorName(">>"))),
                                                   hasParent(binaryOperator(hasOperatorName("&"))),
                                                   hasParent(binaryOperator(hasOperatorName("|"))),
                                                   hasParent(binaryOperator(hasOperatorName("%")))))
                                  .bind("intLitToUnsigned")),
                     this);

    Finder->addMatcher(traverse(TK_AsIs,
                                binaryOperator(hasOperatorName("/"),
                                               hasLHS(implicitCastExpr(hasDescendant(
                                                   implicitCastExpr(hasType(isUnsignedInteger()))))),
                                               hasRHS(integerLiteral(hasType(asString("int")))
                                                          .bind("intLitToUnsigned")))),
                       this);

    Finder
        ->addMatcher(traverse(TK_AsIs,
                              binaryOperator(hasOperatorName("/"),
                                             hasLHS(integerLiteral(hasType(asString("int")))
                                                        .bind("intLitToUnsigned")),
                                             hasRHS(implicitCastExpr(hasDescendant(implicitCastExpr(
                                                 hasType(isUnsignedInteger()))))))),
                     this);
}

void IntegerLiteralConversion::check(const MatchFinder::MatchResult &Result)
{
    if (const auto *Cast = Result.Nodes.getNodeAs<IntegerLiteral>("intLitToUnsigned")) {

        const SourceManager &SM = *Result.SourceManager;
        SourceLocation       Loc = Cast->getBeginLoc();

        auto Diag = diag(Loc, "Integer literal should be unsigned");

        SourceLocation EndLoc =
            Lexer::getLocForEndOfToken(Cast->getEndLoc(), 0, SM, Result.Context->getLangOpts());

        // Skip if the literal comes from a macro
        if (!Loc.isMacroID()) {
            Diag << FixItHint::CreateInsertion(EndLoc, "U");
        }
    }
}

} // namespace clang::tidy::misra
