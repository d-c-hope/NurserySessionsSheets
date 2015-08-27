# NurserySessionsSheets
Allows printing of which child is in which room on a given month

The app allows you to add children including a date of birth and then to add half day sessions for each child between sets of dates.

e.g. 01/04/2015- 01/12/2016, Mon AM, MonPM, FriAM

These can then be exported to tab or CSV delimited files for easy import into an Excel or Numbers spreadsheet

## Spreadsheet rules:

When the csv files are created they are done according to the following rules:

1. If a child starts in a particular month even if in the last week then they should appear in that month
2. If a child leaves in a particular month even if in the first week then they should appear in that month
3. All children under 2 or becoming 2 in the second half of the month should be shown in room 1
4. All children aged 2 or becoming 2 in the first half of the month or becoming 3 in the 2nd half of the month should be in room 2.
5. All children over 3 or becoming 3 in the first half of the month should be in room 3
6. If a child changes sessions in a month use the new sessions if they change before the 15th and the old sessions if they change on the 15th or after.

## Compiling and running
The app should be compiled using Qt Creator or at least QMake. You'll need to point the app at your boost directory and have compiled boost_filesystem

Also if you want to distribute the app you need to run macdeployqt on the .app file for OSX

The code can be used for non profit non commercial purposes but can only be used commerically with the permission of the repo owner, D Hope. 
If you do use it for any other purpose please reproduce this message
