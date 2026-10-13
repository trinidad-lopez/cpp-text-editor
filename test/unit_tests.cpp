#include "gtest/gtest.h"
#include "document.h"
#include <iostream>


TEST(DocumentTest, Constructor) {
    std::vector<std::string> empty;

    EXPECT_ANY_THROW(editor_core::Document test_document(empty));

    EXPECT_NO_THROW(editor_core::Document test_document);
}

TEST(DocumentTest, InsertCharacter) {
    editor_core::Document test_document;

    //Outside Lower boundary 0 <= pos.line
    test_document.insert_character((const char)'L', editor_core::position({-1,0}));
    EXPECT_EQ(test_document.get_line(0), "");

    //Outside Upper boundary pos.line < line
    test_document.insert_character((const char)'U', editor_core::position({test_document.get_line_count(),1}));
    EXPECT_EQ(test_document.get_line(0), "");

    //Outside Lower boundary 0 <= pos.column
    test_document.insert_character((const char)'L', editor_core::position({0,-1}));
    EXPECT_EQ(test_document.get_line(0), "");

    //Outside Upper boundary pos.column <= line.size
    test_document.insert_character((const char)'U', editor_core::position({0,test_document.get_column_len(0)+1}));
    EXPECT_EQ(test_document.get_line(0), "");

    //Inside Lower boundaries 0 <= pos.line && 0 <= pos.column
    test_document.insert_character((const char)'L', editor_core::position({0,0}));
    EXPECT_EQ(test_document.get_line(0), "L");

    //Inside Upper boundaries pos.line < lines && pos.column <= line.size
    test_document.insert_character((const char)'U', editor_core::position({test_document.get_line_count()-1,test_document.get_column_len(test_document.get_line_count()-1)}));
    EXPECT_EQ(test_document.get_line(0), "LU");
}

TEST(DocumentTest, DeleteCharacter) {
    editor_core::Document test_document({"ABCD"});

    //Outside Lower boundary 0 <= pos.line
    test_document.delete_character(editor_core::position({-1,0}));
    EXPECT_EQ(test_document.get_line(0), "ABCD");

    //Outside Upper boundary pos.line < line
    test_document.delete_character(editor_core::position({test_document.get_line_count(),0}));
    EXPECT_EQ(test_document.get_line(0), "ABCD");

    //Outside Lower boundary 0 <= pos.column
    test_document.delete_character(editor_core::position({0, -1}));
    EXPECT_EQ(test_document.get_line(0), "ABCD");

    //Outside Upper boundary pos.column < line.size
    test_document.delete_character(editor_core::position({0,test_document.get_column_len(0)}));
    EXPECT_EQ(test_document.get_line(0), "ABCD");

    //Inside Lower boundaries 0 <= pos.line && 0 <= pos.column
    test_document.delete_character(editor_core::position({0,0}));
    EXPECT_EQ(test_document.get_line(0), "BCD");

    //Inside Upper boundaries pos.line < lines && pos.column < line.size
    test_document.delete_character(editor_core::position({test_document.get_line_count()-1,test_document.get_column_len(test_document.get_line_count()-1)-1}));
    EXPECT_EQ(test_document.get_line(0), "BC");
}

TEST(DocumentTest, InsertNewLine) {
    editor_core::Document test_document({"AB"});

    //Outside Lower boundary 0 <= pos.line
    test_document.insert_new_line(editor_core::position({-1,0}));
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"AB"}));

    //Outside Upper boundary pos.line < line
    test_document.insert_new_line(editor_core::position({test_document.get_line_count(),1}));
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"AB"}));

    //Outside Lower boundary 0 <= pos.column
    test_document.insert_new_line(editor_core::position({0,-1}));
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"AB"}));

    //Outside Upper boundary pos.column <= line.size
    test_document.insert_new_line(editor_core::position({0,test_document.get_column_len(0)+1}));
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"AB"}));

    //Inside Lower boundaries 0 <= pos.line && 0 <= pos.column
    test_document.insert_new_line(editor_core::position({0,0}));
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"","AB"}));

    //Inside Upper boundaries pos.line < lines && pos.column <= line.size
    test_document.insert_new_line(editor_core::position({test_document.get_line_count()-1,test_document.get_column_len(test_document.get_line_count()-1)}));
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"", "AB", ""}));
}

TEST(DocumentTest, MergeWithNextLine) {
    editor_core::Document test_document({"A", "B", "C"});

    //Outside Lower boundary 0 <= pos.line
    test_document.merge_with_next_line(-1);
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"A", "B", "C"}));

    //Outside Upper boundary pos.line < line
    test_document.merge_with_next_line(test_document.get_line_count()-1);
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"A", "B", "C"}));

    //Inside Lower boundary 0 <= pos.line
    test_document.merge_with_next_line(0);
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"AB", "C"}));

    //Inside Upper boundary pos.line < lines
    test_document.merge_with_next_line(test_document.get_line_count()-2);
    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"ABC"}));
}

TEST(DocumentTest, GetColumnLen) {
    editor_core::Document test_document({"A"});

    //Outside Lower boundary 0 <= pos.line
    EXPECT_EQ(test_document.get_column_len(-1), -1);

    //Outside Upper boundary pos.line < lines
    EXPECT_EQ(test_document.get_column_len(1), -1);

    //Inside boundaries 0 <= pos.line < lines
    EXPECT_EQ(test_document.get_column_len(0), 1);
}

TEST(DocumentTest, GetLineCount) {
    editor_core::Document test_document;

    EXPECT_EQ(test_document.get_line_count(), 1);
}

TEST(DocumentTest, GetLine) {
    editor_core::Document test_document({"A"});

    //Outside Lower boundary 0 <= pos.line
    EXPECT_EQ(test_document.get_line(-1), std::string({0}));

    //Outside Upper boundary pos.line < lines
    EXPECT_EQ(test_document.get_line(1), std::string({0}));

    //Inside boundaries 0 <= pos.line < lines
    EXPECT_EQ(test_document.get_line(0), "A");
}

TEST(DocumentTest, ReadDocument) {
    editor_core::Document test_document({"AB", "CD"});

    //START: Outside Lower boundary 0 <= pos.line
    EXPECT_EQ(test_document.readDocument(editor_core::position({-1,0}), 
                                            editor_core::position({0,0})).size(),
                                            0);

    //START: Outside Upper boundary pos.line < line
    EXPECT_EQ(test_document.readDocument(editor_core::position({test_document.get_line_count(),0}), 
                                        editor_core::position({0,0})).size(),
                                        0);

    //START: Outside Lower boundary 0 <= pos.column
    EXPECT_EQ(test_document.readDocument(editor_core::position({0,-1}), 
                                        editor_core::position({0,0})).size(),
                                        0);

    //START: Outside Upper boundary pos.column < line.size
    EXPECT_EQ(test_document.readDocument(editor_core::position({0,test_document.get_column_len(0)}), 
                                        editor_core::position({0,0})).size(),
                                        0);

    //END: Outside Lower boundary 0 <= pos.line
    EXPECT_EQ(test_document.readDocument(editor_core::position({0,0}), 
                                            editor_core::position({-1,0})).size(),
                                            0);

    //END: Outside Upper boundary pos.line < line
    EXPECT_EQ(test_document.readDocument(editor_core::position({0,0}), 
                                        editor_core::position({test_document.get_line_count(),0})).size(),
                                        0);

    //END: Outside Lower boundary 0 <= pos.column
    EXPECT_EQ(test_document.readDocument(editor_core::position({0,0}), 
                                        editor_core::position({0,-1})).size(),
                                        0);

    //END: Outside Upper boundary pos.column < line.size
    EXPECT_EQ(test_document.readDocument(editor_core::position({0,0}), 
                                        editor_core::position({0,test_document.get_column_len(0)})).size(),
                                        0);

    //END < START
    EXPECT_EQ(test_document.readDocument(editor_core::position({1,1}), 
                                        editor_core::position({0,0})).size(),
                                        0);

    
    EXPECT_EQ(test_document.readDocument(editor_core::position({0,1}), editor_core::position({1,0})),std::vector<std::string>({"B", "C"}));
}

TEST(DocumentTest, ReadFullDocument) {
    editor_core::Document test_document({"AB", "CD"});

    EXPECT_EQ(test_document.readFullDocument(), std::vector<std::string>({"AB", "CD"}));
}