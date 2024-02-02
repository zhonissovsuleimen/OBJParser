#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct VertexInfo
{
   // coordinates
   float x;
   float y;
   float z;
   // normal
   float normal_x;
   float normal_y;
   float normal_z;
   // texture coordinates
   float u;
   float v;
};

struct Triangle
{
    VertexInfo v1;
    VertexInfo v2;
    VertexInfo v3;
};

int main(int argc, char **argv)
{
   if (argc < 2) {
      std::cout << "USAGE: homework2_exe [filename]" << std::endl;
      return 1;
   }
   std::string filename{ argv[1] };
   std::ifstream fileStream (filename);

   if (fileStream.is_open()) {
      std::string line;
      unsigned int vCount = 0;
      unsigned int vtCount = 0;
      unsigned int vnCount = 0;

      //counting the number of v's, vt's, and vn's
      while (std::getline(fileStream, line)) {
         if (line.length() < 2) continue;

         if (line[0] == 'v' && line[1] == ' ') {
            vCount++;
         } else if (line[0] == 'v' && line[1] == 't') {
            vtCount++;
         } else if (line[0] == 'v' && line[1] == 'n') {
            vnCount++;
         }
      }

      //reset the filestream to the beginning of the file
      fileStream.clear();
      fileStream.seekg(0);

      //vertex cache: x, y, z, [w]; w is optional and defaults to 1.0
      std::vector<std::vector<float>> vCache(vCount, std::vector<float>(4));
      for(int i = 0; i < vCount; i++) {
         vCache[i][3] = 1.0;
      }
      //texture coordinates cache: u, [v, w]; v, w are optional and default to 0.0
      std::vector<std::vector<float>> vtCache(vtCount, std::vector<float>(3));
      std::vector<std::vector<float>> vnCache(vnCount, std::vector<float>(3));


      fileStream.close();
   } else {
      std::cout << "Unable to open file" << std::endl;
      return 1;
   }


}