#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>

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
      return 0;
   }
   std::string filename{ argv[1] };
   std::ifstream fileStream (filename);

   std::list<Triangle> triangles;

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
            i++;
         } else if (line[0] == 'v' && line[1] == 't') {
            std::string cords = line.substr(2);
            cords = cords.substr(cords.find_first_not_of(' '));

            std::string u = cords.substr(0, cords.find(' '));
            vtCache[j][0] = std::stof(u);
            cords = cords.substr(cords.find(' '));
            cords = cords.substr(cords.find_first_not_of(' '));

            vtCache[j][1] = std::stof(cords);
            j++;
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
            k++;
         } else if (line[0] == 'f' && line[1] == ' '){
            int v1, vt1, vn1;
            int v2, vt2, vn2;
            int v3, vt3, vn3;
            //in case there are 4 data points
            int v4, vt4, vn4;

            std::string cords = line.substr(1);
            cords = cords.substr(cords.find_first_not_of(' '));
            v1 = std::stoi(cords.substr(0, cords.find('/')));
            cords = cords.substr(cords.find('/') + 1);
            vt1 = std::stoi(cords.substr(0, cords.find('/')));
            cords = cords.substr(cords.find('/') + 1);
            vn1 = std::stoi(cords.substr(0, cords.find(' ')));            
            cords = cords.substr(cords.find(' ') + 1);

            cords = cords.substr(cords.find_first_not_of(' '));
            v2 = std::stoi(cords.substr(0, cords.find('/')));
            cords = cords.substr(cords.find('/') + 1);
            vt2 = std::stoi(cords.substr(0, cords.find('/')));
            cords = cords.substr(cords.find('/') + 1);
            vn2 = std::stoi(cords.substr(0, cords.find(' ')));
            cords = cords.substr(cords.find(' ') + 1);

            cords = cords.substr(cords.find_first_not_of(' '));
            v3 = std::stoi(cords.substr(0, cords.find('/')));
            cords = cords.substr(cords.find('/') + 1);
            vt3 = std::stoi(cords.substr(0, cords.find('/')));
            cords = cords.substr(cords.find('/') + 1);
            vn3 = std::stoi(cords.substr(0, cords.find(' ')));
            
            Triangle t = {
               VertexInfo {
                  vCache[v1 - 1][0],
                  vCache[v1 - 1][1],
                  vCache[v1 - 1][2],
                  vnCache[vn1 - 1][0],
                  vnCache[vn1 - 1][1],
                  vnCache[vn1 - 1][2],
                  vtCache[vt1 - 1][0],
                  vtCache[vt1 - 1][1]
               },
               VertexInfo {
                  vCache[v2 - 1][0],
                  vCache[v2 - 1][1],
                  vCache[v2 - 1][2],
                  vnCache[vn2 - 1][0],
                  vnCache[vn2 - 1][1],
                  vnCache[vn2 - 1][2],
                  vtCache[vt2 - 1][0],
                  vtCache[vt2 - 1][1]
               },
               VertexInfo {
                  vCache[v3 - 1][0],
                  vCache[v3 - 1][1],
                  vCache[v3 - 1][2],
                  vnCache[vn3 - 1][0],
                  vnCache[vn3 - 1][1],
                  vnCache[vn3 - 1][2],
                  vtCache[vt3 - 1][0],
                  vtCache[vt3 - 1][1]
               }
            }; 
            triangles.push_back(t);

            int erase = 0;
            int copy = vn3;
            while (copy > 0) {
               copy /= 10;
               erase++;
            }

            cords = cords.erase(0, erase);            
            if (cords.length() > 0 && cords.find_first_not_of(' ') != std::string::npos) {
               cords = cords.substr(cords.find_first_not_of(' '));
               v4 = std::stoi(cords.substr(0, cords.find('/')));
               cords = cords.substr(cords.find('/') + 1);
               vt4 = std::stoi(cords.substr(0, cords.find('/')));
               cords = cords.substr(cords.find('/') + 1);
               vn4 = std::stoi(cords.substr(0, cords.find(' ')));

               Triangle t2 = {
                  VertexInfo {
                     vCache[v1 - 1][0],
                     vCache[v1 - 1][1],
                     vCache[v1 - 1][2],
                     vnCache[vn1 - 1][0],
                     vnCache[vn1 - 1][1],
                     vnCache[vn1 - 1][2],
                     vtCache[vt1 - 1][0],
                     vtCache[vt1 - 1][1]
                  },
                  VertexInfo {
                     vCache[v3 - 1][0],
                     vCache[v3 - 1][1],
                     vCache[v3 - 1][2],
                     vnCache[vn3 - 1][0],
                     vnCache[vn3 - 1][1],
                     vnCache[vn3 - 1][2],
                     vtCache[vt3 - 1][0],
                     vtCache[vt3 - 1][1]
                  },
                  VertexInfo {
                     vCache[v4 - 1][0],
                     vCache[v4 - 1][1],
                     vCache[v4 - 1][2],
                     vnCache[vn4 - 1][0],
                     vnCache[vn4 - 1][1],
                     vnCache[vn4 - 1][2],
                     vtCache[vt4 - 1][0],
                     vtCache[vt4 - 1][1]
                  }
               };
               triangles.push_back(t2);
            } 
         }
      }

      fileStream.close();
   } else {
      std::cout << "Unable to open file" << std::endl;
      return 0;
   }

   std::cout << "Number of triangles: " << triangles.size() << std::endl;
   for(Triangle i : triangles){
      std::cout << "t:" << std::endl;

      std::cout << "v:" << std::endl;
      std::cout << "x=" << i.v1.x << std::endl;
      std::cout << "y=" << i.v1.y << std::endl;
      std::cout << "z=" << i.v1.z << std::endl;
      std::cout << "nx=" << i.v1.normal_x << std::endl;
      std::cout << "ny=" << i.v1.normal_y << std::endl;
      std::cout << "nz=" << i.v1.normal_z << std::endl;
      std::cout << "u=" << i.v1.u << std::endl;
      std::cout << "v=" << i.v1.v << std::endl;

      std::cout << "v:" << std::endl;
      std::cout << "x=" << i.v2.x << std::endl;
      std::cout << "y=" << i.v2.y << std::endl;
      std::cout << "z=" << i.v2.z << std::endl;
      std::cout << "nx=" << i.v2.normal_x << std::endl;
      std::cout << "ny=" << i.v2.normal_y << std::endl;
      std::cout << "nz=" << i.v2.normal_z << std::endl;
      std::cout << "u=" << i.v2.u << std::endl;
      std::cout << "v=" << i.v2.v << std::endl;

      std::cout << "v:" << std::endl;
      std::cout << "x=" << i.v3.x << std::endl;
      std::cout << "y=" << i.v3.y << std::endl;
      std::cout << "z=" << i.v3.z << std::endl;
      std::cout << "nx=" << i.v3.normal_x << std::endl;
      std::cout << "ny=" << i.v3.normal_y << std::endl;
      std::cout << "nz=" << i.v3.normal_z << std::endl;
      std::cout << "u=" << i.v3.u << std::endl;
      std::cout << "v=" << i.v3.v << std::endl;
   }
}