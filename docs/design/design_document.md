# Editor Core Model

**Author:** Jose Trinidad Lopez Moreno

**Date:** 10-05-2026

**Version:** 0.1

## Purpose

Define the core model used to represent and interact with the editor.

## Requirements Considered

- REQ-EDIT-001
- REQ-EDIT-002
- REQ-EDIT-003
- REQ-EDIT-004
- REQ-EDIT-005
- REQ-EDIT-006

- REQ-FILE-001
- REQ-FILE-002
- REQ-FILE-003
- REQ-FILE-004
- REQ-FILE-005

- REQ-NAV-001
- REQ-NAV-002

- REQ-HIST-001
- REQ-HIST-002
- REQ-HIST-003

- REQ-SEL-001
- REQ-SEL-002
- REQ-SEL-003
- REQ-SEL-004

## Derived State

### Document text

The document must represent an ordered collection of text lines.

Derived from:
- REQ-EDIT-001
- REQ-EDIT-005
- REQ-EDIT-003
- REQ-EDIT-004

### Document path

The editor must represent the system path of the current active document.

Derived from:
- REQ-FILE-004

### Cursor State

The editor must represent the current cursor insertion position within the active document lines and columns.

Derived from:
- REQ-NAV-001
- REQ-NAV-002

### Operations History

The editor must represent the operations that changed the active document in the document history.

Derived from:
- REQ-HIST-001
- REQ-HIST-002

### Selection

The editor must represent the selected text within the active document.

Derived from:
- REQ-SEL-001

## Invariants

### INV-DOC-001

An active document contains at least one line.

Derived from:
- REQ-EDIT-001

### INV-CURSOR-001

The cursor row shall identify an existing document line.
0 <= cursor.row < document.lines

Derived from:
- REQ-NAV-001

### INV-CURSOR-002

The cursor column shall identify an existing column on the current line.
0 <= cursor.column <= current_line.length

Derived from:
- REQ-NAV-001

## Responsibilities

The editor model is responsible for:
- Keeping the document valid structure after each edit operation.
- Saving documents on a valid path.
- Keeping a valid history of edit operations.

The editor model is not responsible for:
- Fitting the document on the document view.
- Highlighting the selected text.
- 

In Memory Document-Owned
- Document text: This is the document contents and it needs to owned it to protect its invariants.
-

Editor-Owned
- Document path: This is the editor saved path for the active document, even if it is changed, it won't affect the original document.
- Cursor State: The cursor is purely for the editor interaction, and doesn't actually exist on the document.
- Operations History: The operations history, is for edition convenience and doesn't represent actual metadata that the document saves.
- Selection: The selection data is for edition convenience.
- 
Unresolved
- 

## Open Design Questions

- Does each interactable section has its own cursor state or does the cursor has an state for each section?
- Does selecting a text, saves all characters, or only the range of positions withing the active document?