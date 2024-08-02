#ifndef SCULPTOR_HPP
#define SCULPTOR_HPP

struct Voxel
{
  float r, g, b, a; // Cores e transparência
  bool show;        // Ativado ou desativado
};

class Sculptor
{

private:
  Voxel ***v;       // Matriz 3D de voxels
  int nx, ny, nz;   // Dimensões da matriz
  float r, g, b, a; // Cor atual

public:
  Sculptor(int _nx, int _ny, int _nz);

  ~Sculptor();

  void setColor(float r, float g, float b, float a);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void writeOFF(const char *filename);
};

#endif // SCULPTOR_H