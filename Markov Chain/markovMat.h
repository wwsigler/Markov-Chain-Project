#ifndef MARKOVMAT_H
#define MARKOVMAT_H

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class markovMat {
private:
    map<string, map<string, float>> matrix;
    int corpusSize;

public:
    markovMat(const char* filename);
    ~markovMat();
    string generate(int length);
};

markovMat::markovMat(const char* filename) {
    ifstream file(filename);
    string line, word;
    float weight;

    if (file.good()) {
        file >> corpusSize;
        file.ignore(1, '\n');

        while (getline(file, line)) {
            stringstream parser(line);
            string prevWord, currWord;

            parser >> prevWord;
            while (parser >> currWord >> weight) {
                matrix[prevWord][currWord] = weight;
                prevWord = currWord;
            }
        }
    }
}

markovMat::~markovMat()
{
    // map should be destroyed automatically
}


string markovMat::generate(int length)
{
    //initializes random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    //random starting bigram
    map<string, map<string, float>>::iterator it = matrix.begin();
    advance(it, rand() % matrix.size());
    string prev = it->first;
    string result = prev;

    //generates word sequence
    for (int i = 1; i < length; i++)
	{
    	map<string, float>& successors = matrix[prev];
        if (successors.empty())
		{
            //new bigram if no successor
            it = matrix.begin();
            advance(it, rand() % matrix.size());
            prev = it->first;
        }
		else
		{
            //random successor selection
            float totalWeight = 0.0;
            for (auto& pair : successors)
			{
                totalWeight += pair.second;
            }
            float l = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * totalWeight;
            for (auto& pair : successors)
			{
                l -= pair.second;
                if (l < 0.0) {
                    prev = pair.first;
                    break;
                }
            }
        }
        result += " " + prev;
    }
	//removes commas
	    for (int i = 0; i < result.size(); i++)
		{
			if (result[i] == ',')
			{
				result[i] = ' ';
			}			
		}
    return result;
}


#endif
