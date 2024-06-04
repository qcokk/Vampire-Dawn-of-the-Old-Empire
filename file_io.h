#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>

#include "main.h"

void save_files(struct player Player, string file_name);
void load_files (struct player & Player, string file_name);
vector<string> file_manager();
void save_file_manager(player Player, int current_size, vector<string> v);

#endif
