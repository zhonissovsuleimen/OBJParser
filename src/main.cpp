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

bool isObjectDefinition(const std::string& line){
   return line.length() >= 2 && line[0] == 'o' && line[1] == ' ';
}

bool isVertexDefinition(const std::string& line){
   return line.length() >= 2 && line[0] == 'v' && line[1] == ' ';
}

bool isNormalDefinition(const std::string& line){
   return line.length() >= 2 && line[0] == 'v' && line[1] == 'n';
}

bool isTextureDefinition(const std::string& line){
   return line.length() >= 2 && line[0] == 'v' && line[1] == 't';
}

bool isFaceDefinition(const std::string& line){
   return line.length() >= 2 && line[0] == 'f' && line[1] == ' ';
}

void fillVertexCords(const std::string& line, float& x, float& y, float& z){
   std::string cords = line.substr(1);
   cords = cords.substr(cords.find_first_not_of(' '));

   std::string xStr = cords.substr(0, cords.find(' '));
   x = std::stof(xStr);
   cords = cords.substr(cords.find(' '));
   cords = cords.substr(cords.find_first_not_of(' '));

   std::string yStr = cords.substr(0, cords.find(' '));
   y = std::stof(yStr);
   cords = cords.substr(cords.find(' '));
   cords = cords.substr(cords.find_first_not_of(' '));

   z = std::stof(cords);
}

void fillNormalCords(const std::string& line, float& x, float& y, float& z){
   std::string cords = line.substr(2);
   cords = cords.substr(cords.find_first_not_of(' '));

   std::string xCords = cords.substr(0, cords.find(' '));
   x = std::stof(xCords);
   cords = cords.substr(cords.find(' '));
   cords = cords.substr(cords.find_first_not_of(' '));

   std::string yCords = cords.substr(0, cords.find(' '));
   y = std::stof(yCords);
   cords = cords.substr(cords.find(' '));
   cords = cords.substr(cords.find_first_not_of(' '));

   z = std::stof(cords);
}

void fillTextureCords(const std::string& line, float& u, float& v){
   std::string cords = line.substr(2);
   cords = cords.substr(cords.find_first_not_of(' '));

   std::string uStr = cords.substr(0, cords.find(' '));
   u = std::stof(uStr);
   cords = cords.substr(cords.find(' '));
   cords = cords.substr(cords.find_first_not_of(' '));

   v = std::stof(cords);
}

void fillCountInfo(std::ifstream& fileStream, unsigned int& vCount, unsigned int& vtCount, unsigned int& vnCount){
   std::string line;
   while (std::getline(fileStream, line)) {
      if (isVertexDefinition(line)) {
         vCount++;
      } else if (isTextureDefinition(line)) {
         vtCount++;
      } else if (isNormalDefinition(line)) {
         vnCount++;
      }
   }
}

void fillTriangles(const std::string& line, const std::vector<std::vector<float>>& vCache, const std::vector<std::vector<float>>& vnCache, const std::vector<std::vector<float>>& vtCache,  Triangle& t1, bool& isQuad, Triangle& t2){
   int v1, vt1, vn1;
   int v2, vt2, vn2;
   int v3, vt3, vn3;
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
   
   t1 = {
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

   int erase = 0;
   int copy = vn3;
   while (copy > 0) {
      copy /= 10;
      erase++;
   }

   cords = cords.erase(0, erase);            
   if (cords.length() > 0 && cords.find_first_not_of(' ') != std::string::npos) {
      isQuad = true;
      cords = cords.substr(cords.find_first_not_of(' '));
      v4 = std::stoi(cords.substr(0, cords.find('/')));
      cords = cords.substr(cords.find('/') + 1);
      vt4 = std::stoi(cords.substr(0, cords.find('/')));
      cords = cords.substr(cords.find('/') + 1);
      vn4 = std::stoi(cords.substr(0, cords.find(' ')));

      t2 = {
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
   } 
}

void printResults(const std::list<std::list<Triangle>>& objects){
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

      unsigned int vCount = 0;
      unsigned int vtCount = 0;
      unsigned int vnCount = 0;
      fillCountInfo(fileStream, vCount, vtCount, vnCount);

      std::vector<std::vector<float>> vCache(vCount, {0.0f, 0.0f, 0.0f});
      std::vector<std::vector<float>> vtCache(vtCount, {0.0f, 0.0f});
      std::vector<std::vector<float>> vnCache(vnCount, {0.0f, 0.0f, 0.0f});
   
      fileStream.clear();
      fileStream.seekg(0);

      int v = 0;
      int vt = 0;
      int vn = 0;
      while (!fileStream.eof()) {
         std::list<Triangle> objectTriangles;

         while (std::getline(fileStream, line)) {
            if (isObjectDefinition(line)) break; 

            if (isVertexDefinition(line)) {
               float x,y,z;
               fillVertexCords(line, x, y, z);
               vCache[v][0] = x;
               vCache[v][1] = y;
               vCache[v][2] = z;
               v++;
            } else if (isTextureDefinition(line)) {
               float u,v;
               fillTextureCords(line, u, v);
               vtCache[vt][0] = u;
               vtCache[vt][1] = v;
               vt++;
            } else if (isNormalDefinition(line)) {
               float x,y,z;
               fillNormalCords(line, x, y, z);
               vnCache[vn][0] = x;
               vnCache[vn][1] = y;
               vnCache[vn][2] = z;
               vn++;
            } else if (isFaceDefinition(line)) {
               bool isQuad = false;
               Triangle t1, t2;
               fillTriangles(line, vCache, vnCache, vtCache, t1, isQuad, t2);

               objectTriangles.push_back(t1);
               allTriangles.push_back(t1);

               if (isQuad) {
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
   
   printResults(objects);
}