# Software Requirements Specification

**Author:** Jose Trinidad Lopez Moreno

**Date:** 09-02-2026

**Version:** 0.1

---

## 1. Purpose

This file defines the requirements of the cpp-text-editor software. It is meant to be use as a base to derive the implementation and testing, it can guide the branching and it bounds the scope.

## 2. Scope

- The cpp-text-editor software, is a terminal base text editor software.
- The software minimizes the complexity of the UI by using a simple command line.
- The software can create/open/save text files, through the system paths. It permits basic text editing and undo/redo mechanics.
- The software permits basic navigation of the text file, through the arrows and mouse inputs.
- The visualization is simple plain text, for every file, regardless of its termination.
- The software includes line numbering.
- The software includes basic status information. (Cursor position and error codes)

## 3. Assumptions and Constraints

Input files are assumed to contain plain text.

Keyboard input is assumed.

The editor shall run on terminal environment.

One open document at a time is assumed.

Supports ASCII text only

The editor shall build and run on Windows OS.

## 4. Functional Requirements

REQ-EDIT-000
The editor shall permit the user to do operations on an active document.

REQ-EDIT-001
The active document has to at least include one line.

REQ-EDIT-002
The editor shall permit the user to insert text characters at the cursor position.
After the character is placed, the cursor position is at the right of the character.
This operation shifts the characters that were at the right of the cursor, if any, to the right.

REQ-EDIT-003
The editor shall permit the user to delete text characters at the left of the cursor position.
After a character is deleted, the cursor position is at the left of where the character was at.
After a line break is deleted, the cursor is position at what was the end of the line above, previous to the operation.
If a character is deleted, it shifts the characters that were at the right of the cursor, if any, to the left.
If a line break is deleted, it shifts the characters that were at the line, to the end of the line above, which shifts the end of the line to the end of the characters added.

REQ-EDIT-004
The editor shall permit the user to delete text characters and line breaks at the right of the cursor position.
After the character/line-break is deleted, the cursor position is unchanged.
If a character is deleted, it shifts the characters that were at the right of the cursor (excluding the deleted character), if any, to the left.
If a line break is deleted, it shifts the characters that were at the line below, to the end of the current line, which shifts the end of the line to the end of the characters added.

REQ-EDIT-005
The editor shall permit the user to insert new lines at the cursor position.
After the line is placed, the cursor position is at the start of the new line.
This operation shifts the lines that were down of the cursor, keeping the same characters.
This operation shifts the characters that were at the right of the cursor, to the start of the new line.

REQ-EDIT-006
The editor shall permit the user to insert a tab at the cursor position.
After the tab is placed, the cursor position is at the right of the tab.
This operation shifts the characters that were at the right of the cursor, if any, to the right.
The tab is consider a character "\t", not any amount of spaces.

REQ-FILE-001
The editor shall permit the user to browse the system paths on the file-browser (REQ-UI-003) view, with the arrow input.
Where the browse movement is mapped to:

- UP: Move to file/folder above.
- DOWN: Move to file/folder below.
- LEFT: Move outside folder.
- RIGHT: Move inside folder.

REQ-FILE-002
The editor shall permit the user to do an "OPEN" command.
For this the file-browser view shall be open, then the user should select a file on the file-browser, to use as on the active document view (REQ-UI-003).
The select operation is mapped to enter:

ENTER: 

- file: Select file
- folder: Move inside folder.
- no selection: error code (REQ-ERR-001)

After selecting a file, the file-browser shall close and the file shown on the active document view

REQ-FILE-003
The editor shall permit the user to do a "NEW FILE" command, which will create a new file to use as active document on the document viewport.
This opens the active document view.

REQ-FILE-004
The editor shall permit the user to do a "SAVE" command, when having an active document.
If the file already points to a path, it will save to the same path.

If the file doesn't point anywhere, it will trigger a "SAVE AS" operation, without an entered name.

REQ-FILE-005
The editor shall permit the user to do a "SAVE AS" command, follow of the name to which to save the file, when having an active document.
If no name is given, the editor will select a default prefix name with a numerical incrementing subfix, to not repeat an already existing file on the location.
For this the file-browser view shall be open, with the file name written on the command line, which the user can change, then the user should confirm operation inside of a folder on the file-browser, to use as location to save the active document.
File browser view will default to showing inside the current folder where the file is save, if any.

The select operation is mapped to enter:

ENTER: 

- file: Ask for replace file confirmation
- folder: Move inside folder
- no selection: Ask for save new file confirmation

After successful confirmation, the file-browser view shall close and the file will be shown again on the active document view but pointing to the new direction.

REQ-NAV-001
The editor shall permit the user to move the cursor with the arrow inputs. Where the movement is mapped to:

- UP: Move to line before.
- DOWN: Move to line after.
- LEFT: Move to character before.
- RIGHT: Move to character after.

The movement between lines should keep the cursor visual terminal column number the same, if possible.
The desired visual terminal column is change each time the user moves left or right.

REQ-NAV-002
The editor shall permit the user to move the cursor with the left click of the mouse input, at the closest position the user was hovering.

REQ-HIST-001
The editor shall permit the user to undo the last edit operation, that changed the active document.

REQ-HIST-002
The editor shall permit the user to reapply the last undo operation. This is called redo.

REQ-HIST-003
The editor shall clear the redo history after a new change is apply.

REQ-SEL-001
The editor shall permit the user to select sections of the active document, by moving the cursor while holding left click of the mouse input.

REQ-SEL-002
The editor shall permit the user to delete a selected section of text.
After the operation, the cursor position is at the start of the removed section.
This is still consider one single operation.

REQ-SEL-003
The editor shall permit the user to copy a selected section of text.
This is saved on the system clipboard.

REQ-SEL-004
The editor shall permit the user to paste a section of text, from the system clipboard.
If the operation is done while selecting a section of text, the paste text will replace the selected text.
This is still consider one single operation.

REQ-ERR-001
The editor shall show an error code on the bottom status section, when trying to open a non existent file.
This error shall not close nor block the editor application from running.

REQ-ERR-002
The editor shall show an error code on the bottom status section, when trying to save a file on a path where the editor doesn't have access.
This error shall not close nor block the editor application from running.

REQ-ERR-003
The editor shall show an error code on the bottom status section, when entering a command with bad syntax.
This error shall not close nor block the editor application from running.

REQ-CMD-001
The editor shall define a syntax for each supported command.

REQ-CMD-002
The editor shall recognize user input that matches a defined command, and execute its operation.

REQ-UI-001
The editor shall have a document viewport section and a command line section when running.

REQ-UI-002
The editor shall show the application name and version, on the command line prefix:

    NAME-VERSION> USER-INPUT-COMMANDS
    {  PREFIX   }{       SUFIX      }

REQ-UI-003
The editor shall have an active document view and a file-browser view. Both on the document viewport, which only lets one at a time.

REQ-UI-004
The editor shall permit the user scroll through the document viewport and the command line, independently

REQ-UI-005
The editor shall have a reserved section on the left of an active document, to show each line number.

REQ-UI-006
The editor shall have a reserved status section, at the bottom of the document viewport.

REQ-UI-007
The editor shall show the line and visual terminal column number the cursor is at, on the bottom status section.

## 5. Non-Functional Requirements

## 6. Out of Scope

Not supported for now:

- Not full UTF-8 compatibility
- Open multiple files
- Configuration
- Colors
- Images
- Auto-corrector
- Syntax Highlighting
- Linter
- Auto-saver 
- Compiler
- Plugings

## 7. Validation

Each requirement needs a behavioral validation evidence, that passes, before it can be consider implemented.
This can either be automated or manual depending on the requirement.

The first constraint to validate is that the software builds an run on Windows, following the documented process.

Requirements from the edit/file/nav/hist/err/cmd family should be Unit Tested.

Requirements from the ui/sel family should be manually validated, given that these are more visual or depend on mouse use.