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

      //vertex cache: x, y, z, [w]; w is optional and defaults to 1.0
      //w is not used as the project does not require it
      std::vector<std::vector<float>> vCache(vCount, std::vector<float>(3));
      // for(int i = 0; i < vCount; i++) {
      //    vCache[i][3] = 1.0;
      // }

      //texture coordinates cache: u, [v, w]; v, w are optional and default to 0.0
      //w is not used as the project does not require it
      std::vector<std::vector<float>> vtCache(vtCount, std::vector<float>(2));

      //vertex normals cache: x, y, z;
      std::vector<std::vector<float>> vnCache(vnCount, std::vector<float>(3));

      //reset the filestream to the beginning of the file
      fileStream.clear();
      fileStream.seekg(0);

      int i = 0;
      int j = 0;
      int k = 0;
      while (std::getline(fileStream, line)) {
         if (line.length() < 2) continue;

         if (line[0] == 'v' && line[1] == ' ') {
            std::string cords = line.substr(1);
            cords = cords.substr(cords.find_first_not_of(' '));

            std::string x = cords.substr(0, cords.find(' '));
            vCache[i][0] = std::stof(x);
            cords = cords.substr(cords.find(' '));
            cords = cords.substr(cords.find_first_not_of(' '));

            std::string y = cords.substr(0, cords.find(' '));
            vCache[i][1] = std::stof(y);
            cords = cords.substr(cords.find(' '));
            cords = cords.substr(cords.find_first_not_of(' '));

            vCache[i][2] = std::stof(cords);
         } else if (line[0] == 'v' && line[1] == 't') {
            std::string cords = line.substr(2);
            cords = cords.substr(cords.find_first_not_of(' '));

            std::string u = cords.substr(0, cords.find(' '));
            vtCache[j][0] = std::stof(u);
            cords = cords.substr(cords.find(' '));
            cords = cords.substr(cords.find_first_not_of(' '));

            vtCache[j][1] = std::stof(cords);
         } else if (line[0] == 'v' && line[1] == 'n') {
            std::string cords = line.substr(2);
            cords = cords.substr(cords.find_first_not_of(' '));

            std::string x = cords.substr(0, cords.find(' '));
            vnCache[k][0] = std::stof(x);
            cords = cords.substr(cords.find(' '));
            cords = cords.substr(cords.find_first_not_of(' '));

            std::string y = cords.substr(0, cords.find(' '));
            vnCache[k][1] = std::stof(y);
            cords = cords.substr(cords.find(' '));
            cords = cords.substr(cords.find_first_not_of(' '));

            vnCache[k][2] = std::stof(cords);
         }
      }

      fileStream.close();
   } else {
      std::cout << "Unable to open file" << std::endl;
      return 1;
   }


}