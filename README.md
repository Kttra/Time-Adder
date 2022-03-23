# Time Adder
Purpose of the program is to receive multiple time inputs from the user and add up the time. Time adder has been greatly updated. This version can handle unlimited inputs compared to the limited 3 in the previous version. The program converts characters to integers in C++ and then adds the times inputted.

The expected input will be in the format min:sec. For example, "12:34" would be considered valid input.

**Valid input examples would be:**
------------------------------------------------
- 12+34+54
- 12:00 + 13
- 14 + 10:00
- 11:00
- 12:34 + 13:00 + 41:00 + 12:34 + 13:00 + 41:00 + 12:34 + 13:00 + 41:00
- 1+++15
- 11:
- :10

**Invalid input would be:**
------------------------------------------------
- gdgrefer (random letters)
- 11:11+12:1.....2+11::::10 (A lot of colons or dots)

**Time Adder in Action**
------------------------------------------------
```
Custom program by Kttra. Made to add time for user.
Input 0 if you want to reset the time.

Enter time (min:sec): 1:30+1:30
3 mins 0 secs

Enter time (min:sec): 11:11+11:11
25 mins 22 secs

Enter time (min:sec): 300
30 mins 22 secs

Enter time (min:sec): 300:00
5 hrs 30 mins 22 secs

Enter time (min:sec): 0
Reset time to: 0 mins 0 secs

Enter time (min:sec): gdgrefer
Invalid input!

Enter time (min:sec):
```

**Additional Notes:**
------------------------------------------------
The input ":1" would be considered to be 1 second instead of 10 minutes.
The reason for this is decision is because "1:" would be considered 1 minute.
Time inputted without a colon will be considered seconds instead of minutes. To clear the console, input "clc" or "clear". This will not reset the time.

**Version v1.0.0 Limitations**
------------------------------------------------
Could not handle more than 3 times. Could not handle inputs that started with a colon. Did not take into account if user inputted multiple colons or dots between a time. Originally the program was made with the thought of only accepting one time, but I decided that was too limiting and changed the project halfway. Because of this, I did not have time to think of inputs such as the ones below. Version 2.0.0 mostly takes from the first version, except I split the user's input and calculate it into the time vector as a substring. Thus, making it more efficient.
- 12:34 + 13:00 + 41:00 + 12:34
- 2+11::::10
- 1+++++++1
