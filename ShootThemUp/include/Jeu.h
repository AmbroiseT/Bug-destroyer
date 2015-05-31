#ifndef JEU_H
#define JEU_H

#include <vector>
#include <string>

class Jeu
{
    public:
        Jeu();
        virtual ~Jeu();
        void printScores();
        void chargerScores();
        void sauverScores();
        void ajouterScore(int s);
        std::string StringScore();
        std::string get(int i);
        std::string scoreString(int score);
    protected:
    private:
        std::vector<int> scores;
        int convertionString(std::string nombre);
};

#endif // JEU_H
