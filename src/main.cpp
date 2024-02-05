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

   std::list<std::list<Triangle>> objects;
   std::list<Triangle> allTriangles;

   if (fileStream.is_open()) {
      std::string line;

      //counting the number of v's, vt's, and vn's
      unsigned int vCount = 0;
      unsigned int vtCount = 0;
      unsigned int vnCount = 0;

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
   
      fileStream.clear();
      fileStream.seekg(0);

      int i = 0;
      int j = 0;
      int k = 0;
      while (std::getline(fileStream, line)) {
          if (line.length() < 2) continue;
          if (line[0] == 'o' && line[1] == ' ') {
              break;
          }
      }

      while (!fileStream.eof()) {
          std::list<Triangle> objectTriangles;
         //parsing the v's, vt's, and vn's and storing them
         while (std::getline(fileStream, line)) {
            if (line.length() < 2) continue;
            if (line[0] == 'o' && line[1] == ' ') {
               break;
            }

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
               objectTriangles.push_back(t);
               allTriangles.push_back(t);

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
                  objectTriangles.push_back(t2);
                  allTriangles.push_back(t2);
               } 
            }
         }

         objects.push_back(objectTriangles);
      }

      fileStream.close();
   } else {
      std::cout << "Unable to open file" << std::endl;
      return 0;
   }
   
   for(std::list<Triangle> object : objects){
      for(Triangle triangle : object){
         std::cout << "t:" << std::endl;

         std::cout << "v:" << std::endl;
         std::cout << "x=" << triangle.v1.x << std::endl;
         std::cout << "y=" << triangle.v1.y << std::endl;
         std::cout << "z=" << triangle.v1.z << std::endl;
         std::cout << "nx=" << triangle.v1.normal_x << std::endl;
         std::cout << "ny=" << triangle.v1.normal_y << std::endl;
         std::cout << "nz=" << triangle.v1.normal_z << std::endl;
         std::cout << "u=" << triangle.v1.u << std::endl;
         std::cout << "v=" << triangle.v1.v << std::endl;

         std::cout << "v:" << std::endl;
         std::cout << "x=" << triangle.v2.x << std::endl;
         std::cout << "y=" << triangle.v2.y << std::endl;
         std::cout << "z=" << triangle.v2.z << std::endl;
         std::cout << "nx=" << triangle.v2.normal_x << std::endl;
         std::cout << "ny=" << triangle.v2.normal_y << std::endl;
         std::cout << "nz=" << triangle.v2.normal_z << std::endl;
         std::cout << "u=" << triangle.v2.u << std::endl;
         std::cout << "v=" << triangle.v2.v << std::endl;

         std::cout << "v:" << std::endl;
         std::cout << "x=" << triangle.v3.x << std::endl;
         std::cout << "y=" << triangle.v3.y << std::endl;
         std::cout << "z=" << triangle.v3.z << std::endl;
         std::cout << "nx=" << triangle.v3.normal_x << std::endl;
         std::cout << "ny=" << triangle.v3.normal_y << std::endl;
         std::cout << "nz=" << triangle.v3.normal_z << std::endl;
         std::cout << "u=" << triangle.v3.u << std::endl;
         std::cout << "v=" << triangle.v3.v << std::endl;
      }
      std::cout << std::endl;
   }
   
}