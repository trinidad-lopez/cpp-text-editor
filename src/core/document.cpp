#include "document.h"
#include <cstddef>
#include <cstring>
#include <iostream>

namespace editor_core
{

    Document::Document(const std::vector<std::string> &contents){
        if(text_valid(contents)){
            document_text = contents;
        }else{
            throw std::invalid_argument("Invalid argument");
        }
    }
    
    void Document::insert_character(const char c, position pos){
        //TO-DO: Check for valid character
        if(pos.line < 0 || pos.line >= get_line_count()) return;
        if(pos.column < 0 || pos.column > get_column_len(pos.line)) return;

        document_text[pos.line].insert(pos.column, std::string(1,c));
    }

    void Document::delete_character(position pos){
        if(pos.line < 0 || pos.line >= get_line_count()) return;
        if(pos.column < 0 || pos.column >= get_column_len(pos.line)) return;

        document_text[pos.line].erase(pos.column, 1);
    }

    void Document::insert_new_line(position pos){
        if(pos.line < 0 || pos.line >= get_line_count()) return;
        if(pos.column < 0 || pos.column > get_column_len(pos.line)) return;

        std::string new_line(document_text[pos.line].substr(pos.column));
        document_text[pos.line].erase(pos.column);
        document_text.insert(document_text.begin()+pos.line+1, new_line);
    }

    void Document::merge_with_next_line(int line){
        if(line < 0 || line >= get_line_count()-1) return;

        document_text[line].append(document_text[line+1]);
        document_text.erase(document_text.begin()+line+1);
    }

    int Document::get_column_len(int line) const {
        if(line < 0 || line >= get_line_count()) return -1;

        return document_text[line].size();
    }

    int Document::get_line_count() const {
        return document_text.size();
    }

    std::string Document::get_line(int line) const {
        if(line < 0 || line >= get_line_count()) return {0};
        
        return document_text[line];
    }

    std::vector<std::string> Document::readDocument(position start, position end) const{
        std::vector<std::string> subText;

        int x = end.column-start.column;
        int y = end.line-start.line;
        if(start.line < 0 || start.column < 0 || end.line < 0 || end.column < 0) return subText; // No negatives
        if(y < 0 || (y == 0 && x < 0)) return subText; // Start has to be an earlier or same position as end.
        if(end.line >= get_line_count() || end.column >= get_column_len(end.line)) return subText; // Positions have to exist.

        int column_start, column_end, len;
        for(int line=start.line;line<=end.line;line++){
            column_start = 0;
            column_end = get_column_len(line)-1;
            if(line==start.line) column_start = start.column;
            if(line==end.line) column_end = end.column;
            len = column_end-column_start+1;
            subText.push_back(document_text[line].substr(column_start, len));
        }

        return subText;
    }

    std::vector<std::string> Document::readFullDocument() const {
        return document_text;
    }

    bool Document::text_valid(const std::vector<std::string> &text){
        if(text.size() == 0) return false;
        // Need to check valid characters

        return true;
    }
}