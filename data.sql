
The `FILENAME` macro defines the name of the CSV file where the attendance records will be stored. The `viewAttendance` function writes the attendance records to this file in CSV format, including a header row.

The `loadAttendance` function reads the attendance records from the file and populates the `students` array with the corresponding `Student` structures.

In the `main` function, the `loadAttendance` function is called at the beginning to load any existing attendance records from the file. At the end of the program, the `viewAttendance` function is called to save the updated attendance records to the file.

Note that in this implementation, the attendance records are overwritten every time the program is run. To modify this behavior, you could add an option to load existing attendance records at the beginning of the program and merge them with the new attendance records.
