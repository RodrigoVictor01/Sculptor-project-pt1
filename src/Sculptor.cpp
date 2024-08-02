#include "../include/Sculptor.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

// CONSTRUCTOR

/* Construtor da classe Sculptor. Recebe as dimensões nx, ny, nz e inicializa a
 * matriz tridimensional de Voxels.*/
Sculptor::Sculptor(int nx, int ny, int nz) {
  // Define as dimensões nx, ny, nz.
  this->nx = nx;
  this->ny = ny;
  this->nz = nz;

  // Aloca memória para a matriz tridimensional de Voxels.
  v = new Voxel **[nx];
  v[0] = new Voxel *[nx * ny];
  v[0][0] = new Voxel[nx * ny * nz];

  // Cria as linhas da matriz de ponteiros.
  for (int i = 1; i < nx; i++) {
    v[i] = v[i - 1] + ny;
  }

  // Cria as colunas da matriz de ponteiros.
  for (int j = 1; j < nx * ny; j++) {
    v[0][j] = v[0][j - 1] + nz;
  }

  /* Inicializa cada voxel com valores padrão (cores e transparência 0, não
   * visível).*/
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        v[i][j][k].r = 0.0;
        v[i][j][k].g = 0.0;
        v[i][j][k].b = 0.0;
        v[i][j][k].a = 0.0;
        v[i][j][k].show = false;
        // std::cout << "v[" << i << "][" << j << "][" << k << "] =  aaaa"
        //           << std::endl;
      }
    }
  }
}

// DESTRUCTOR
/* Destrutor da classe Sculptor. Libera a memória alocada para a matriz
 * tridimensional de Voxels.*/
Sculptor::~Sculptor() {

  delete[] v[0][0];
  delete[] v[0];
  delete[] v;

}

// Método para definir a cor e a transparência dos voxels.
void Sculptor::setColor(float r, float g, float b, float a) {

  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;

}

// Método para adicionar um voxel em uma posição específica com a cor definida.
void Sculptor::putVoxel(int x, int y, int z) {

  v[x][y][z].r = r;
  v[x][y][z].g = g;
  v[x][y][z].b = b;
  v[x][y][z].a = a;
  v[x][y][z].show = true;

}

/* Método para remover um voxel em uma posição específica (tornando-o
 * invisível).*/
void Sculptor::cutVoxel(int x, int y, int z) { v[x][y][z].show = false; }

/* Método para adicionar uma caixa (bloco de voxels) em um intervalo de posições
 * específico.*/
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int i = x0; i < x1; i++) {
    for (int j = y0; j < y1; j++) {
      for (int k = z0; k < z1; k++) {
        putVoxel(i, j, k);
      }
    }
  }
}

/* Método para remover uma caixa (bloco de voxels) em um intervalo de posições
 * específico.*/
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int i = x0; i < x1; i++) {
    for (int j = y0; j < y1; j++) {
      for (int k = z0; k < z1; k++) {
        cutVoxel(i, j, k);
      }
    }
  }
}

// Método para escrever a representação do objeto em formato OFF em um arquivo.
void Sculptor::writeOFF(const char *filename) {
  // Abre o arquivo para escrita.
  std::ofstream fout;
  fout.open(filename);

  if (!fout.is_open()) {
    std::cout << "Erro ao abrir arquivo" << std::endl;
    exit(1);
  }

  // Calcula o número de vértices a serem escritos.
  int Nvertices = 0;
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          Nvertices += 8;
        }
      }
    }
  }

  // Calcula o número de faces a serem escritas.
  int Nfaces = 0;
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          Nfaces += 6;
        }
      }
    }
  }

  // Seta quantidade de casas decimais padrões para as variáveis de escrita.
  fout << std::fixed;
  fout << std::setprecision(1);

  // Escreve o cabeçalho do arquivo OFF.
  fout << "OFF" << std::endl;
  fout << Nvertices << " " << Nfaces << " 0" << std::endl;

  // Escreve os vértices para cada voxel visível.
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        // Verifica se o voxel na posição atual está visível.
        if (v[i][j][k].show) {
          /* Escreve as coordenadas dos 8 vértices do voxel visível no arquivo
           * OFF.*/

          /* Cada voxel tem 8 vértices em torno de si, com uma distância de 0.5
           em cada eixo (x, y, z). Para cada vértice, as coordenadas (x, y, z)
           são calculadas adicionando ou subtraindo 0.5 à posição atual (i, j,
           k): x pode ser i - 0.5 ou i + 0.5 y pode ser j - 0.5 ou j + 0.5 z
           pode ser k - 0.5 ou k + 0.5 Essas operações criam os vértices nos
           cantos de cada voxel visível. */

          // Vértice 1
          fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          // Vértice 2
          fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          // Vértice 3
          fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          // Vértice 4
          fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          // Vértice 5
          fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
          // Vértice 6
          fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
          // Vértice 7
          fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
          // Vértice 8
          fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
        }
      }
    }
  }

  // Escreve as faces para cada voxel visível.

  // Variável para contar o índice dos vértices.
  int count = 0;
  // Percorre todos os voxels em todas as dimensões nx, ny e nz.
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        // Verifica se o voxel na posição atual está visível.
        if (v[i][j][k].show) {

          /*Cada face é composta por 4 vértices (porque é im cubo) O formato de
          escrita de uma face é: 4 [indice1] [indice2] [indice3] [indice4] [r]
          [g] [b] [a]*/

          // Escreve a primeira face do voxel no arquivo OFF.
          fout << "4 " << count << " " << count + 3 << " " << count + 2 << " "
               << count + 1 << " ";
          // Escreve a cor do voxel no arquivo OFF.
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;

          // Escreve a segunda face do voxel no arquivo OFF.
          fout << "4 " << count + 4 << " " << count + 5 << " " << count + 6
               << " " << count + 7 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;

          // Escreve a terceira face do voxel no arquivo OFF.
          fout << "4 " << count << " " << count + 1 << " " << count + 5 << " "
               << count + 4 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;

          // Escreve a quarta face do voxel no arquivo OFF.
          fout << "4 " << count << " " << count + 4 << " " << count + 7 << " "
               << count + 3 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;

          // Escreve a quinta face do voxel no arquivo OFF.
          fout << "4 " << count + 3 << " " << count + 7 << " " << count + 6
               << " " << count + 2 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;

          // Escreve a sexta face do voxel no arquivo OFF.
          fout << "4 " << count + 1 << " " << count + 2 << " " << count + 6
               << " " << count + 5 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;

          // Incrementa o contador de vértices em 8 para o próximo voxel
          // visível.
          count += 8;
        }
      }
    }
  }
  fout.close();
}