/* word_count.c is a word frequency counter developed with the Glib library
*for Software Systems by Joseph Lee
*
*It accepts any number of filenames from the command line at prints out each unique word
*that occurs in the text files along with the number of times that word appears 
*
*This program can be compiled using the Makefile in this directory
*/

#include <glib.h>

int main(int argc, char* argv[]) {
    //initializations
	gssize length;
	gchar* content;
	gchar** str_ptr;
	gchar** split_str;
	int *val = g_new (int, 1);
	int *initial_val = g_new (int, 1);
	*initial_val=1;

	//create a Glib hashtable outside of the for loop that indexes through files
	GHashTable *word_counter_table = g_hash_table_new(g_str_hash, g_str_equal);

	//this handles cases where the user inputs more than one filename
	for (int index=1; index<argc; index++){
		gchar** filename = argv[index];

		if (g_file_get_contents (filename, &content, &length, NULL)==TRUE) {
			//Replace anything that isn't a valid character with whitespace, this handles punctuation
			g_strcanon(content, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", ' ');

        // split the string into an array of separate strings using whitespace as the seperator
			split_str = g_strsplit(content, " ", 0);


        // index through this array of unique "words"
			//if the word already exists in our hash table we need to add a count to its value
			//if the word isn't in the hash table then we need to insert it with a value of 1
			for (str_ptr = split_str; *str_ptr; str_ptr++){
				if (g_hash_table_contains(word_counter_table, *str_ptr)) {
					*val = g_hash_table_lookup(word_counter_table, *str_ptr);
					g_hash_table_replace(word_counter_table, *str_ptr, *val+1);
				} else {
					g_hash_table_insert(word_counter_table, *str_ptr, *initial_val);
				}
			}

        // get all the words in the hash table
			GList* keys = g_hash_table_get_keys(word_counter_table);

        // print all of the word,count pairs
			while (keys != NULL){
				g_printf("%s, %d\n", keys->data, g_hash_table_lookup(word_counter_table, keys->data));
				keys = keys->next;
			}

		} else {
			//return 1 if something went wrong getting the file
			return 1;
		}
	}
	//return 0 if successful
	return 0;
}