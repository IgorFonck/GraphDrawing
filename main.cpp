/* 
* Autor: Igor Oliveira da Fonseca
*
* Alguns trechos adaptados de: https://chameerawijebandara.wordpress.com/2014/03/15/sample-layout-in-ogdf/
*
*/

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/planarlayout/MixedModelLayout.h>
#include <ogdf/fileformats/GraphIO.h>
 
#include <iostream>
#include <chrono>
#include <ctime> 
#include <string> 
#include <iostream>
#include <fstream>

using namespace ogdf;
 
int main(int argc,char* argv[])
{
    
    int i_start = 0;
    int i_end = 0;
     if (argc==3) {
         // Utiliza valores de step e n máximo passados como argumento
         i_start = std::stoi(argv[1]);
         i_end = std::stoi(argv[2]);
     }
     else {
         // Não foram passados argumentos, usa valores padrão
         i_start = 50;
         i_end = 500;
     }

    int loop = 1; // contador de loops

    bool is_sparse = true; // controle de grafo esparso/denso
    
    // Inicia o arquivo CSV
    std::ofstream myfile;
    myfile.open ("output_times.csv");
    myfile << "0";
    for (int i = i_start; i <= i_end; i = i + i_start) {
        myfile << "," << i;
    }
    myfile << "\n";

    for (int i = i_start; i <= i_end; i = i + i_start) {

        int edges_sparse =  i * 1.5;
        int edges_dense = (3 * i) - 6;

        // Gera o grafo aleatório
        Graph G;
        if (is_sparse)
            randomPlanarTriconnectedGraph(G, i, edges_sparse);
        else
            randomPlanarTriconnectedGraph(G, i, edges_dense);

        // Cria os atributos para o grafo
        GraphAttributes GA(G, GraphAttributes::nodeGraphics |
                                    GraphAttributes::edgeGraphics |
                                    GraphAttributes::nodeLabel |
                                    GraphAttributes::nodeStyle);

        GA.scale(16, 9, false);

        // Iteração por todos os vértices do grafo
        node v;
        for (node v : G.nodes)
        {
            GA.fillColor(v) = Color("#13d16e"); // cor de preenchimento do vértice

            GA.height(v) = 20.0;                // define a altura como 20
            GA.width(v) = 20.0;                 // define a largura como 20
            GA.shape(v) = ogdf::Shape::Ellipse; // define a forma como elipse

            // Utiliza o índice do vértice como label
            string s = to_string(v->index());
            char const *pchar = s.c_str();
            GA.label(v) = pchar;
        }

        // Inicia o timer
        auto start = std::chrono::system_clock::now();

        // Utiliza o algoritmo MixedModelLayout
        MixedModelLayout MML;
        MML.call(GA);

        // Gera o grafo em formato SVG
        auto itos = std::to_string(i);
        auto title_sparse = "mygraph-" + itos + "-sparse.svg";
        auto title_dense = "mygraph-" + itos + "-dense.svg";
        if (is_sparse)
            GraphIO::write(GA, title_sparse, GraphIO::drawSVG);
        else
            GraphIO::write(GA, title_dense, GraphIO::drawSVG);

        // Imprime tempo de processamento
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "(l=" << loop << ",i=" << i << ") " << elapsed_seconds.count() << "\n";

        // Escreve no arquivo CSV
        if (i == i_start)
        {
            if (is_sparse)
            {
                //myfile << "Sparse" << loop << ",0";
                myfile << "0";
            }
            else
            {
                //myfile << "Dense" << loop-3 << ",0";
                myfile << "0";
            }
        }
        myfile << "," << elapsed_seconds.count();
        if (i == i_end)
        {
            myfile << "\n";
        }

        // Três loops para esparso e três para denso
        if (i == i_end)
        { // Terminou este loop
            if (loop == 3)
            {
                // Se terminou o 3º loop, altera para grafo denso
                is_sparse = false;
            }
            i = 0;
            if (loop == 6)
            {
                // Se terminou o 6º loop, permite encerrar
                i = i_end;
            }
            loop++;
        }
    }

    // Encerra o arquivo CSV
    myfile.close();

    return 0;
}