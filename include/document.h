#pragma once

#include <string>
#include <vector>


namespace editor_core
{
    
    typedef struct {
        int line;
        int column;
    } position;

    class Document
    {
        public:
        /**
         * @brief Constructor for class Document
         * 
         * @param contents  Text to initialize the document contents.
         */
        Document(const std::vector<std::string> &contents = std::vector<std::string>({""}));

        /**
         * @brief Inserts character at position. 
         * 
         * If the position already has a character, it shift them to the right.
         * The position has to be on the range: 
         *      0 <= pos.line < lines
         *      0 <= pos.column <= line.size 
         * 
         * @param c     Character to insert.
         * @param pos   Position to insert at.
         * @return void
         */
        void insert_character(const char c, position pos);

        /**
         * @brief Deletes character at position. 
         * 
         * It shifts the characters that were at the right of the character, to the left.
         * The position has to be on the range: 
         *      0 <= pos.line < lines
         *      0 <= pos.column < line.size 
         * 
         * @param pos   Position to delete.
         * @return void
         */
        void delete_character(position pos);

        /**
         * @brief Inserts new line at position. 
         * 
         * It moves the characters from the position (inclusive) to the end of the current line to the new line.
         * The position has to be on the range: 
         *      0 <= pos.line < lines
         *      0 <= pos.column <= line.size 
         * 
         * @param pos   Position to insert at.
         * @return void
         */
        void insert_new_line(position pos);

        /**
         * @brief Merges given line with next line. 
         * 
         * It appends the next line to the end of the selected line and deletes the next line.
         * The selected line has to be on the range: 
         *      0 <= line < lines-1
         * 
         * @param line   Selected line.
         * @return void
         * @note There is always at least one line.
         */
        void merge_with_next_line(int line);

        /**
         * @brief Length of given line. 
         * 
         * The selected line has to be on the range: 
         *      0 <= line < lines
         * 
         * @param line   Selected line.
         * @return Length
         * @note Returns -1 when out of range.
         */
        int get_column_len(int line) const;

        /**
         * @brief Number of lines on document. 
         * 
         * @return Number
         */
        int get_line_count() const;

        /**
         * @brief Returns a copy of the string of a line. 
         * 
         * The selected line has to be on the range: 
         *      0 <= line < lines
         * 
         * @param line  Selected line.
         * @return String
         * @note Returns {0} when out of range.
         */
        std::string get_line(int line) const;

        /**
         * @brief Returns copy of the Document from given range. 
         * 
         * The positions have to be on the range: 
         *      0 <= pos.line < lines
         *      0 <= pos.column < line.size
         * The relation between both positions has to be Start < End.
         * 
         * @param start     Start of range.
         * @param end       End of range.
         * @return Vector<String>
         * @note Returns empty when arguments are invalid.
         */
        std::vector<std::string> readDocument(position start, position end) const;

        /**
         * @brief Returns copy of the Document.
         * 
         * @return Vector<String>
         */
        std::vector<std::string> readFullDocument() const; 

        private:
        std::vector<std::string> document_text;

        /**
         * @brief It verifies if the text is valid for class Document. 
         * 
         * @param text  Vector of strings.
         * @return true/false
         */
        bool text_valid(const std::vector<std::string> &text);


    };


}