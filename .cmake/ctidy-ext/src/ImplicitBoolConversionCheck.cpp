//===--- ImplicitBoolConversionCheck.cpp - clang-tidy----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ImplicitBoolConversionCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"
#include "clang/Tooling/FixIt.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misra {

ImplicitBoolConversionCheck::ImplicitBoolConversionCheck(StringRef Name, ClangTidyContext *Context)
    : ClangTidyCheck(Name, Context)
{
}

void ImplicitBoolConversionCheck::registerMatchers(MatchFinder *Finder)
{
    const auto parent =
        anyOf(hasParent(binaryOperator(hasOperatorName("&&"))),
              hasParent(binaryOperator(hasOperatorName("||"))),
              hasParent(unaryOperator(hasOperatorName("!"),
                                      optionally(hasParent(unaryOperator(hasOperatorName("!"))
                                                               .bind("notnot"))))
                            .bind("not")),
              hasParent(stmt(anyOf(ifStmt(), whileStmt()))));

#if 0
    Finder->addMatcher(
        traverse(TK_AsIs,
            implicitCastExpr(
                anyOf(
                    hasType(isSignedInteger()),
                    hasType(isUnsignedInteger())
                ),

                anyOf(
                    hasDescendant(
                        memberExpr(
                            anyOf(
                                hasType(asString("int32_t")),
                                hasType(asString("int16_t")),
                                hasType(asString("int8_t")),
                                hasType(asString("int")),
                                hasType(asString("short int")),
                                hasType(asString("ssize_t")),

                                hasType(asString("uint32_t")),
                                hasType(asString("uint16_t")),
                                hasType(asString("uint8_t")),
                                hasType(asString("unsigned int")),
                                hasType(asString("unsigned short int")),
                                hasType(asString("size_t")),

                                hasType(asString("char"))//,

                                //hasType(isAnyPointer())
                            )
                        ).bind("memberExpr")
                    ),

                    hasDescendant(
                        declRefExpr(
                            anyOf(
                                hasType(asString("int32_t")),
                                hasType(asString("int16_t")),
                                hasType(asString("int8_t")),
                                hasType(asString("int")),
                                hasType(asString("short int")),
                                hasType(asString("ssize_t")),

                                hasType(asString("uint32_t")),
                                hasType(asString("uint16_t")),
                                hasType(asString("uint8_t")),
                                hasType(asString("unsigned int")),
                                hasType(asString("unsigned short int")),
                                hasType(asString("size_t")),

                                hasType(asString("char"))//,

                                //hasType(isAnyPointer())
                            )
                        ).bind("declRefExpr")
                    )
                ),

                anyOf(
                    hasParent(binaryOperator(hasOperatorName("&&"))),
                    hasParent(binaryOperator(hasOperatorName("||"))),
                    hasParent(
                        unaryOperator(
                            hasOperatorName("!"),
                            hasParent(
                                unaryOperator(
                                    hasOperatorName("!")).bind("notnot"))
                        ).bind("not")
                    ),
                    hasParent(stmt(anyOf(ifStmt(), whileStmt())))
                ),

                optionally(hasParent(stmt().bind("parentStmt")))
            )

            .bind("castToBool")
        ),
        this
    );

    Finder->addMatcher(
        traverse(TK_AsIs,
            implicitCastExpr(
                anyOf(
                    hasType(isSignedInteger()),
                    hasType(isUnsignedInteger())
                ),

                anyOf(
                    hasDescendant(
                        memberExpr(
                            anyOf(
                                hasType(asString("int32_t")),
                                hasType(asString("int16_t")),
                                hasType(asString("int8_t")),
                                hasType(asString("int")),
                                hasType(asString("short int")),
                                hasType(asString("ssize_t"))
                            )
                        ).bind("memberExpr")
                    ),

                    hasDescendant(
                        declRefExpr(
                            anyOf(
                                hasType(asString("int32_t")),
                                hasType(asString("int16_t")),
                                hasType(asString("int8_t")),
                                hasType(asString("int")),
                                hasType(asString("short int")),
                                hasType(asString("ssize_t"))
                            )
                        ).bind("declRefExpr")
                    )
                ),

                anyOf(
                    hasParent(binaryOperator(hasOperatorName("&&"))),
                    hasParent(binaryOperator(hasOperatorName("||"))),
                    hasParent(
                        unaryOperator(
                            hasOperatorName("!"),
                            hasParent(
                                unaryOperator(
                                    hasOperatorName("!")).bind("notnot"))
                        ).bind("not")
                    ),
                    hasParent(stmt(anyOf(ifStmt(), whileStmt())))
                ),

                optionally(hasParent(stmt().bind("parentStmt")))
            )

            .bind("castToBool")
        ),
        this
    );
#endif

    ////////////////////////////////////////////////////////////////////////////
    Finder->addMatcher(traverse(TK_AsIs,
                                callExpr(anyOf(hasType(asString("int32_t")),
                                               hasType(asString("int16_t")),
                                               hasType(asString("int8_t")), hasType(asString("int")),
                                               hasType(asString("short int")),
                                               hasType(asString("ssize_t"))),
                                         parent, optionally(hasParent(stmt().bind("parentStmt"))))
                                    .bind("castIntToBool")),
                       this);

    Finder->addMatcher(traverse(TK_AsIs,
                                callExpr(anyOf(hasType(asString("uint32_t")),
                                               hasType(asString("uint16_t")),
                                               hasType(asString("uint8_t")),
                                               hasType(asString("unsigned int")),
                                               hasType(asString("unsigned")),
                                               hasType(asString("unsigned short int")),
                                               hasType(asString("size_t"))),
                                         parent, optionally(hasParent(stmt().bind("parentStmt"))))
                                    .bind("castUIntToBool")),
                       this);

    Finder->addMatcher(traverse(TK_AsIs, callExpr(hasType(isAnyPointer()), parent,
                                                  optionally(hasParent(stmt().bind("parentStmt"))))
                                             .bind("castPtrToBool")),
                       this);

    Finder->addMatcher(traverse(TK_AsIs, callExpr(hasType(asString("char")), parent,
                                                  optionally(hasParent(stmt().bind("parentStmt"))))
                                             .bind("castCharToBool")),
                       this);

    ////////////////////////////////////////////////////////////////////////////
    Finder->addMatcher(
        traverse(TK_AsIs,
                 implicitCastExpr(
                     anyOf(hasDescendant(memberExpr(anyOf(hasType(asString("int32_t")),
                                                          hasType(asString("int16_t")),
                                                          hasType(asString("int8_t")),
                                                          hasType(asString("int")),
                                                          hasType(asString("short int")),
                                                          hasType(asString("ssize_t"))))),
                           hasDescendant(declRefExpr(anyOf(hasType(asString("int32_t")),
                                                           hasType(asString("int16_t")),
                                                           hasType(asString("int8_t")),
                                                           hasType(asString("int")),
                                                           hasType(asString("short int")),
                                                           hasType(asString("ssize_t"))))),
                           hasDescendant(implicitCastExpr(anyOf(hasType(asString("int32_t")),
                                                                hasType(asString("int16_t")),
                                                                hasType(asString("int8_t")),
                                                                hasType(asString("int")),
                                                                hasType(asString("short int")),
                                                                hasType(asString("ssize_t"))))),
                           hasDescendant(unaryOperator(anyOf(hasType(asString("int32_t")),
                                                             hasType(asString("int16_t")),
                                                             hasType(asString("int8_t")),
                                                             hasType(asString("int")),
                                                             hasType(asString("short int")),
                                                             hasType(asString("ssize_t"))),
                                                       hasOperatorName("*")))),

                     parent, optionally(hasParent(stmt().bind("parentStmt"))))
                     .bind("implicitCastIntToBool")),
        this);

    Finder->addMatcher(
        traverse(TK_AsIs,
                 implicitCastExpr(
                     anyOf(hasDescendant(memberExpr(anyOf(hasType(asString("uint32_t")),
                                                          hasType(asString("uint16_t")),
                                                          hasType(asString("uint8_t")),
                                                          hasType(asString("unsigned int")),
                                                          hasType(asString("unsigned short int")),
                                                          hasType(asString("size_t"))))),
                           hasDescendant(declRefExpr(anyOf(hasType(asString("uint32_t")),
                                                           hasType(asString("uint16_t")),
                                                           hasType(asString("uint8_t")),
                                                           hasType(asString("unsigned int")),
                                                           hasType(asString("unsigned short int")),
                                                           hasType(asString("size_t"))))),
                           hasDescendant(implicitCastExpr(anyOf(
                               hasType(asString("uint32_t")), hasType(asString("uint16_t")),
                               hasType(asString("uint8_t")), hasType(asString("unsigned int")),
                               hasType(asString("unsigned short int")),
                               hasType(asString("size_t"))))),
                           hasDescendant(unaryOperator(anyOf(hasType(asString("uint32_t")),
                                                             hasType(asString("uint16_t")),
                                                             hasType(asString("uint8_t")),
                                                             hasType(asString("unsigned int")),
                                                             hasType(asString("unsigned short int")),
                                                             hasType(asString("size_t"))),
                                                       hasOperatorName("*")))),

                     parent, optionally(hasParent(stmt().bind("parentStmt"))))
                     .bind("implicitCastUIntToBool")),
        this);

    Finder->addMatcher(
        traverse(TK_AsIs,
                 implicitCastExpr(
                     anyOf(hasDescendant(memberExpr(hasType(asString("char")))),
                           hasDescendant(declRefExpr(hasType(asString("char")))),
                           hasDescendant(implicitCastExpr(hasType(asString("char")))),
                           hasDescendant(unaryOperator(anyOf(hasType(asString("char")),
                                                             hasType(asString("const char"))),
                                                       hasOperatorName("*")))),

                     parent, optionally(hasParent(stmt().bind("parentStmt"))))
                     .bind("implicitCastCharToBool")),
        this);

    Finder->addMatcher(traverse(TK_AsIs,
                                implicitCastExpr(anyOf(memberExpr(hasType(isAnyPointer())),
                                                       declRefExpr(hasType(isAnyPointer())),
                                                       implicitCastExpr(hasType(isAnyPointer()))),

                                                 parent,
                                                 optionally(hasParent(stmt().bind("parentStmt"))))
                                    .bind("implicitCastPtrToBool")),
                       this);

#if 0
    // Match pointers used in boolean expressions //////////////////////////////
    Finder->addMatcher(
        traverse(TK_AsIs,
            implicitCastExpr(
                hasType(pointerType()),
                anyOf(
                    hasParent(unaryOperator(hasOperatorName("!")).bind("not")),
                    hasParent(stmt(anyOf(ifStmt(), whileStmt())))
                ),
                optionally(hasParent(stmt().bind("parentStmt")))
            )
            .bind("implicitCastToBool")
        ),
        this
    );

    Finder->addMatcher(
        traverse(TK_AsIs,
            callExpr(
                hasType(isAnyPointer()),
                anyOf(
                    hasParent(binaryOperator(hasOperatorName("&&"))),
                    hasParent(binaryOperator(hasOperatorName("||"))),
                    hasParent(unaryOperator(hasOperatorName("!")).bind("not")),
                    hasParent(stmt(anyOf(ifStmt(), whileStmt())))
                ),
                optionally(hasParent(stmt().bind("parentStmt")))
            )
            .bind("callExprPtrCastToBool")
        ),
        this
    );

    // Function return unsigned integer value used in bool expression
    Finder->addMatcher(
        traverse(TK_AsIs,
            callExpr(
                hasType(isUnsignedInteger()),
                anyOf(
                    hasParent(binaryOperator(hasOperatorName("&&"))),
                    hasParent(binaryOperator(hasOperatorName("||"))),
                    hasParent(unaryOperator(hasOperatorName("!")).bind("not")),
                    hasParent(stmt(anyOf(ifStmt(), whileStmt())))
                ),
                optionally(hasParent(stmt().bind("parentStmt")))
            )
            .bind("callExprUintCastToBool")
        ),
        this
    );

    Finder->addMatcher(
        traverse(TK_AsIs,
            callExpr(
                hasType(isSignedInteger()),
                anyOf(
                    hasParent(binaryOperator(hasOperatorName("&&"))),
                    hasParent(binaryOperator(hasOperatorName("||"))),
                    hasParent(unaryOperator(hasOperatorName("!")).bind("not")),
                    hasParent(stmt(anyOf(ifStmt(), whileStmt())))
                ),
                optionally(hasParent(stmt().bind("parentStmt")))
            )
            .bind("callExprIntCastToBool")
        ),
        this
    );

    Finder->addMatcher(
        traverse(TK_AsIs,
            // Match a signed variable
implicitCastExpr(
    anyOf(
        hasType(isSignedInteger()),
        hasType(isUnsignedInteger())
    ),

    anyOf(
        hasParent(binaryOperator(hasOperatorName("&&"))),
        hasParent(binaryOperator(hasOperatorName("||"))),
        hasParent(
            unaryOperator(
                hasOperatorName("!"),
                hasParent(unaryOperator(hasOperatorName("!")).bind("notnot"))
            ).bind("not")
        ),
        hasParent(stmt(anyOf(ifStmt(), whileStmt())))
    )
)

            .bind("castExprIntCastToBool")
        ),
        this
    );




    // Match chars used in boolean expressions /////////////////////////////////
    Finder->addMatcher(
        traverse(TK_AsIs,
            implicitCastExpr(
                hasType(isAnyCharacter()),
                anyOf(
                    hasParent(unaryOperator(hasOperatorName("!")).bind("not")),
                    hasParent(stmt(anyOf(ifStmt(), whileStmt())))
                ),
                optionally(hasParent(stmt().bind("parentStmt")))
            )
            .bind("charCastToBool")
        ),
        this
    );

    Finder->addMatcher(
        traverse(TK_AsIs,
            implicitCastExpr(
                hasDescendant(implicitCastExpr(hasType(isAnyCharacter()))),
                anyOf(
                    hasParent(binaryOperator(hasOperatorName("&&"))),
                    hasParent(binaryOperator(hasOperatorName("||")))
                ),
                optionally(hasParent(stmt().bind("parentStmt")))
            )
            .bind("charCastToBool")
        ),
        this
    );
#endif
}

std::string get_replacement(const std::string &s)
{
    if (s == "int32_t" || s == "int16_t" || s == "int8_t" || s == "int" || s == "short int" ||
        s == "ssize_t") {
        return std::string("0");
    } else if (s == "uint32_t" || s == "uint16_t" || s == "uint8_t" || s == "unsigned int" ||
               s == "unsigned short int" || s == "size_t") {
        return std::string("0U");
    } else if (s == "char") {
        return std::string("'\\0'");
    } else {
        return "NULL";
    }
}

void ImplicitBoolConversionCheck::check(const MatchFinder::MatchResult &Result)
{

    if (const auto *Cast = Result.Nodes.getNodeAs<CallExpr>("castIntToBool")) {
        if (Result.Nodes.getNodeAs<UnaryOperator>("notnot")) {
            auto Diag = diag(Cast->getBeginLoc(), "CANNOT HANDLE '!!' (notnot)");
            return;
        }

        auto Diag = diag(Cast->getBeginLoc(), "Implicit integer cast to bool");

        const auto    *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc =
            Lexer::getLocForEndOfToken(Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                                       Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc = cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(CharSourceRange::getCharRange(ParentStartLoc,
                                                                           ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == 0");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != 0");
        }
    }

    if (const auto *Cast = Result.Nodes.getNodeAs<CallExpr>("castUIntToBool")) {
        if (Result.Nodes.getNodeAs<UnaryOperator>("notnot")) {
            auto Diag = diag(Cast->getBeginLoc(), "CANNOT HANDLE '!!' (notnot)");
            return;
        }

        auto Diag = diag(Cast->getBeginLoc(), "Implicit integer cast to bool");

        const auto    *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc =
            Lexer::getLocForEndOfToken(Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                                       Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc = cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(CharSourceRange::getCharRange(ParentStartLoc,
                                                                           ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == 0U");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != 0U");
        }
    }

    if (const auto *Cast = Result.Nodes.getNodeAs<CallExpr>("castPtrToBool")) {
        if (Result.Nodes.getNodeAs<UnaryOperator>("notnot")) {
            auto Diag = diag(Cast->getBeginLoc(), "CANNOT HANDLE '!!' (notnot)");
            return;
        }

        auto Diag = diag(Cast->getBeginLoc(), "Implicit integer cast to bool");

        const auto    *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc =
            Lexer::getLocForEndOfToken(Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                                       Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc = cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(CharSourceRange::getCharRange(ParentStartLoc,
                                                                           ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == NULL");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != NULL");
        }
    }

    if (const auto *Cast = Result.Nodes.getNodeAs<CallExpr>("castCharToBool")) {
        if (Result.Nodes.getNodeAs<UnaryOperator>("notnot")) {
            auto Diag = diag(Cast->getBeginLoc(), "CANNOT HANDLE '!!' (notnot)");
            return;
        }

        auto Diag = diag(Cast->getBeginLoc(), "Implicit integer cast to bool");

        const auto    *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc =
            Lexer::getLocForEndOfToken(Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                                       Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc = cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(CharSourceRange::getCharRange(ParentStartLoc,
                                                                           ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == '\\0'");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != '\\0'");
        }
    }

    if (const auto *Cast = Result.Nodes.getNodeAs<ImplicitCastExpr>("implicitCastCharToBool")) {

        auto Diag = diag(Cast->getBeginLoc(), "Implicit cast to bool");

        const auto    *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc =
            Lexer::getLocForEndOfToken(Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                                       Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc = cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(CharSourceRange::getCharRange(ParentStartLoc,
                                                                           ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == '\\0'");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != '\\0'");
        }
    }

    if (const auto *Cast = Result.Nodes.getNodeAs<ImplicitCastExpr>("implicitCastPtrToBool")) {

        auto Diag = diag(Cast->getBeginLoc(), "Implicit cast to bool");

        const auto    *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc =
            Lexer::getLocForEndOfToken(Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                                       Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc = cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(CharSourceRange::getCharRange(ParentStartLoc,
                                                                           ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == NULL");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != NULL");
        }
    }

    if (const auto *Cast = Result.Nodes.getNodeAs<ImplicitCastExpr>("implicitCastIntToBool")) {

        auto Diag = diag(Cast->getBeginLoc(), "Implicit cast to bool");

        const auto    *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc =
            Lexer::getLocForEndOfToken(Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                                       Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc = cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(CharSourceRange::getCharRange(ParentStartLoc,
                                                                           ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == 0");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != 0");
        }
    }

    if (const auto *Cast = Result.Nodes.getNodeAs<ImplicitCastExpr>("implicitCastUIntToBool")) {

        auto Diag = diag(Cast->getBeginLoc(), "Implicit cast to bool");

        const auto    *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc =
            Lexer::getLocForEndOfToken(Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                                       Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc = cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(CharSourceRange::getCharRange(ParentStartLoc,
                                                                           ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == 0U");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != 0U");
        }
    }

#if 0
    if (const auto *Cast =
        Result.Nodes.getNodeAs<CallExpr>("callExprCastToBool")) {
        auto Diag = diag(Cast->getBeginLoc(), "Call Expression implicit cast to bool");

        std::string s = get_replacement(Cast->getType().getAsString());
        const auto *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc = Lexer::getLocForEndOfToken(
                Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc =
                    cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(
                    CharSourceRange::getCharRange(ParentStartLoc, ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, std::string(" == ").append(get_replacement(s)));
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, std::string(" != ").append(get_replacement(s)));
        }
    }

    if (const auto *Cast =
        Result.Nodes.getNodeAs<CallExpr>("callExprUintCastToBool")) {
        if (Result.Nodes.getNodeAs<UnaryOperator>("notnot")) {
            return;
        }
        auto Diag = diag(Cast->getBeginLoc(), "Call Expression implicit cast to bool");

        const auto *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc = Lexer::getLocForEndOfToken(
                Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc =
                    cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(
                    CharSourceRange::getCharRange(ParentStartLoc, ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == 0U");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != 0U");
        }
    }

    if (const auto *Cast =
        Result.Nodes.getNodeAs<CallExpr>("callExprIntCastToBool")) {
        if (Result.Nodes.getNodeAs<UnaryOperator>("notnot")) {
            auto Diag = diag(Cast->getBeginLoc(), "CANNOT HANDLE '!!'");
            return;
        }

        auto Diag = diag(Cast->getBeginLoc(), "Call Expression implicit cast to bool");

        const auto *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc = Lexer::getLocForEndOfToken(
                Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc =
                    cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(
                    CharSourceRange::getCharRange(ParentStartLoc, ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == 0");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != 0");
        }
    }

    if (const auto *Cast =
        Result.Nodes.getNodeAs<ImplicitCastExpr>("castExprIntCastToBool")) {
        if (Result.Nodes.getNodeAs<UnaryOperator>("notnot")) {
            auto Diag = diag(Cast->getBeginLoc(), "CANNOT HANDLE '!!'");
            return;
        }

        auto Diag = diag(Cast->getBeginLoc(), "Call Expression implicit cast to bool");

        const auto *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc = Lexer::getLocForEndOfToken(
                Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc =
                    cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(
                    CharSourceRange::getCharRange(ParentStartLoc, ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == 0");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != 0");
        }
    }


    if (const auto *Cast =
        Result.Nodes.getNodeAs<ImplicitCastExpr>("implicitCastToBool")) {
        auto Diag = diag(Cast->getBeginLoc(), "implicit pointer conversion %0 -> bool") << Cast->getSubExpr()->getType();

        const auto *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc = Lexer::getLocForEndOfToken(
                Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc =
                    cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(
                    CharSourceRange::getCharRange(ParentStartLoc, ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == NULL");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != NULL");
        }
    }

    if (const auto *Cast =
        Result.Nodes.getNodeAs<ImplicitCastExpr>("charCastToBool")) {
        auto Diag = diag(Cast->getBeginLoc(), "implicit char conversion %0 -> bool") << Cast->getSubExpr()->getType();

        const auto *Parent = Result.Nodes.getNodeAs<Stmt>("parentStmt");
        SourceLocation EndLoc = Lexer::getLocForEndOfToken(
                Cast->getEndLoc(), 0, Result.Context->getSourceManager(),
                Result.Context->getLangOpts());

        if (Result.Nodes.getNodeAs<UnaryOperator>("not")) {
            SourceLocation ParentStartLoc = Parent->getBeginLoc();
            SourceLocation ParentEndLoc =
                    cast<UnaryOperator>(Parent)->getSubExpr()->getBeginLoc();
            Diag << FixItHint::CreateRemoval(
                    CharSourceRange::getCharRange(ParentStartLoc, ParentEndLoc));
            Diag << FixItHint::CreateInsertion(EndLoc, " == '\\0'");
        } else {
            Diag << FixItHint::CreateInsertion(EndLoc, " != '\\0'");
        }
    }
#endif
}

void ImplicitBoolConversionCheck::handleCastToBool(const ImplicitCastExpr *Cast,
                                                   const Stmt             *Parent,
                                                   ASTContext             &Context)
{
}
} // namespace clang::tidy::misra
