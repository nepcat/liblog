```
$ make && ./liblog-test.out
gcc -std=c99 -Wall -Wextra -Wpedantic -o obj/main.c.o -c src/main.c
gcc -std=c99 -Wall -Wextra -Wpedantic -o obj/liblog.c.o -c src/liblog.c
gcc -std=c99 -Wall -Wextra -Wpedantic -o liblog-test.out obj/main.c.o obj/liblog.c.o 
[2024-07-26 19:31:55 TRACE test_var()] test_var: 1337
[2024-07-26 19:31:55 INFO  main()] Testing formats: 123
[2024-07-26 19:31:55 DEBUG test_function()] Reached the desired point...
[2024-07-26 19:31:55 WARN  main()] Got negative value
[2024-07-26 19:31:55 ERROR main()] Unexpected value: (nil)
[2024-07-26 19:31:55 FATAL main()] Failed to allocate enough memory
```