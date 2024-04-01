#include <bits/stdc++.h>
using namespace std;
ifstream fin ("input.txt");
ofstream fout ("output.txt");
map<pair<int, char>, vector<int>> mat;
map<pair<int,int>, int> from;
unordered_set <int> st_final;
string cuv;

void reconstitutie (int y,int poz)
{
    if (poz == 0)
    {
        fout << from[{y,poz}] << ' ' << y << ' ';
        return;
    }
    reconstitutie(from[{y,poz}],poz-1);
    fout<<y<<' ';
}

bool verifica (unordered_set<int> stare, int poz)
{
    if (poz == cuv.size())
    {
        for (auto x : stare)
            if (st_final.find(x) != st_final.end())
            {
                fout<<"Drumul: ";
                reconstitutie(x,poz-1);
                fout<<'\n';
                return 1;
            }
        return 0;
    }
    unordered_set<int> stari_noi;
    for (auto x : stare)
        if (mat.find({x, cuv[poz]}) != mat.end())
            for (auto y : mat[{x, cuv[poz]}])
            {
                stari_noi.insert(y);
                from[{y,poz}] = x;
            }
    if (stari_noi.empty())
        return 0;
    return verifica(stari_noi, poz + 1);
}

int main()
{
    int n, m, x, y, st_init, nrF, nrCuv;
    char l;
    vector<int>stari;
    fin >> n;
    for (int i = 1; i <= n; i++)
    {
        fin >> x;
        stari.push_back(x);
    }
    fin >> m;
    for (int i = 1; i <= m; i++)
    {
        fin >> x >> y >> l;
        if (mat.find({x,l}) == mat.end())
            mat[{x, l}] = {y};
        else mat[{x,l}].push_back(y);
    }
    fin >> st_init >> nrF;
    for (int i = 1; i <= nrF; i++)
    {
        fin >> x;
        st_final.insert(x);
    }
    fin >> nrCuv;
    for (int i = 1; i <= nrCuv; i++)
    {
        fin >> cuv;
        if (verifica({st_init}, 0))
            fout << "DA";
        else fout << "NU";
        fout << '\n';
        from.clear();
    }
    return 0;
}
