# QVerwaltung
Hausverwaltung in Qt


Dependencies
M means modified
U means Unmodified ( i made no changes)
Library     |     Version     |     License
Qt                  5.12U             LGPL
PODOFO              0.9M              LGPL
 |_ POCO C++        trunk U           BOOST
 RIBBON             trunk U           LGPL
 
 
 Downloads:
 Ribbon - https://github.com/martijnkoopman/Qt-Ribbon-Widget
 
 
 Podofo - Source inside this Project
 To compile my version of Podofo you just need to download the Source from podofo.sourceforge.net and replace the .h and .cpp with mine. and recompile it. And add Poco C++ Library to it.
 Following changes were made:
 - Replaced std::auto_ptr with Poco Shared Ptr. It is now compatible to C++17
