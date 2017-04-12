  # build an executable named word_count from word_count.c

#first list dependencies
word_count: word_count.c 
#actual compilation command
	gcc -std=c11 -o word_count word_count.c `pkg-config --libs --cflags glib-2.0`