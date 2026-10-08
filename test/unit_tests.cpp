#include "gtest/gtest.h"
#include "document.h"
#include <iostream>

TEST(DocumentTest, documentModel) {
    
    const std::vector<std::string> text ={"A"};
    editor_core::Document test_document(text);
    EXPECT_EQ(test_document.get_line_count(),1);
    EXPECT_EQ(test_document.get_column_len(0),1);

    test_document.delete_character(editor_core::position({0,0}));
    EXPECT_EQ(test_document.get_line(0), "");

    test_document.insert_character((const char)'A', editor_core::position({0,0}));
    test_document.insert_character((const char)'B', editor_core::position({0,1}));
    test_document.insert_character((const char)'D', editor_core::position({0,2}));
    test_document.insert_character((const char)'C', editor_core::position({0,2}));
    EXPECT_EQ(test_document.get_line(0), "ABCD");

    test_document.insert_new_line(editor_core::position({0,2}));
    EXPECT_EQ(test_document.get_line_count(),2);
    EXPECT_EQ(test_document.readDocument(editor_core::position({0,1}), editor_core::position({1,0})),std::vector<std::string>({"B","C"}));

    test_document.merge_with_next_line(0);
    EXPECT_EQ(test_document.get_line_count(),1);
    EXPECT_EQ(test_document.get_line(0), "ABCD");

    test_document.delete_character(editor_core::position({0,2}));
    EXPECT_EQ(test_document.get_line(0), "ABD");

    test_document.insert_new_line(editor_core::position({0,3}));
    EXPECT_EQ(test_document.get_line(0), "ABD");
    EXPECT_EQ(test_document.get_line(1), "");
}