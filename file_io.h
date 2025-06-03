#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include "album.h"

bool loadAlbumFromFile(const std::string& filePath, Album& album);
bool saveAlbumToFile(const std::string& filePath, const Album& album);

#endif
